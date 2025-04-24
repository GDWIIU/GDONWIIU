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
    fprintf(file, "%s", _data);
    fclose(file);
}
int printldbgptr(char *_file, void *_ptr) {
    FILE *file = fopen(_file, "a");
    fprintf(file, "%p", _ptr);
    fclose(file);
}