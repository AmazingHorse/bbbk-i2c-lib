#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "bbbk_i2c.h"

int i2c_open(const char *path, int *error) {
    int i2c_fd, errsv;
    if((i2c_fd = open(path, O_RDWR)) < 0) {
        errsv = errno;
        perror("error: i2c_open() failure");
        if (errsv == EACCES) {
            *error = FILE_ACCESS_ERROR;
        } 
        return -1;
    }
    return i2c_fd;
}
