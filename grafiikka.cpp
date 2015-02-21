#include <SDL/SDL.h>
#include <vector>

#include "Otus.h"
#include "grafiikka.h"
#include "const.h"

//#include <time.h>       // k‰ytet‰‰n kelloa rand()in seedin‰

using namespace std;

void setPixel(SDL_Surface *s, coordinates coords, rgb color) {      //SDL_Surface on constructi jolla on w ja h.
  int *scr = (int*)s->pixels;
  if ((coords.x >= 0) && (coords.x < s->w) && (coords.y >= 0) && (coords.y < s->h)) // Jos piirrett‰v‰ pikseli on nollien ja w:n ja h:n v‰liss‰ eli Surfacen alueella..
    scr[coords.x + coords.y*s->w] = SDL_MapRGB(s->format, color.r, color.g, color.b); // .. mappaa v‰ri x:n ja y:n fiksusti m‰‰r‰‰m‰lle pixelille.
}

void drawBackground(SDL_Surface *petrimalja, Maailma& maailma) {
  int x, y;
  if(SDL_MUSTLOCK(petrimalja)) {
    if(SDL_LockSurface(petrimalja) < 0) return;
  }
  for(y = (petrimalja->h-1); y > -1; y-- ) {  // Alustetaan petrimalta, Otusten alusta eli screeni, valkoiseksi
    for( x = 0; x < petrimalja->w; x++ ) {
      setPixel(petrimalja, coordinates{x, y}, rgb{255, 255, 255});
    }
  }
  if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
  SDL_Flip(petrimalja);
}


void drawCreatures(SDL_Surface *petrimalja, Maailma& maailma) { // piirret‰‰n petrimalja, ja sitten joka otus vuorollaan sen p‰‰lle
  if(SDL_MUSTLOCK(petrimalja)) {
    if(SDL_LockSurface(petrimalja) < 0) return;
  }

  if (maailma.creaturesByBirth.size()>0) {    // piirret‰‰n joka otus maljan p‰‰lle
    for (int i = maailma.creaturesByBirth.size()-1; i>-1; i-- ) {
      coordinates c = maailma.creaturesByBirth[i]->myCoord;
      coordinates coords_(c.x, (petrimalja->h-1-c.y)); //(petrimalja->h-1-c.y)
      rgb rgb_(maailma.creaturesByBirth[i]->RGBfenotype.r, maailma.creaturesByBirth[i]->RGBfenotype.g, maailma.creaturesByBirth[i]->RGBfenotype.b);
      setPixel(petrimalja, coords_, rgb_);
    }
  }

  if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
  SDL_Flip(petrimalja);
}


void drawEmptied(SDL_Surface *petrimalja, Maailma& maailma) {
  if (CLEAN_AFTER_MOVE == true) {
    if(SDL_MUSTLOCK(petrimalja)) {
      if(SDL_LockSurface(petrimalja) < 0) return;
    }

    if (maailma.creaturesJustMoved.size()>0) {    // piirret‰‰n liikkuneiden paikoille valkeat
      for (int i = maailma.creaturesJustMoved.size()-1; i>-1; i-- ) {
        coordinates c = maailma.creaturesJustMoved[i];
        coordinates coords_(c.x, (petrimalja->h-1-c.y)); //(petrimalja->h-1-c.y)
        rgb rgb_(255, 255, 255);
        setPixel(petrimalja, coords_, rgb_);
      }
    }

    if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
    SDL_Flip(petrimalja);
  }
}
