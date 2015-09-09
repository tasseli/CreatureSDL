#pragma once

class Otus;

#include <vector>
#include "SDL/SDL.h"
#include "Maailma.h"
#include "Otus.h"
#include "const.h"

using namespace std;

void setPixel(SDL_Surface*, coordinates coords_, rgb rgb_);

void drawBackground(SDL_Surface*);
void drawCreatures (SDL_Surface*, Maailma& maailma);
void drawEmptied   (SDL_Surface*, Maailma& maailma);

