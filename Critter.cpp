#include "Critter.h"

using std::setfill;
using std::setw;

int Critter::birthCounter = 0; // staticin alustus! Ei classiin.

Critter::Critter (rgb RGBgenome_, coordinates whereTo) : RGBfenotype{RGBgenome_}, RGBgenome{RGBgenome_}, myCoord{whereTo} {
//  r_askel = g_askel = b_askel = 0;      // tulevat tarpeelliseks kun implementoidaan fenotyyppi
  birthNumber = birthCounter++;

  ofstream myfile;                // out-file-streamiasia
  myfile.open("CritterLog.txt", ios::app);   // logataan kuulumisia kuten sijaintia
  myfile << "I'm born! Rgb ";
  myfile << std::setfill(' ') << std::setw(3) << RGBgenome_.r << ' ' << std::setw(3) << RGBgenome_.g << ' ' << std::setw(3) << RGBgenome_.b ;
  myfile << ", xy " << std::setw(3) << whereTo.x << " " << std::setw(3) << whereTo.y << std::endl;
  myfile.close();
}

void Critter::horny() { // muututaan keltaiseksi (Otuksien syntyvärit on kirjoittaessani punasävyisiä)
  RGBfenotype.r = 255, RGBfenotype.g = 255, RGBfenotype.b = 0;
}

void Critter::freak() { // muututaan siniseksi (Otuksien syntyvärit on kirjoittaessani punasävyisiä)
  RGBfenotype.r = 0, RGBfenotype.g = 0, RGBfenotype.b = 255;
}

void Critter::relax() {  // fenotyypin implementaatiota
  if (RGBfenotype.r!=RGBgenome.r)
    RGBfenotype.r = towardsOwnColor(RGBfenotype.r, RGBgenome.r);
  if (RGBfenotype.g!=RGBgenome.g)
    RGBfenotype.g = towardsOwnColor(RGBfenotype.g, RGBgenome.g);
  if (RGBfenotype.b!=RGBgenome.b)
    RGBfenotype.b = towardsOwnColor(RGBfenotype.b, RGBgenome.b);
}

int Critter::towardsOwnColor(int colorNow, int normalColor) {  // fenotyypin implementaatiota
  int returnStep = 25;
  if (abs(colorNow - normalColor)<GRAPH_ACCURACY || abs(colorNow - normalColor)<returnStep)
    return normalColor;
  else {
    if(colorNow<normalColor)
      return colorNow += returnStep;
    else
      return colorNow -= returnStep;
  }
}


