#pragma once

class Otus;

#include <SDL/SDL.h>
#include <vector>

#include "Maailma.h"

using namespace std;

void setPixel(SDL_Surface*, coordinates coords_, rgb rgb_);

void drawBackground(SDL_Surface*, Maailma& maailma);
void drawCreatures (SDL_Surface*, Maailma& maailma);
void drawEmptied   (SDL_Surface*, Maailma& maailma);

