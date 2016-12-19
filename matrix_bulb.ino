#define BAUDRATE 115200
#define LOOP_PERIOD_MS 20
#define LOOP_PERIOD_MICROS 20000

#define MAX_BULB_NUM 5

#define ROW 5
#define COLUMN 8

int ids[MAX_BULB_NUM];


// duty : 0.0 ~ 1.0
void oneCyclePwmCtrl(int *_ids, int _num, float _duty)
{
  int time_on = LOOP_PERIOD_MICROS * _duty;
  int time_off = LOOP_PERIOD_MICROS - time_on;
  if(time_on > 0){
    for(int i = 0; i < _num; i++)
    {
      digitalWrite(_ids[i], HIGH);
    }
    delayMicroseconds(time_on);
    for(int i = 0; i < _num; i++)
    {
      digitalWrite(_ids[i], LOW);
    }
    delayMicroseconds(time_off);
  }
}

void setup() {
  Serial.begin(BAUDRATE);
  randomSeed(analogRead(0));

  //TODO setup GPIO
}

void loop() {
  //if(sensor){
  if(true){
    int row = random(ROW);
    int column = random(COLUMN);

  }

}
