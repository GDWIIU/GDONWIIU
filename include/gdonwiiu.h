#include <unistd.h>
#include <fcntl.h>

#ifndef __GDONWIIU_HEADERS__
#define __GDONWIIU_HEADERS__
#endif

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
    int fd = open(file, O_RDONLY); \
    read(fd, destptr, rbits); \
    close(fd);

struct GDONWIIU_DATA initGDONWIIU_Struct() {
    struct GDONWIIU_DATA data;
    RDFILE_MAC("/gdonwiiu/data/winever.txt", data.__wine_version, 10);
    RDFILE_MAC("/gdonwiiu/data/debver.txt", data.__debian_version, 10);
    RDFILE_MAC("/gdonwiiu/data/kerver.txt", data.__kernel_version, 10);
    RDFILE_MAC("/gdonwiiu/data/sysdver.txt", data.__systemd_version, 10);
    RDFILE_MAC("/gdonwiiu/data/gdonwiiuver.txt", data.__gdonwiiu_version, 10);
    RDFILE_MAC("/gdonwiiu/data/gd/target_ver_max.txt", data.__target_gd_version_max, 10);
    RDFILE_MAC("/gdonwiiu/data/gd/target_ver_min.txt", data.__target_gd_version_min, 10);
    return data;
}