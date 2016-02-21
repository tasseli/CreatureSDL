#include "loopProgram.h"

using namespace std;

bool loopProgram() {
  // Logi
  ofstream myfile;                // out-file-streamiasia
  myfile.open("otuslogi.txt");   // logataan kuulumisia kuten sijaintia
  srand(time(0));                 // rand():in seedaus erolla nollakellonlyömään

  // SDL init
  SDL_Surface *petrimalja = NULL;
  SDL_Event event;
  int keypress = 0;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;
  if (!(petrimalja = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE))) {   //Asetettu Critter.h:ssa
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
//      if(SDL_MUSTLOCK(petrimalja)) SDL_UnlockSurface(petrimalja);
//      SDL_Flip(petrimalja);

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
  myfile.close();
  SDL_Quit();
  return 0;
}


