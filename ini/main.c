#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "include/gdonwiiu.h"
#include "include/stdlog.h"

#define STDLOG_PATH "/gdonwiiu/logs/stdlog.log"
#define ERRORL_PATH "/gdonwiiu/logs/errors.log"

// 0: sucsess, 1: program error, 2: system error
int createCProcessExec(char *_target, char *const _argv[], char *const _envp[]) {
    int forkproc = fork();
    int procstat;

    if (forkproc == -1) {
        printf("[ ERROR ]: Failed to fork process\n");
        printl(ERRORL_PATH, "[ ERROR ]: Failed to fork process\n");
        return 2;
    } else if (forkproc == 0) {
        execve(_target, _argv, _envp);
    } else {
        waitpid(forkproc, &procstat, 0);
        if (procstat == 0) {
            return 0;
        } else {
            printf("[ WARNING ]: Child process returned status code of 1\n");
            printl(ERRORL_PATH, "[ WARNING ]: Child process returned status code of 1\n");
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[], char *envp[]) {
    // startup infomation
    printf("Welcome to GDONWIIU\n");
    printl(STDLOG_PATH, "Startup GDONWIIU\n");

    struct GDONWIIU_DATA gdonwiiu_data = initGDONWIIU_Struct();
    if (&gdonwiiu_data == NULL) {
        fprintf(stderr, "Failed to initialize GDONWIIU_DATA structure\n");
        printl(STDLOG_PATH, "Error: Failed to initialize GDONWIIU_DATA structure\n");
        return EXIT_FAILURE;
    }
    printl(STDLOG_PATH, "Initialized standard data structure at pointer: ");
    printldbgptr(STDLOG_PATH, &gdonwiiu_data);
    printl(STDLOG_PATH, "\n"); // eol terminator

    printf("  wine version: %s\n", gdonwiiu_data.__wine_version);
    printf("  debian version: %s\n", gdonwiiu_data.__debian_version);
    printf("  kernel version: %s\n", gdonwiiu_data.__kernel_version);
    printf("  systemd version: %s\n", gdonwiiu_data.__systemd_version);
    printf("  gdonwiiu version: %s\n\n", gdonwiiu_data.__gdonwiiu_version);

    printl(STDLOG_PATH, "Printed all data to stdio ( fd 1 )\n");

    // setting up runtime support
    printf("[ EXECUTE ]: Executing service | /gdonwiiu/services/aptpkg\n");
    printl(STDLOG_PATH, "[ EXECUTE ]: Executing service /gdonwiiu/services/aptpkg\n");
    createCProcessExec("/gdonwiiu/services/aptpkg", NULL, NULL);
}