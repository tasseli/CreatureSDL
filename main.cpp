#include <SDL/SDL.h>    // n‰ytet‰‰n helppoa grafiikkaa
#include <vector>       // tehd‰‰n otuksista joustavan kokoinen taulukko
#include <time.h>       // k‰ytet‰‰n kelloa rand()in seedin‰

#include "Otus.h"       // oma otukseni
#include "grafiikka.h"  // esimerkkisivulta kopioitu ja muokattu grafiikkarutiini

// basic file operations
#include <iostream>
#include <fstream>

//#include <iostream>   // ei viel‰ tarvetta
//#include <stdio.h>    // ei viel‰ tarvetta


using namespace std;


/*****

// TODO k‰ytet‰‰n maailma.petriDishi‰ eik‰ maailmanOtuksia. <3

  T‰ss‰ vaiheessa piirret‰‰n 640x480 -kokoinen valkoinen petrimalja. Sen keskelt‰ aloittaa OTUKSIA_ALUSSA:n mukainen m‰‰r‰ Otuksia,
  jotka ovat syntyess‰‰n punas‰vyisi‰. Otukset havainnoivat samalle kohdalle sattuneita lajitovereitaan, ja pyrkiv‰t parittelemaan
  vieh‰tt‰vimm‰n kanssa. Onnistunut lis‰‰ntyminen saa otuksen friikkaamaan (muuttumaan siniseksi), ja lis‰‰ntymiseen johtamaton
  parittelu (OTUKSIAMAXin tultua t‰yteen) tekee ne hornyiksi (keltaisiksi). V‰ri palautuu otuksen PALAUDU-keston aikana sen omaksi.

  Otus perii v‰rins‰ v‰limuotona vanhemmiltaan.
  Otuksella on v‰ri ja koordinaatit, ja se liikkuu ~satunnaisesti. Reunalla otus p‰‰tt‰‰ olla kulkematta maljan sein‰n yli.
  Mainissa vuoroin piirret‰‰n, liikutellaan, tunnustellaan ja paritellaan otuksia. '1' lopettaa simulaation.
****/




int main(int argc, char* argv[]) {

   // Logi, SDL init
    ofstream myfile;                // out-file-streamiasia
    myfile.open("otuslogi.txt");   // logataan kuulumisia kuten sijaintia
    cout << "Avataan logi" << endl;

    srand(time(0));                 // rand():in seedaus erolla nollakellonlyˆm‰‰n
    SDL_Surface *petrimalja;            // SDL:n k‰yttˆ‰, jota en tarkemmin ymm‰rr‰
    SDL_Event event;

    int keypress = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    cout << "tsekattiin mit‰ SDL_Init sano" << endl;
    if (!(petrimalja = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE))) {   //Asetettu Otus.h:ssa - mut mit‰h‰n: SDL_FULLSCREEN| tekee. Ahaa. Flagit tulee |:illa eroteltuina vikaks.
      SDL_Quit();
      return 1;
    }
    cout << "tsekattiin mit‰ SDL_SetVideoMode sano" << endl;

// TODO k‰ytet‰‰n maailma.petriDishi‰ eik‰ maailmanOtuksia. <3
   // Otuksien alkusynty
    Maailma maailma(WIDTH,HEIGHT);               // petrimaljan data, sis. ison otuspointteritaulukon
    cout << "Maailma luotu" << endl;

    Otus* syntyva = NULL;
    maailma.creatures[320][241] = syntyva = new Otus(255,0,0,320,241);
    maailma.addToIndex(maailma.creatures[syntyva->myCoord.x][syntyva->myCoord.y]);
    cout << "Otus luotu" << endl;

    syntyva = NULL;
  //  maailmanOtukset.at(0).omaJarjestysNro = 0; // huolehditaan otuksia luodessa viel‰ j‰rkk‰nrosta k‰sin, jotta otukset tiet‰‰ olla parittelematta itsens‰ kanssa. TODO fiksummin
    myfile << "Otus[" << 0 << "]: synnyin! Arvoilla (rgb) (255,0,0) (xy) (320,241) \n";                      // t‰ll‰ kierroksella syntyneit‰

    for (int i=0+maailma.creatures_alive_sum; i<OTUKSIA_ALUSSA; i++) {
      int x_syntyva = (317+3*i)%WIDTH;
      int y_syntyva = (237+3*i)%HEIGHT;
      if (maailma.creatures[x_syntyva][y_syntyva]==NULL) {
        cout << "Oli NULL" << endl;
        maailma.creatures[x_syntyva][y_syntyva] = syntyva = new Otus((255-i)%256,(3+i)%256,0,x_syntyva,y_syntyva);     // lis‰otukset syntyy kulmittain vierekk‰in keskilinjalle punas‰vyisin‰
        maailma.addToIndex(maailma.creatures[x_syntyva][y_syntyva]);
        myfile << "Synnyin! Arvoilla (rgb) "<< syntyva->r << " " << syntyva->g << " " << syntyva->b <<" (xy) " << syntyva->myCoord.x << " " << syntyva->myCoord.y << " \n"; // t‰ll‰ kierroksella syntyneit‰
        cout << "Uus otus luotu" << endl;
      }
  //    maailmanOtukset.at(i+1).omaJarjestysNro = i+1; // tiedet‰‰n et yks on tehty aiemmin
      syntyva = NULL;
    }

  cout << "While-looppi alkamassa" << endl;

  while(!keypress) {  // Vars. looppi
    cout << "Drawscreen alkamassa" << endl;
    drawScreen(petrimalja, maailma);
    cout << "Drawscreen tehty" << endl;

    while(SDL_PollEvent(&event)) { // jos 1 painettu, loppu
      switch (event.type) {
        case SDL_QUIT:
        cout << "Case n‰ytt‰‰ SDL_QUITilta" << endl;
        keypress = 1;
        break;
        case SDL_KEYDOWN:
        cout << "Case n‰ytt‰‰ SDL_KEYDOWNilta" << endl;
        keypress = 1;
        break;
      }
    }
    cout << "SDL_Pollevent ohitettu" << endl;

    {   // Liikkumiset, latautumiset
      for(int i=0; i<(maailma.creatures_alive_sum); i++) {
        cout << "Liikutaan" << endl;
        maailma.liiku(i);    // maailman otukset, liikkukaa
        cout << "Liikuttu" << endl;

/*        if (*maailmanOtukset[i].lisaantymiseenAikaa >0) {    // kohta saatte lis‰‰nty‰ taas
          maailmanOtukset[i].lisaantymiseenAikaa--;
          maailmanOtukset[i].relax();
        }*/
      }

    }

//    maailma.findAllProcreators();

/*          maailmanOtukset[i].freak();
          myfile << "Otus[" << otuksetSizeAluksi+syntyneita << "]: synnyin! Arvoilla (rgb) "<< syntyva->r << " " << syntyva->g << " " << syntyva->b <<" (xy) " << syntyva->x << " " << syntyva->y << " \n"; // t‰ll‰ kierroksella syntyneit‰
          syntyneita++;*/

//         if (!syntyva) cout << "ei syntyv‰‰" << endl;


  }
  cout << "while p‰‰ttyi" << endl;
  myfile.close();
  SDL_Quit();
  cout << "close ja quit tehty" << endl;

  return 0;
}
