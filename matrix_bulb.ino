#include <TimerOne.h>
#include <MsTimer2.h>


#define BAUDRATE 115200
#define LOOP_PERIOD_MS 20
#define PWM_CTRL_PERIOD 1
#define LIGHT_CTRL_PERIOD_MICROS 500000

#define MAX_BULB_NUM 30
#define INITIAL_ID 2

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

void lightCtrl()
{
    for(int i = INITIAL_ID; i < INITIAL_ID + MAX_BULB_NUM; i++)
    {
        duty[i - INITIAL_ID] = random(0, LOOP_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(BAUDRATE);
    randomSeed(analogRead(0));

    for(int i = INITIAL_ID; i < INITIAL_ID + MAX_BULB_NUM; i++)
    {
        pinMode(i, OUTPUT);
        id[i - INITIAL_ID] = i;
        duty[i - INITIAL_ID] = random(0, LOOP_PERIOD_MS);
    }

    Timer1.initialize(LIGHT_CTRL_PERIOD_MICROS);
    Timer1.attachInterrupt(lightCtrl);

    MsTimer2::set(PWM_CTRL_PERIOD, pwmCtrl);
    //MsTimer2::set(LIGHT_CTRL_PERIOD, lightCtrl);
    MsTimer2::start();
  //TODO setup GPIO
}

void loop() {
}
