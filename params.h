#pragma once

#define BAUDRATE 115200
#define LOOP_PERIOD_MS 20
#define LOOP_PERIOD_MICROS 20000

#define MAX_BULB_NUM 5

#define LIFESPAN 5

#define ROW 3
#define COLUMN 10

#define DUTY_TABLE_SIZE 500

extern float duty_table[DUTY_TABLE_SIZE];
