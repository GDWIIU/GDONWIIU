#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct __gd_meta_ {
    char *_appdata;
    char *_program_files;
};
#define GDMETA __gd_meta_

struct GDMETA getGDMETAContents() {
    struct GDMETA meta;
    FILE *_filedesc;

    printf("[ OK ]: Reading gdmeta contents ( /gdonwiiu/geometrydash/data/procfiles.target )\n");
    _filedesc = fopen("/gdonwiiu/geometrydash/data/procfiles.target", "r");
    fgets(meta._program_files, 35, _filedesc);
    fclose(_filedesc);
    printf("[ OK ]: Reading gdmeta contents ( /gdonwiiu/geometrydash/data/appdata.target )\n");
    _filedesc = fopen("/gdonwiiu/geometrydash/data/appdata.target", "r");
    fgets(meta._appdata, 35, _filedesc);
    fclose(_filedesc);

    return meta;
}

void * installGeometryDash(struct GDMETA meta) {
    char *_SystemCopyADCmd = malloc(44 + strlen(meta._appdata));
    char *_SystemCopyPFCmd = malloc(46 + strlen(meta._program_files));
    sprintf(_SystemCopyADCmd, "cp -r /gdonwiiu/geometrydash/appdata WINC:/%s", meta._appdata);
    sprintf(_SystemCopyPFCmd, "cp -r /gdonwiiu/geometrydash/procfiles WINC:/%s", meta._program_files);

    printf("[ OK ]: Copying geometry dash files to WINC: target directory\n");
    system(_SystemCopyADCmd);
    printf("[ OK ]: Copying geometry dash files to WINC: target directory\n");
    system(_SystemCopyPFCmd);

    printf("[ OK ]: Removing geometry dash files /gdonwiiu/geometrydash\n");
    system("rm -r /gdonwiiu/geometrydash");
    system("mkdir /gdonwiiu/geometrydash");
}


int main(int argc, char *argv[], char **envp) {
    printf("[ OK ]: Decompressing Geometry Dash image\n");
    system("tar xf /gdonwiiu/geometrydash.gdimg /gdonwiiu/geometrydash");

    struct GDMETA metadata = getGDMETAContents();
    installGeometryDash(metadata);

    return 0;
}