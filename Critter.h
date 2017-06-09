#pragma once

#include "C:/SDL2-2.0.4/include/SDL.h"                                // show easy graphics
#include <vector>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "const.h"


using namespace std;

class Critter
{
public:
  Critter (rgb RGBgenome_, coordinates whereTo);    // define color

  rgb RGBfenotype;                                  // fenotype: how it looks right now
  const rgb RGBgenome;                              // genotype: how it looks by inherited qualities - or "typically"
  coordinates myCoord;
  int birthNumber;
  static int birthCounter;
  int   waitSex{WAIT_FIRST};                        // how many moving steps celibacy lasts
  bool  isAlive{true};

  void horny();                                     // show how you feel by turning yellow
  void freak();                                     // show how you feel by turning blue
  void rot();                                       // show how you feel by turning black
  void relax();                                     // take a step towards "typical" (color)
  int towardsOwnColor(int color, int normalColor);  // calculate the step


};
