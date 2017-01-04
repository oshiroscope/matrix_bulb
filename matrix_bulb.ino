#define BAUDRATE 115200
#define LOOP_PERIOD_MS 20
#define LOOP_PERIOD_MICROS 20000

#define MAX_BULB_NUM 5

#define ROW 3
#define COLUMN 10

struct Pos
{
public:
  int col;
  int row;
};

int pos2Id(Pos pos)
{
  return pos.col + pos.row * COLUMN + 2;
}

Pos bulbs[MAX_BULB_NUM];

// duty : 0.0 ~ 1.0
void oneCyclePwmCtrl(Pos *_bulbs, int _num, float _duty)
{
  Serial.println(_duty);

  int time_on = LOOP_PERIOD_MICROS * _duty;
  int time_off = LOOP_PERIOD_MICROS - time_on;
  if(time_on > 0){
    for(int i = 0; i < _num; i++)
    {
      Serial.print(_bulbs[i].row);
      Serial.print("\t");
      Serial.print(_bulbs[i].col);
      Serial.print("\t");
      Serial.print(pos2Id(_bulbs[i]));
      Serial.println();

      digitalWrite(pos2Id(_bulbs[i]), HIGH);
    }
    //delayMicroseconds(time_on);
    delay(time_on / 1000);
    for(int i = 0; i < _num; i++)
    {
      digitalWrite(pos2Id(_bulbs[i]), LOW);
    }
    //delayMicroseconds(time_off);
    delay(time_off / 1000);
  }
}

void light(Pos *_bulbs, int _num)
{
  int cnt = 0;
  while(1)
  {
    oneCyclePwmCtrl(_bulbs, _num, 0.8);
    cnt++;
    if(cnt == 13)
    {
      break;
    }
  }
  cnt = 5;
  while(1)
  {
    int max_cnt = 400;
    oneCyclePwmCtrl(_bulbs, _num, 5 / (float)cnt);
    cnt++;
    if(cnt == max_cnt)
    {
      break;
    }
  }
  cnt = 0;
  while(1)
  {
    int max_cnt = 100;
    oneCyclePwmCtrl(_bulbs, _num, (5 / (float)400) * ((float)max_cnt - cnt) / max_cnt);
    cnt++;
    if(cnt == max_cnt)
    {
      break;
    }
  }

}

void setup() {
  Serial.begin(BAUDRATE);
  randomSeed(analogRead(0));

  for(int i = 0; i < COLUMN; i++)
  {
    for(int j = 0; j < ROW; j++)
    {
      Pos p;
      p.col = i;
      p.row = j;
      pinMode(pos2Id(p), OUTPUT);
    }
  }
}

void loop() {
  //if(sensor){
  if(true){
    int row = random(ROW);
    int column = random(COLUMN);
    bulbs[0].row = row;
    bulbs[0].col = column;
    light(bulbs, 1);
  }

}
