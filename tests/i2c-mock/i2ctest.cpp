#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "bbbk_i2c.h"
#include "stream.h"

    int open_stream(const char *name, int *error) {
        mock("os")
            .actualCall("open_stream")
            .withParameter("name", name)
            .withOutputParameter("error", error);
        return mock("os").intReturnValue();
    }
    void perror(const char *str) {
        mock("os")
            .actualCall("perror")
            .withParameter("str", str);
    }
}

TEST_GROUP(i2c_lib)
{
    char i2c_path[11] = "/dev/i2c-3";
    int *i2c_error;
    int i2c_fd;
    i2c_error_code code;
    void setup() {
        i2c_fd = -1;
    }

    void teardown()
    {
        free(i2c_path);
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(i2c_lib, open_fails_EACCES)
{
    mock("os")
        .expectOneCall("open_stream")
        .withParameter("name", "/dev/i2c-3")
        .withOutputParameterReturning("error", i2c_error, sizeof(int))
        .andReturnValue(-1);
    mock("os")
        .expectOneCall("perror")
        .withParameter("str", "error: i2c_open() failure");
    i2c_fd = i2c_open(i2c_path, i2c_error);
    LONGS_EQUAL(i2c_fd, -1);
    LONGS_EQUAL(*i2c_error, E_ACCESS_DENIED);
    
}

