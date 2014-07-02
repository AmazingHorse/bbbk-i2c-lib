#ifndef BBBK_I2C_H
#define BBBK_I2C_H

int i2c_open(const char *path, int *error);

typedef enum {                                                                   
    E_ACCESS_DENIED = 1                                                          
} i2c_error_code;    



#endif  /* D_Flash_H */
