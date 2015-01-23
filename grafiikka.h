#pragma once

class Otus;

#include <SDL/SDL.h>
#include <vector>

#include "Maailma.h"

using namespace std;

void setPixel(SDL_Surface*, int, int, int, int, int);

void drawScreen(SDL_Surface*, Maailma& maailma);

