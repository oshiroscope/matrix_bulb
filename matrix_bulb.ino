#include <MsTimer2.h>


#define BAUDRATE 115200
#define LOOP_PERIOD_MS 20
#define PWM_CTRL_PERIOD 1

#define MAX_BULB_NUM 5

#define ROW 5
#define COLUMN 8

int id[MAX_BULB_NUM];
int duty[MAX_BULB_NUM];

// duty : 0 ~ LOOP_PERIOD_MS
void pwmCtrl()
{
    static int cnt = 0;

    for(int i = 0; i < MAX_BULB_NUM; i++)
    {
        if(cnt < duty[i])
        {
            digitalWrite(id[i], HIGH);
        }
        else
        {
            digitalWrite(id[i], LOW);
        }
    }

    cnt++;
    if(cnt == LOOP_PERIOD_MS)
        cnt = 0;
}

void setup() {
    Serial.begin(BAUDRATE);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    id[0] = 2;
    id[1] = 3;
    id[2] = 4;
    id[3] = 5;
    id[4] = 6;

    duty[0] = 0;
    duty[1] = 3;
    duty[2] = 8;
    duty[3] = 15;
    duty[4] = 20;

    MsTimer2::set(PWM_CTRL_PERIOD, pwmCtrl);
    MsTimer2::start();
  //TODO setup GPIO
}

void loop() {
}
