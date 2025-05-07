#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int installPackage(char *_package) {
    int forkpid = fork();
    int status;

    char *argv[3];
    argv[0] = "install";
    argv[1] = _package;
    argv[2] = "\0";
    
    if (forkpid == -1) {
        printf("[ ERROR ]: There has been an error forking process at %i\n", getpid());
        return 1;
    } else if (forkpid == 0) {
        execve("/usr/bin/apt", argv, NULL);
    } else {
        waitpid(forkpid, &status, 0);
        if (status == 0) {
            printf("[ OK ]: Sucsessfuly installed apt package %s and exited with status of 0 | thrown from adress of %p\n", _package, &status);
            return 0;
        } else if (status == 1) {
            printf("[ OK ]: Failed to install apt package %s and exited with status of 1 | thrown from adress of %p\n", _package, &status);
            return 1;
        }
    }
}

int main(int argc, char *argv[], char **envp) {
    installPackage("python3");
    installPackage("wine32");
    return 0;
}