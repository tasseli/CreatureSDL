#include "Otus.h"

Otus::Otus (float r_annettu, float g_annettu, float b_annettu, int x_annettu, int y_annettu) {
//    _x = xera; syntaksi jotenkin v�h�n eri... g
  myCoord.x = x_annettu;
  myCoord.y = y_annettu;
  r = r_gen = r_annettu;
  g = g_gen = g_annettu;
  b = b_gen = b_annettu;
  r_askel = g_askel = b_askel = 0;
//  himoittu = -1;
}
/*Otus::Otus (int x_annettu, int y_annettu) {

  r = r_gen = (Uint8)rand()%256; // arvotut v�rit.
  g = g_gen = (Uint8)rand()%256;
  b = b_gen = (Uint8)rand()%256;
  x = x_annettu;
  y = y_annettu;
  r_askel = g_askel = b_askel = 0;
  himoittu = -1;
}*/
/*
Otus::Otus () {
}*/
/*

void Otus::horny() { // muututaan keltaiseksi (Otuksien syntyv�rit on kirjoittaessani punas�vyisi�)
  r =255;
  g =255;
  b =0;
}

void Otus::freak() { // muututaan siniseksi (Otuksien syntyv�rit on kirjoittaessani punas�vyisi�)
  r =0;
  g =0;
  b =255;
}

void Otus::relax() {
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

float Otus::kohtiOmaaVaria(float vari, float normaalivari, char varinNimi) {
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

/*
bool Otus::voikoLaskea () {
  if (y < 1)
    return 0;
  else return 1;
} // onko petrimaljassa tilaa liikkua alas
bool Otus::voikoNousta () {
  if (y > (HEIGHT-1))
    return 0;
  else return 1;
} // voiko liikkua yl�s
bool Otus::voikoVasen ()  {
  if (x < 1)
    return 0;
  else return 1;
} // voiko liikkua vasemmalle
bool Otus::voikoOikea ()  {
  if (x > (WIDTH-1))
    return 0;
  else return 1;
} // voiko liikkua oikealle
*/
