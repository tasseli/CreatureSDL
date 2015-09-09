#pragma once

class Critter;

#include <vector>
#include "SDL/SDL.h"
#include "World.h"
#include "Critter.h"
#include "const.h"

using namespace std;

void setPixel(SDL_Surface*, coordinates coords_, rgb rgb_);

void drawBackground(SDL_Surface*);
void drawCritters (SDL_Surface*, World& maailma);
void drawEmptied   (SDL_Surface*, World& maailma);

