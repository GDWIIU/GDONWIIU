#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include "include/gdonwiiu.h"
#include "include/stdlog.h"

#define STDLOG_PATH "/gdonwiiu/logs/stdlog.log"

int main(int argc, char *argv[], char *envp[]) {
    // startup infomation
    printf("Welcome to GDONWIIU\n");
    printl(STDLOG_PATH, "Startup GDONWIIU\n");

    struct GDONWIIU_DATA gdonwiiu_data = initGDONWIIU_Struct();
    printl(STDLOG_PATH, "Initialized standard data structure at pointer: ");
    printldbgptr(STDLOG_PATH, &gdonwiiu_data);
    printl(STDLOG_PATH, "\n"); // eol terminator

    printf("  wine version: %s\n", gdonwiiu_data.__wine_version);
    printf("  debian version: %s\n", gdonwiiu_data.__debian_version);
    printf("  kernel version: %s\n", gdonwiiu_data.__kernel_version);
    printf("  systemd version: %s\n", gdonwiiu_data.__systemd_version);
    printf("  gdonwiiu version: %s\n", gdonwiiu_data.__gdonwiiu_version);

    printl(STDLOG_PATH, "Printed all data to stdio ( fd 1 )\n");

    // setting up runtime support
    
}