#ifndef BBBK_I2C_H
#define BBBK_I2C_H

int i2c_open(const char *path, int *error);

typedef enum
{
    FILE_ACCESS_ERROR = 0,
} i2c_status;
#endif  /* D_Flash_H */
