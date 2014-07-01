#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include <fcntl.h>
#include <errno.h>
#include "bbbk_i2c.h"

    int open(const char *path, int oflag) {
        mock("os")
            .actualCall("open")
            .withParameter("path", path)
            .withParameter("oflag", oflag);
        return mock("os").intReturnValue();
    }

}

TEST_GROUP(i2c_lib)
{
    char *i2c_path;
    int i2c_oflag;
    int i2c_fd;
    int error;
    void setup() {
        char tmp_path[]="/dev/i2c-3";
        size_t len = sizeof(tmp_path);
        i2c_path = (char*)malloc(len+1);
        memcpy(i2c_path, tmp_path, len);
        i2c_oflag = O_RDWR;
        i2c_fd = -1;
        error = -1;
    }

    void teardown()
    {
        free(i2c_path);
        mock.checkExpectations();
        mock().clear();
    }
};

TEST(i2c_lib, open_fails_EACCES)
{
    mock("os")
        .expectOneCall("open")
        .withParameter("path", i2c_path)
        .withParameter("oflag", i2c_oflag)
        .andReturnValue(-1);
    mock("os")
        .expectOneCall("perror")
        .withParameter("error: i2c_open() failure");
    errno = EACCES;
    result = i2c_open(i2c_path, &error);
    LONGS_EQUAL(result, -1);
    LONGS_EQUAL(*error, FILE_ACCESS_ERROR);
    
}

