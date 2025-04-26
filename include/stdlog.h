#include <stdio.h>
#include <fcntl.h>

#ifndef __STDLOG_HEADERS__
#define __STDLOG_HEADERS__
#endif

#ifdef USE_CUSTOM_STDIO
#define STDOUT 1
#define STDIN 0
#define STDERR 2
#endif

int printl(char *_file, char *_data) {
    FILE *file = fopen(_file, "a");
    if (file == NULL) {
        return -1; // Return error code if file cannot be opened
    }
    fprintf(file, "%s", _data);
    fclose(file);
    return 0; // Return success code
}

int printldbgptr(char *_file, void *_ptr) {
    FILE *file = fopen(_file, "a");
    if (file == NULL) {
        return -1; // Return error code if file cannot be opened
    }
    fprintf(file, "%p", _ptr);
    fclose(file);
    return 0; // Return success code
}