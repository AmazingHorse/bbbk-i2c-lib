#include <stdio.h>
#include <errno.h>
#include "bbbk_i2c.h"
#include "stream.h"

int i2c_open(const char *path, int *error) {
    int i2c_fd;
    int errsv = 0;
    if((i2c_fd = open_stream(path, &errsv)) < 0) {
        perror("error: i2c_open() failure");
        if(errsv == EACCES) {
            *error = E_ACCESS_DENIED;
        }
        return -1;
    }
    return i2c_fd;
}
