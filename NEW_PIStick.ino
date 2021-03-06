#include "LedControl.h"
#include <cppQueue.h>
void setup()
{
  randomSeed(analogRead(0));

  struct Position
  {
    int row;
    int col;
  };

  Position newHead {3, 3};

  Queue body(sizeof(newHead), 32, FIFO);

  Position one{1, 1};
  Position two{2, 2};
  Position three{3, 3};

  body.push(&one);
  body.push(&two);
  body.push(&three);


  LedControl display = LedControl(8, 12, 10, 4); //pin 12 is connected to the DataIn, pin 11 is connected to the CLK, pin 10 is connected to LOAD
  int x = 1;
  int y = 1;
  int command;
  int dataX = 0;
  int dataY = 0;
  Position * dequePoint;
  int appleX;
  int appleY;
  int snakeLength = 3;
  for (int address = 0; address < 4; address++)  //The MAX72XX is in power-saving mode on startup
  {
    display.shutdown(address, false);
    display.setIntensity(address, 1);
    display.clearDisplay(address);
  }

  bool eatenApple = true;
  while (true)
  {
    if (eatenApple)
    {
      appleX = random(32);
      appleY = random(8);
      eatenApple = false;
    }
    if (appleX > 7)
    {
      display.setLed(3 - (appleX / 8), appleY, appleX % 8, true);
    }
    else
    {
      display.setLed(3, appleY, appleX, true);
    }
    delay(140);

    dataX = analogRead(A2);
    dataY = analogRead(A4);
    if (dataX < 200)
    {
      x = -1;
    }
    else if (dataX > 600)
    {
      x = 1;
    }
    else
    {
      x = 0;
    }
    if (dataY < 200)
    {
      y = -1;
    }
    else if (dataY > 600)
    {
      y = 1;
    }
    else
    {
      y = 0;
    }

    if (y == -1)
    {
      newHead.row = -1;
    }
    else if (y == 1)
    {
      newHead.row = 1;
    }
    else
    {
      newHead.row = 0;
    }
    if (x == -1)
    {
      newHead.col = -1;
    }
    else if (x == 1)
    {
      newHead.col = 1;
    }
    else
    {
      newHead.col = 0;
    }


    display.clearDisplay();
    Position currentPoint{0, 0};
    for (int i = 0; i < snakeLength ; i++)
    {
      body.pop(&currentPoint);
      if (currentPoint.col > 7)
      {
        display.setLed(3 - (currentPoint.col / 8), currentPoint.row, currentPoint.col % 8, true);
      }
      else
      {
        display.setLed(3, currentPoint.row, currentPoint.col, true);
      }

      body.push(&currentPoint);
    }
    int newRow = currentPoint.row + newHead.row;
    int newCol = currentPoint.col + newHead.col;

    if (newRow > 7) newRow = 0;
    if (newRow < 0) newRow = 7;
    if (newCol > 31) newCol = 0;
    if (newCol < 0) newCol = 31;



    Position * newH = (Position*)malloc(sizeof(Position));
    newH->row = newRow;
    newH->col = newCol;
    if (!(newHead.row == 0 && newHead.col == 0))
    {
      body.push(newH);
      if (!(appleX == newCol && appleY == newRow))
      {
        body.pop(&dequePoint);
      }
      else
      {
        snakeLength++;
        eatenApple = true;
      }


    }
    //free(dequePoint->row);
    // free(dequePoint->col);

    delay(50);

  }
}

void loop()
{

}
