#include <unistd.h>
#include <fcntl.h>

#ifndef __GDONWIIU_HEADERS__
#define __GDONWIIU_HEADERS__
#endif

int rdfilemac_fd;

struct __gdonwiiu_data_ {
    char *__wine_version;
    char *__debian_version;
    char *__kernel_version;
    char *__systemd_version;
    char *__gdonwiiu_version;
    
    char *__target_gd_version_min;
    char *__target_gd_version_max;
};
#define GDONWIIU_DATA __gdonwiiu_data_

#define RDFILE_MAC(file, destptr, rbits) \
    rdfilemac_fd = open(file, O_RDONLY); \
    read(rdfilemac_fd, destptr, rbits); \
    close(rdfilemac_fd);

struct GDONWIIU_DATA initGDONWIIU_Struct() {
    struct GDONWIIU_DATA data;

    // Allocate memory for each string pointer
    data.__wine_version = malloc(11);
    data.__debian_version = malloc(11);
    data.__kernel_version = malloc(11);
    data.__systemd_version = malloc(11);
    data.__gdonwiiu_version = malloc(11);
    data.__target_gd_version_min = malloc(11);
    data.__target_gd_version_max = malloc(11);

    // Ensure memory allocation was successful
    if (!data.__wine_version || !data.__debian_version || !data.__kernel_version ||
        !data.__systemd_version || !data.__gdonwiiu_version || 
        !data.__target_gd_version_min || !data.__target_gd_version_max) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Read data into allocated memory
    RDFILE_MAC("/gdonwiiu/data/winever.txt", data.__wine_version, 10);
    RDFILE_MAC("/gdonwiiu/data/debver.txt", data.__debian_version, 10);
    RDFILE_MAC("/gdonwiiu/data/kerver.txt", data.__kernel_version, 10);
    RDFILE_MAC("/gdonwiiu/data/sysdver.txt", data.__systemd_version, 10);
    RDFILE_MAC("/gdonwiiu/data/gdonwiiuver.txt", data.__gdonwiiu_version, 10);
    RDFILE_MAC("/gdonwiiu/data/gd/target_ver_max.txt", data.__target_gd_version_max, 10);
    RDFILE_MAC("/gdonwiiu/data/gd/target_ver_min.txt", data.__target_gd_version_min, 10);

    // Null-terminate the strings
    data.__wine_version[10] = '\0';
    data.__debian_version[10] = '\0';
    data.__kernel_version[10] = '\0';
    data.__systemd_version[10] = '\0';
    data.__gdonwiiu_version[10] = '\0';
    data.__target_gd_version_min[10] = '\0';
    data.__target_gd_version_max[10] = '\0';

    return data;
}