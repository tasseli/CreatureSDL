#pragma once

class Otus;

#include <SDL/SDL.h>
//#undef main // int argc, char* argv[] needed in main()
#include <vector>

#include "Maailma.h"

using namespace std;

void setPixel(SDL_Surface*, int, int, int, int, int);

void drawScreen(SDL_Surface*, Maailma& maailma);

