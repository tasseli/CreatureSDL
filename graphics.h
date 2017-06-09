#pragma once

class Critter;

#include <vector>
#include "C:/SDL2-2.0.4/include/SDL.h"                                // show easy graphics
#include "World.h"
#include "Critter.h"
#include "const.h"

using namespace std;

void setPixel(SDL_Surface*, coordinates coords_, rgb rgb_);

void drawBackground(SDL_Surface*);
void drawCritters (SDL_Surface*, World& maailma);
void drawEmptied   (SDL_Surface*, World& maailma);

