#ifndef EZO_BOARD_H
#define EZO_BOARD_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    EZO_SUCCESS,
    EZO_FAIL,
    EZO_NOT_READY,
    EZO_NO_DATA,
    EZO_NOT_READ_CMD
} ezo_error_t;

typedef struct {
    uint8_t i2c_address;
    char name[16];  // can be dynamically allocated if needed
    float reading;
    bool issued_read;
    ezo_error_t last_error;
} EzoBoard;

// Constructors
void ezo_init(EzoBoard* board, uint8_t addr);
void ezo_init_named(EzoBoard* board, uint8_t addr, const char* name);

// Commands
void ezo_send_cmd(EzoBoard* board, const char* cmd);
void ezo_send_read(EzoBoard* board);
void ezo_send_cmd_with_num(EzoBoard* board, const char* cmd, float num, uint8_t decimals);
void ezo_send_read_with_temp(EzoBoard* board, float temperature);

// Receive
ezo_error_t ezo_receive_cmd(EzoBoard* board, char* buf, uint8_t len);
ezo_error_t ezo_receive_read(EzoBoard* board);

// Getters
bool ezo_is_read_poll(const EzoBoard* board);
float ezo_get_last_reading(const EzoBoard* board);
const char* ezo_get_name(const EzoBoard* board);
ezo_error_t ezo_get_error(const EzoBoard* board);
uint8_t ezo_get_address(const EzoBoard* board);

// Setters
void ezo_set_name(EzoBoard* board, const char* name);
void ezo_set_address(EzoBoard* board, uint8_t addr);

#endif // EZO_BOARD_H
