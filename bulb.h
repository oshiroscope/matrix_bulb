#pragma once

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

enum BulbPairState
{
  DEAD = 0,
  SPAWNED,
  ALIVE,
  DYING
};

class BulbPair
{
public:
  BulbPair()
  {
    state = DEAD;
    life = 0;
  }

  Bulb first;
  Bulb second;

  void gen()
  {
    switch (state) {
      case DEAD:
        return;
      case SPAWNED:
        state = ALIVE;
        life++;
        break;
      case ALIVE:
        life++;
        if(life == LIFESPAN)
        {
          state = DYING;
        }
        break;
      case DYING:
        state = DEAD;
        life = 0;
        break;
    }
    second = first;
    int seed = random(8);
    int row, col;
    switch (seed)
    {
      case 0:
        row = second.row - 1;
        col = second.col - 1;
        break;
      case 1:
        row = second.row - 1;
        col = second.col;
        break;
      case 2:
        row = second.row - 1;
        col = second.col + 1;
        break;
      case 3:
        row = second.row;
        col = second.col - 1;
        break;
      case 4:
        row = second.row;
        col = second.col + 1;
        break;
      case 5:
        row = second.row + 1;
        col = second.col - 1;
        break;
      case 6:
        row = second.row + 1;
        col = second.col;
        break;
      case 7:
        row = second.row + 1;
        col = second.col + 1;
        break;
    }

    if(row <= -1)
    {
      row += 2;
    }
    else if(row >= ROW)
    {
      row -= 2;
    }

    if(col <= -1)
    {
      col += 2;
    }
    else if(col >= COLUMN)
    {
      col -= 2;
    }

    first.setPos(row, col);
  }

  void spawn()
  {
    first.setPos(random(ROW), random(COLUMN));
    state = SPAWNED;
  }

  void kill()
  {
    state = DYING;
  }

  BulbPairState getState()
  {
    return state;
  }

private:
  BulbPairState state;
  int life;

};
