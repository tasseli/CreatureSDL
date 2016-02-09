#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>     // srand()
#include <time.h>       // seeding rand()
#include "SDL/SDL.h"    // show easy graphics

#include "Critter.h"       // my creatures <3
#include "graphics.h"  // graphic routines copied and edited


using namespace std;


/*****
  Aim: Draw a plate filled with n of INIT_CREATURES amount of Critters. They are red when born. They look around for other
  members for their species, and try to mate with the most interesting one. They freak() when managing this, which makes them
  blue temporarily. If they can't release themselves after finding a potential partner, they're horny() - turning yellow. for
  a while. MAX_CREATURES filling up will induce this.

  A Critter will inherit their color as a compromise of their parents' colors.
  A Critter has a genetic color, a temporary color (fenotype), and it moves ~randomly. It avoids crossing borders of its world.
  In main() the turn alternates among moving, feeling and mating. '1' ends the simulation.
*****/


int main(int argc, char* argv[]) {

  // Logi, SDL init
  ofstream myfile;                // out-file-streamiasia
  myfile.open("otuslogi.txt");   // logataan kuulumisia kuten sijaintia
  srand(time(0));                 // rand():in seedaus erolla nollakellonlyömään
  SDL_Surface *petrimalja = NULL;            // SDL:n käyttöä, jota en tarkemmin ymmärrä
  SDL_Event event;
  int keypress = 0;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;
  if (!(petrimalja = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE))) {   //Asetettu Critter.h:ssa - mut mitähän: SDL_FULLSCREEN| tekee. Ahaa. Flagit tulee |:illa eroteltuina vikaks.
    SDL_Quit();
    return 1;
  }

  // Otuksien alkusynty
  World maailma(WIDTH,HEIGHT);

  drawBackground(petrimalja);
  if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
  SDL_Flip(petrimalja);


  while(!keypress) {  // Vars. looppi kunnes keskeytetään napilla
    for( int colorCounter = 0; colorCounter<10; ++colorCounter) { // hoidetaan relax()it joka 10. ticki
      drawEmptied(petrimalja, maailma);
      if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
      SDL_Flip(petrimalja);

      drawCritters(petrimalja, maailma);
      if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
      SDL_Flip(petrimalja);

      while(SDL_PollEvent(&event)) { // jos 1 painettu, loppu
        switch (event.type) {
          case SDL_QUIT:
          keypress = 1;
          break;
          case SDL_KEYDOWN:
          keypress = 1;
          break;
        }
      }
      maailma.step(colorCounter);
    }
  }
//  myfile << "while päättyi" << endl;
  myfile.close();
  SDL_Quit();

  return 0;
}
