#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "include/stdlog.h"

#define SERVICE_ERROR_LOG "/gdonwiiu/logs/serviceerrorlog.log"

int startRuntimeErrorLogProcess(char *_Error, char *_Eid, char *_RefService) {
    pid_t forkpid = fork();

    // argv pointer
    char **argv = calloc(3, 52);
    argv[0] = _Error;
    argv[1] = _Eid;
    argv[2] = "\0"; // trailing null terminator

    if (forkpid == -1) {
        printl(SERVICE_ERROR_LOG, "Failed to fork process in C function startRuntimeErrorLogProcess ( rt32logs.rthelper.service ) | Pointer: ");
        printldbgptr(SERVICE_ERROR_LOG, &forkpid);
        printl(SERVICE_ERROR_LOG, "\n"); // eol terminator
    } else if (forkpid == 0) {
        execve("/gdonwiiu/bin/runtimeerror.dbg", argv, NULL);
        printl(SERVICE_ERROR_LOG, "Failed to execve in C function startRuntimeErrorProcess in child process of rt32logs.rthelper.service\n");
        _exit(1);
    } else {
        int status;
        waitpid(forkpid, &status, 0);

        if (status == 1) {
            printl(SERVICE_ERROR_LOG, "Forked process exited with status code of 1 ( rt32logs.rthelper.service ) | Pointer: ");
            printldbgptr(SERVICE_ERROR_LOG, &status);
            printl(SERVICE_ERROR_LOG, "\n"); // eol terminator
            return 1;
        } else {
            return status;
        }
    }
}


int main(int argc, char *argv[], char **envp) {
    FILE *file = fopen("/gdonwiiu/logs/stderrlogs.log", "r");
    if (file == NULL) {
        printf("[ ERROR FROM SERVICE ]: Failed to open stderrlogs.log | rt32logs.rthelper.service\n");
        printl(SERVICE_ERROR_LOG, "Failed to open error log file ( killing process ) | Pointer: ");
        printldbgptr(SERVICE_ERROR_LOG, &file);
        printl(SERVICE_ERROR_LOG, "\n"); // eol terminator
        _exit(1);
    }
    char *fullfilebuff = malloc(65120);
    char presavestate[52];
    char savestate[52];

    for (;;) {
        fgets(fullfilebuff, 65120, file);
        int bufflen = strlen(fullfilebuff);
        for (int i; i<52; i++) {
            presavestate[i] = fullfilebuff[bufflen-(52+i)];
        }
        for (int i; i<52; i++) {
            savestate[i] = fullfilebuff[bufflen-(52+i)];
        }

        if (!strcmp(presavestate, savestate)) {
            startRuntimeErrorLogProcess(savestate, "010", "https://github.com/GDWIIU/GDONWIIU/issue");
        }
    }

    return 0;
}