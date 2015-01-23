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

/*
void Otus::horny() { // muututaan keltaiseksi (Otuksien syntyvärit on kirjoittaessani punasävyisiä)
  r =255;
  g =255;
  b =0;
}

void Otus::freak() { // muututaan siniseksi (Otuksien syntyvärit on kirjoittaessani punasävyisiä)
  r =0;
  g =0;
  b =255;
}

void Otus::relax() {  // fenotyypin implementaatiota
  if (r!=r_gen) {
    r = kohtiOmaaVaria(r, r_gen, 'r');
  }
  if (g!=g_gen) {
    g = kohtiOmaaVaria(g, g_gen, 'g');
  }
  if (b!=b_gen) {
    b = kohtiOmaaVaria(b, b_gen, 'b');
  }
}

float Otus::kohtiOmaaVaria(float vari, float normaalivari, char varinNimi) {  // fenotyypin implementaatiota
  if (abs(vari - normaalivari)<TARKKUUS) {
    return normaalivari;
  }
  else {
    switch (varinNimi) {
    case 'r':
      if (r_askel == 0) {
        r_askel = (normaalivari-vari)/PALAUDU;
      }
      return (vari + r_askel);
      break;
    case 'g':
      if (g_askel == 0) {
        g_askel = (normaalivari-vari)/PALAUDU;
      }
      return (vari + g_askel);
      break;
    case 'b':
      if (b_askel == 0) {
        b_askel = (normaalivari-vari)/PALAUDU;
      }
      return (vari + b_askel);
      break;
    default:
      exit(11);
      break;
    }
  }
}
*/

