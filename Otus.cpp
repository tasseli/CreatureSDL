#include "Otus.h"

int Otus::birthCounter = 0; // staticin alustus! Ei classiin.

Otus::Otus (rgb RGBgenome_, coordinates whereTo) {
  myCoord.x = whereTo.x;
  myCoord.y = whereTo.y;
  RGBfenotype = RGBgenome = RGBgenome_;
//  r_askel = g_askel = b_askel = 0;      // tulevat tarpeelliseks kun implementoidaan fenotyyppi
  birthNumber = birthCounter++;
}

short* Otus::outRGB() {
  short* rgb = new short[3];
  rgb[0] = RGBgenome.r;
  std::cout << "Otus.cpp: " << RGBgenome.r << rgb[0] ;
  rgb[1] = RGBgenome.g;
  std::cout << RGBgenome.g << rgb[1] ;
  rgb[2] = RGBgenome.b;
  std::cout << RGBgenome.b << rgb[2] << std::endl;
  return rgb;
}


void Otus::horny() { // muututaan keltaiseksi (Otuksien syntyvärit on kirjoittaessani punasävyisiä)
  RGBfenotype.r =255;
  RGBfenotype.g =255;
  RGBfenotype.b =0;
}

void Otus::freak() { // muututaan siniseksi (Otuksien syntyvärit on kirjoittaessani punasävyisiä)
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
  if (abs(colorNow - normalColor)<TARKKUUS || abs(colorNow - normalColor)<returnStep) {
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


