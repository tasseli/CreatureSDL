#ifndef MAAILMA_H
#define MAAILMA_H

#include <vector>
#include <cstddef>

#include "Otus.h"
#include "const.h"

using namespace std;


class Maailma {
public:
    Maailma(int width,int height);
    bool createCreature(Otus* mother, Otus* father);
    bool createCreature(coordinates whereTo);
    bool createCreature(rgb genome, coordinates whereTo);
    bool nextTo(coordinates myCoords, coordinates herCoords);
    bool withinBounds(coordinates c);
    void breathe(Otus* breather);
    coordinates findEmptyNeighbor(coordinates toThis);
    coordinates findNeighbor(coordinates toThis);
    void moveCreature (Otus* moved);
    Otus* feelAround(Otus* feeler);
    void copulate(Otus* mother);
    /*void findAllProcreators();        // katsoo l‰pi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin
    Otus* checkProcreatingAbility();  // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL*/
    vector<vector<Otus*> > creatures; // sis‰lt‰‰ pointterit kaikkiin Maailman Otuksiin (st‰ckiss‰). Solu t‰ynn‰ tai NULL.
    vector<Otus*> creaturesByBirth;   // pointterit samoihin luomisj‰rjestyksess‰.
};

#endif // MAAILMA_H
