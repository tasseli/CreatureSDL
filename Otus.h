#ifndef OTUS_H_INCLUDED // ifndef-viidakkoni tarkoitus on t‰ll‰ hetkell‰ olla ylivarovainen, katsoa ett‰ joka headeria
#define OTUS_H_INCLUDED // pyydet‰‰n kaikkialla miss‰ sit‰ haluttais k‰ytt‰‰, ja omat headerini on robusteja kutsumiselle mist‰ vain.

#include <SDL/SDL.h>    // n‰ytet‰‰n helppoa grafiikkaa
#include <vector>
#include <cstddef>

#include "const.h"


using namespace std;

class Otus//: public Maailma
{
public:
  float r, g, b;                      // fenotyyppi: n‰kyv‰, muuttuva ominaisuus
  float r_gen, g_gen, b_gen;                  // genotyyppi: otukseen koodattu, muuttumaton ominaisuus
  float r_askel, g_askel, b_askel;// paljonko relatessa palautetaan v‰ri‰ kerralla
  //    int nopeus[2] { }; // suunta, vauhti
  coordinates myCoord;
  int maailma_ID;
  //    int ika = 0;
  //    bool laheiset[OTUKSIAMAX] = { };      // koitan koodata t‰n ulos
  int himoittu;                        // jos asetettu, tahtoo paritella t‰m‰n j‰rkk‰nron kanssa
//  int omaJarjestysNro;
  int lisaantymiseenAikaa = ALKUUN_ILMAN;   // selibaatin kesto, askelia

  Otus (float r, float g, float b, int x, int y);   // m‰‰r‰‰ v‰ri

/*  void tunnustele(vector<Otus>*);
  Otus parittele(Otus);

  void horny();           // ilmaise tunnetilaasi v‰rj‰ytym‰ll‰ keltaiseksi
  void freak();           // ilmaise itse‰si v‰rj‰ytym‰ll‰ siniseksi
  void relax();           // relaa hieman, siirry innostuksesta kohti normaalitilaa
  float kohtiOmaaVaria(float vari, float normaalivari, char varinNimi);     // hoida siirtym‰ viksuna askelena normaalitilaa kohden
*/
/*
  bool voikoLaskea();
  bool voikoNousta();
  bool voikoVasen();
  bool voikoOikea();
  */
//  void liiku(Maailma& maailma, int, int);

};

#endif // OTUS_H_INCLUDED
