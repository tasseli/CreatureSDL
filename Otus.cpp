#include <iomanip>
#include <fstream>
#include "Otus.h"
using std::setfill;
using std::setw;

int Otus::birthCounter = 0; // staticin alustus! Ei classiin.

Otus::Otus (rgb RGBgenome_, coordinates whereTo) {
  ofstream myfile;                // out-file-streamiasia
  myfile.open("otuslogi.txt", ios::app);   // logataan kuulumisia kuten sijaintia
  myCoord.x = whereTo.x;
  myCoord.y = whereTo.y;
  RGBfenotype = RGBgenome = RGBgenome_;
//  r_askel = g_askel = b_askel = 0;      // tulevat tarpeelliseks kun implementoidaan fenotyyppi
  birthNumber = birthCounter++;
  waitSex = WAIT_FIRST;
  isAlive = true;
  myfile << "Synnyin! Rgb ";
  myfile << std::setfill(' ') << std::setw(3) << RGBgenome_.r << ' ' << std::setw(3) << RGBgenome_.g << ' ' << std::setw(3) << RGBgenome_.b ;
  myfile << ", xy " << std::setw(3) << whereTo.x << " " << std::setw(3) << whereTo.y << std::endl;
  myfile.close();
}

void Otus::horny() { // muututaan keltaiseksi (Otuksien syntyv�rit on kirjoittaessani punas�vyisi�)
  RGBfenotype.r =255;
  RGBfenotype.g =255;
  RGBfenotype.b =0;
}

void Otus::freak() { // muututaan siniseksi (Otuksien syntyv�rit on kirjoittaessani punas�vyisi�)
  RGBfenotype.r =0;
  RGBfenotype.g =0;
  RGBfenotype.b =255;
}

void Otus::relax() {  // fenotyypin implementaatiota
  if (RGBfenotype.r!=RGBgenome.r) {
    RGBfenotype.r = towardsOwnColor(RGBfenotype.r, RGBgenome.r);
  }
  if (RGBfenotype.g!=RGBgenome.g) {
    RGBfenotype.g = towardsOwnColor(RGBfenotype.g, RGBgenome.g);
  }
  if (RGBfenotype.b!=RGBgenome.b) {
    RGBfenotype.b = towardsOwnColor(RGBfenotype.b, RGBgenome.b);
  }
}

int Otus::towardsOwnColor(int colorNow, int normalColor) {  // fenotyypin implementaatiota
  int returnStep = 25;
  if (abs(colorNow - normalColor)<GRAPH_ACCURACY || abs(colorNow - normalColor)<returnStep) {
    return normalColor;
  }
  else {
    if(colorNow<normalColor) {
      return colorNow += returnStep;
    }
    else {
      return colorNow -= returnStep;
    }
  }
}


