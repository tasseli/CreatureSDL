#include <SDL/SDL.h>    // n‰ytet‰‰n helppoa grafiikkaa
#include <vector>       // tehd‰‰n otuksista joustavan kokoinen taulukko
#include <time.h>       // k‰ytet‰‰n kelloa rand()in seedin‰

#include "Otus.h"       // oma otukseni
#include "grafiikka.h"  // esimerkkisivulta kopioitu ja muokattu grafiikkarutiini

#include <iostream>
#include <fstream>

using namespace std;


/*****

//
  Tavoite: piirret‰‰n 640x480 -kokoinen valkoinen petrimalja. Sen keskelt‰ aloittaa INIT_CREATURES:n mukainen m‰‰r‰ Otuksia,
  jotka ovat syntyess‰‰n punas‰vyisi‰. Otukset havainnoivat samalle kohdalle sattuneita lajitovereitaan, ja pyrkiv‰t parittelemaan
  vieh‰tt‰vimm‰n kanssa. Onnistunut lis‰‰ntyminen saa otuksen friikkaamaan (muuttumaan siniseksi), ja lis‰‰ntymiseen johtamaton
  parittelu (MAX_CREATURES tultua t‰yteen) tekee ne hornyiksi (keltaisiksi). V‰ri palautuu otuksen PALAUDU-keston aikana sen omaksi.

  Otus perii v‰rins‰ v‰limuotona vanhempiensa genomeista.
  Otuksella on v‰ri ja koordinaatit, ja se liikkuu ~satunnaisesti. Reunalla otus p‰‰tt‰‰ olla kulkematta maljan sein‰n yli.
  Mainissa vuoroin piirret‰‰n, liikutellaan, tunnustellaan ja paritellaan otuksia. '1' lopettaa simulaation.
****/


int main(int argc, char* argv[]) {

  // Logi, SDL init
  ofstream myfile;                // out-file-streamiasia
  myfile.open("otuslogi.txt");   // logataan kuulumisia kuten sijaintia
  srand(time(0));                 // rand():in seedaus erolla nollakellonlyˆm‰‰n
  SDL_Surface *petrimalja;            // SDL:n k‰yttˆ‰, jota en tarkemmin ymm‰rr‰
  SDL_Event event;
  int keypress = 0;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
  if (!(petrimalja = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE))) {   //Asetettu Otus.h:ssa - mut mit‰h‰n: SDL_FULLSCREEN| tekee. Ahaa. Flagit tulee |:illa eroteltuina vikaks.
    SDL_Quit();
    return 1;
  }

  // Otuksien alkusynty
  Maailma maailma(WIDTH,HEIGHT);

  // luodaan otukset
  for (int i=maailma.creaturesByBirth.size(); i<INIT_CREATURES; i++) {
    int x_syntyva = (317+3*i)%WIDTH;
    int y_syntyva = (237+3*i)%HEIGHT;
    if (maailma.creatures[x_syntyva][y_syntyva]==NULL) {
      bool hmm = maailma.createCreature(rgb{(255-i)%256,(3+i)%256,0},coordinates{x_syntyva,y_syntyva});
      myfile << "Uus otus luotu" << endl;
    }
  }

  while(!keypress) {  // Vars. looppi kunnes keskeytet‰‰n napilla
    for( int colorCounter = 0; colorCounter<10; ++colorCounter) { // hoidetaan relax()it joka 10. ticki
      drawScreen(petrimalja, maailma);
      while(SDL_PollEvent(&event)) { // jos 1 painettu, loppu
        switch (event.type) {
          case SDL_QUIT:
          myfile << "Case n‰ytt‰‰ SDL_QUITilta" << endl;
          keypress = 1;
          break;
          case SDL_KEYDOWN:
          myfile << "Case n‰ytt‰‰ SDL_KEYDOWNilta" << endl;
          keypress = 1;
          break;
        }
      }
      // Liikkumiset, latautumiset
      for(int i=0; i<maailma.creaturesByBirth.size(); i++) {
        maailma.moveCreature(maailma.creaturesByBirth[i]);
        if(maailma.creaturesByBirth[i]->waitSex>=1) {
          --maailma.creaturesByBirth[i]->waitSex;
        }
      }
      // Parittelut
      int bz = maailma.creaturesByBirth.size();
      for(int i=0; i<bz; i++) {
        maailma.copulate(maailma.creaturesByBirth[i]);
      }
      // V‰rien palauttelu genotyyppi‰ kohti
      if( colorCounter%10 == 9) {
        for(int i=0; i<maailma.creaturesByBirth.size(); i++) {
          maailma.creaturesByBirth[i]->relax();
        }
      }
    }
  }
  myfile << "while p‰‰ttyi" << endl;
  myfile.close();
  SDL_Quit();

  return 0;
}
