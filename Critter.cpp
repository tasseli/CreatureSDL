#include "Critter.h"

using std::setfill;
using std::setw;

int Critter::birthCounter = 0;                                  // Initializing a static. Can't do in header.

Critter::Critter (rgb RGBgenome_, coordinates whereTo) : RGBfenotype{RGBgenome_}, RGBgenome{RGBgenome_}, myCoord{whereTo} {
  birthNumber = birthCounter++;

  ofstream myfile;                                              // out-file-stream thing
  myfile.open("CritterLog.txt", ios::app);                      // log location + births
  myfile << "I'm born! Rgb ";
  myfile << std::setfill(' ') << std::setw(3) << RGBgenome_.r << ' ' << std::setw(3) << RGBgenome_.g << ' ' << std::setw(3) << RGBgenome_.b ;
  myfile << ", xy " << std::setw(3) << whereTo.x << " " << std::setw(3) << whereTo.y << std::endl;
  myfile.close();
}

void Critter::horny() {                                         // yellow
  RGBfenotype.r = 255, RGBfenotype.g = 255, RGBfenotype.b = 0;
}

void Critter::freak() {                                         // blue
  RGBfenotype.r = 0, RGBfenotype.g = 0, RGBfenotype.b = 255;
}

void Critter::rot() {                                           // black
  RGBfenotype.r = 255, RGBfenotype.g = 255, RGBfenotype.b = 255;
}

void Critter::relax() {
  if (!MORTALITY == true || isAlive == true) {                  // should I take a step towards own color?
    if (RGBfenotype.r!=RGBgenome.r)
      RGBfenotype.r = towardsOwnColor(RGBfenotype.r, RGBgenome.r);
    if (RGBfenotype.g!=RGBgenome.g)
      RGBfenotype.g = towardsOwnColor(RGBfenotype.g, RGBgenome.g);
    if (RGBfenotype.b!=RGBgenome.b)
      RGBfenotype.b = towardsOwnColor(RGBfenotype.b, RGBgenome.b);
  }
}

int Critter::towardsOwnColor(int colorNow, int normalColor) {   // calculating the step
  if (abs(colorNow - normalColor)<COLOR_ACCURACY || abs(colorNow - normalColor)<RETURN_STEP)
    return normalColor;
  else {
    if(colorNow<normalColor)
      return colorNow += RETURN_STEP;
    else {
      return colorNow -= RETURN_STEP;
    }
  }
  throw "Nevermore! if-else was supposed to cover all cases in Critter::towardsOwnColor()"; // above if/else should always return a number.
  return 0;                                                     // remove if throw's removed.
}


