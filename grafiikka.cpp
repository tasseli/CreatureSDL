#include <SDL/SDL.h>

#include <vector>

#include "Otus.h"
#include "grafiikka.h"

//#include <iostream>   // varmaan inputoutputtia?
//#include <stdio.h>    // varmaan inputoutputtia?
//#include <time.h>       // k‰ytet‰‰n kelloa rand()in seedin‰
//#include <vector>       // luodaan Otuksista dynaaminen lista


using namespace std;

//#include grafiikka.h

void setPixel(SDL_Surface *s, coordinates coords, rgb color) {
  int *scr = (int*)s->pixels;
  if ((coords.x >= 0) && (coords.x < s->w) && (coords.y >= 0) && (coords.y < s->h)) // SDL_Surface on constructi jolla on w ja h. Jos x ja y on nollien ja w:n ja h:n v‰liss‰ eli Surfacen alueella..
    scr[coords.x + coords.y*s->w] = SDL_MapRGB(s->format, color.r, color.g, color.b); // Red, Green, Blue   .. mappaa v‰ri x:n ja y:n fiksusti m‰‰r‰‰m‰lle pixelille.
}

void drawScreen(SDL_Surface *petrimalja, Maailma& maailma) { // piirret‰‰n petrimalja, ja sitten joka otus vuorollaan sen p‰‰lle
  int x, y;

  if(SDL_MUSTLOCK(petrimalja)) {
    if(SDL_LockSurface(petrimalja) < 0) return;
  }

  for(y = (petrimalja->h-1); y > -1; y-- ) {// Alustetaan petrimalta, Otusten alusta eli screeni, valkoiseksi
    for( x = 0; x < petrimalja->w; x++ ) {
      setPixel(petrimalja, coordinates{x, y}, rgb{255, 255, 255});
    }
  }
/*
  if (maailma.creatures_alive_sum>0)   // piirret‰‰n joka otus maljan p‰‰lle
  {
    for (int i = maailma.creatures_alive_sum; i>0; i-- ) {
      coordinates c = maailma.giveCoordinates(i);
      setPixel(petrimalja, c.x, (int)petrimalja->h-1-c.y, maailma.creatures[c.x][c.y]->r, maailma.creatures[c.x][c.y]->g, maailma.creatures[c.x][c.y]->b);
    }
  }
*/

  if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);

  SDL_Flip(petrimalja);
}
