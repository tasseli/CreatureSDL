#include "graphics.h"

using namespace std;

void setPixel(SDL_Surface *s, coordinates coords, rgb color) {                        // Color a pixel: SDL_Surface on constructi jolla on w ja h.
  int *scr = (int*)s->pixels;
  if ((coords.x >= 0) && (coords.x < s->w) && (coords.y >= 0) && (coords.y < s->h))   // Jos piirrett‰v‰ pikseli on nollien ja w:n ja h:n v‰liss‰ eli Surfacen alueella..
    scr[coords.x + coords.y*s->w] = SDL_MapRGB(s->format, color.r, color.g, color.b); // .. mappaa v‰ri x:n ja y:n fiksusti m‰‰r‰‰m‰lle pixelille.
}

void drawBackground(SDL_Surface *petrimalja) {
  int x, y;
  if(SDL_MUSTLOCK(petrimalja)) {                                                      // "Use this function to determine whether a surface must be locked for access."
    if(SDL_LockSurface(petrimalja) < 0) return;                                       // Meaning: Lock if I must.
  }
  for(y = (petrimalja->h-1); y > -1; y-- ) {                                          // Initialize dish white pixel by pixel
    for( x = 0; x < petrimalja->w; x++ ) {                                            // Todo: faster way with blit?
      setPixel(petrimalja, coordinates(x, y), rgb(255, 255, 255));
    }
  }
}

void drawCritters(SDL_Surface *petrimalja, World& maailma) {                          // If critters exist, draw each on top of white dish
  if(SDL_MUSTLOCK(petrimalja)) {
    if(SDL_LockSurface(petrimalja) < 0) return;                                       // Lock if I must
  }
  if (maailma.creaturesByBirth.size()>0) {
    for (int i = maailma.creaturesByBirth.size()-1; i>-1; i-- ) {
      setPixel(petrimalja, coordinates{maailma.creaturesByBirth[i]->myCoord.x, (petrimalja->h-1-maailma.creaturesByBirth[i]->myCoord.y)},
               rgb{maailma.creaturesByBirth[i]->RGBfenotype.r, maailma.creaturesByBirth[i]->RGBfenotype.g, maailma.creaturesByBirth[i]->RGBfenotype.b});
    }
  }
}

void drawEmptied(SDL_Surface *petrimalja, World& maailma) {                           // TODO: potential worms' nest, use a day to work around.
  if (CLEAN_AFTER_MOVE == true) {
    if(SDL_MUSTLOCK(petrimalja)) {
      if(SDL_LockSurface(petrimalja) < 0) return;
    }
    if (maailma.creaturesJustMoved.size()>0) {                                        // piirret‰‰n liikkuneiden paikoille valkeat
      for (int i = maailma.creaturesJustMoved.size()-1; i>-1; i-- ) {
        coordinates c = maailma.creaturesJustMoved[i];
        coordinates coords_(c.x, (petrimalja->h-1-c.y));                              //(petrimalja->h-1-c.y)
        rgb rgb_(255, 255, 255);
        setPixel(petrimalja, coords_, rgb_);
      }
    }
  }
}
