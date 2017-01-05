#include "params.h"
#include "bulb.h"

BulbPair bulb_pairs[MAX_BULB_NUM];

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
void oneCyclePwmCtrl(BulbPair *_bulb_pairs, float _first_duty, float _second_duty)
{
  int turn_off_second = LOOP_PERIOD_MICROS * _second_duty;
  int turn_off_first = LOOP_PERIOD_MICROS * _first_duty - turn_off_second;
  int last_wait = LOOP_PERIOD_MICROS - (turn_off_first + turn_off_second);

  for(int i = 0; i < MAX_BULB_NUM; i++)
  {
    if(_bulb_pairs[i].is_enabled())
    {
      digitalWrite(_bulb_pairs[i].first.getId(), HIGH);
      digitalWrite(_bulb_pairs[i].second.getId(), HIGH);
    }
  }

  selectedDelay(turn_off_second);

  for(int i = 0; i < MAX_BULB_NUM; i++)
  {
    if(_bulb_pairs[i].is_enabled())
    {
      digitalWrite(_bulb_pairs[i].second.getId(), LOW);
    }
  }

  selectedDelay(turn_off_first);

  for(int i = 0; i < MAX_BULB_NUM; i++)
  {
    if(_bulb_pairs[i].is_enabled()){
      digitalWrite(_bulb_pairs[i].first.getId(), LOW);
    }
  }

  selectedDelay(last_wait);
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
    bulb_pairs[0].first.row = row;
    bulb_pairs[0].first.col = col;

    row = random(ROW);
    col = random(COLUMN);
    bulb_pairs[0].second.row = row;
    bulb_pairs[0].second.col = col;

    bulb_pairs[0].spawn();

    int cnt = 0;

    while(1)
    {
      oneCyclePwmCtrl(bulb_pairs, duty_table[cnt], duty_table[cnt + DUTY_TABLE_SIZE / 2]);
      cnt++;
      if(cnt == DUTY_TABLE_SIZE / 2)
      {
        cnt = 0;
        bulb_pairs[0].gen();
      }
    }
  }
}
