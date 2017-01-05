#include "params.h"

#define BAUDRATE 115200
#define LOOP_PERIOD_MS 20
#define LOOP_PERIOD_MICROS 20000

#define MAX_BULB_NUM 5

#define ROW 3
#define COLUMN 10

enum BulbState
{
  OFF = 0,
  FIRST = 1,
  SECOND = 2
};

class Bulb
{
public:
  int col;
  int row;
  BulbState state;

  int getId()
  {
    return col + row * COLUMN + 2;
  }
};

Bulb bulbs[MAX_BULB_NUM];

void selectedDelay(int time)
{
  if(time < 16383)
  {
    delayMicroseconds(time);
  }
  else
  {
    delay(time / 1000);
  }
}

// duty : 0.0 ~ 1.0
void oneCyclePwmCtrl(Bulb *_bulbs, float _first_duty, float _second_duty)
{
  Serial.print(_first_duty); Serial.print("\t"); Serial.print(_second_duty); Serial.print("\t");
  int first_time_on = LOOP_PERIOD_MICROS * _first_duty;
  int first_time_off = LOOP_PERIOD_MICROS - first_time_on;

  int second_time_on = LOOP_PERIOD_MICROS * _second_duty;
  int second_time_off = LOOP_PERIOD_MICROS - second_time_on;

  Serial.print(first_time_on ); Serial.print("\t"); Serial.print(second_time_on); Serial.print("\t");
  Serial.print("\n");

  for(int i = 0; i < MAX_BULB_NUM; i++)
  {
    if(_bulbs[i].state != OFF)
    {
      digitalWrite(_bulbs[i].getId(), HIGH);
    }
    else
    {
      digitalWrite(_bulbs[i].getId(), LOW);
    }
  }

  selectedDelay(second_time_on);

  for(int i = 0; i < MAX_BULB_NUM; i++)
  {
    if(_bulbs[i].state == SECOND)
    {
      digitalWrite(_bulbs[i].getId(), LOW);
    }
  }

  selectedDelay(first_time_on - second_time_on);

  for(int i = 0; i < MAX_BULB_NUM; i++)
  {
    if(_bulbs[i].state == FIRST){
      digitalWrite(_bulbs[i].getId(), LOW);
    }
  }

  selectedDelay(first_time_off);
}

void setup() {
  Serial.begin(BAUDRATE);
  randomSeed(analogRead(0));

  for(int i = 0; i < COLUMN; i++)
  {
    for(int j = 0; j < ROW; j++)
    {
      Bulb b;
      b.col = i;
      b.row = j;
      pinMode(b.getId(), OUTPUT);
    }
  }
}

void loop() {
  //if(sensor){
  if(true){
    int row = random(ROW);
    int col = random(COLUMN);
    bulbs[0].row = row;
    bulbs[0].col = col;
    bulbs[0].state = FIRST;

    row = random(ROW);
    col = random(COLUMN);
    bulbs[1].row = row;
    bulbs[1].col = col;
    bulbs[1].state = SECOND;

    int cnt = 0;
    while(1)
    {
      while(1)
      {
        oneCyclePwmCtrl(bulbs, duty_table[cnt], duty_table[cnt + DUTY_TABLE_SIZE / 2]);
        cnt++;
        if(cnt == DUTY_TABLE_SIZE / 2)
        {
          cnt = 0;
          bulbs[0].state = SECOND;
          bulbs[1].state = FIRST;
          break;
        }
      }
      while(1)
      {
        oneCyclePwmCtrl(bulbs, duty_table[cnt], duty_table[cnt + DUTY_TABLE_SIZE / 2]);
        cnt++;
        if(cnt == DUTY_TABLE_SIZE / 2)
        {
          cnt = 0;
          bulbs[0].state = FIRST;
          bulbs[1].state = SECOND;
          break;
        }
      }
    }
  }
}
