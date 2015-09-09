#ifndef CRITTER_H_INCLUDED // ifndef-viidakkoni tarkoitus on t‰ll‰ hetkell‰ olla ylivarovainen, katsoa ett‰ joka headeria
#define CRITTER_H_INCLUDED // pyydet‰‰n kaikkialla miss‰ sit‰ haluttais k‰ytt‰‰, ja omat headerini on robusteja kutsumiselle mist‰ vain.

#include "SDL/SDL.h"    // n‰ytet‰‰n helppoa graphicsa
#include <vector>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "const.h"


using namespace std;

class Critter
{
public:
  rgb RGBfenotype;                    // fenotyyppi: n‰kyv‰, muuttuva ominaisuus
  rgb RGBgenome;                      // genotyyppi: otukseen koodattu, muuttumaton ominaisuus
  coordinates myCoord;
  int birthNumber;
  static int birthCounter;
  int waitSex;                        // selibaatin kesto, askelia
  bool isAlive;

  Critter (rgb RGBgenome_, coordinates whereTo);   // m‰‰r‰‰ v‰ri

  void horny();           // ilmaise tunnetilaasi v‰rj‰ytym‰ll‰ keltaiseksi
  void freak();           // ilmaise itse‰si v‰rj‰ytym‰ll‰ siniseksi
  void relax();           // relaa hieman, siirry innostuksesta kohti normaalitilaa
  int towardsOwnColor(int color, int normalColor);     // hoida siirtym‰ viksuna askelena normaalitilaa kohden


};

#endif // CRITTER_H_INCLUDED
