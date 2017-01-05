#include "params.h"

class Bulb
{
public:
  int col;
  int row;

  int getId()
  {
    return col + row * COLUMN + 2;
  }

  void setPos(int _row, int _col)
  {
    row = _row;
    col = _col;
  }

};

class BulbPair
{
public:
  BulbPair()
  {
    state = false;
  }

  Bulb first;
  Bulb second;

  void gen()
  {
    second = first;
    first.setPos(random(ROW), random(COLUMN));
  }

  void spawn()
  {
    state = true;
  }

  void kill()
  {
    state = false;
  }

  bool is_enabled()
  {
    return state;
  }

private:
  bool state;
};
