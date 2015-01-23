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
    coordinates findEmptyNeighbor(coordinates toThis);
    coordinates getCoords(int birthNumber);
    void moveCreature (Otus* moved);
/*    int feelAround(int bithNumber_);*/  // returns the birthNumber of the first copulateable spouce-to-be near creature #birthNumber_
    Otus* feelAround(Otus* feeler);
    void copulate(Otus* mother);

    /*void findAllProcreators();        // katsoo l‰pi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin
    Otus* checkProcreatingAbility();  // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL*/
    vector<vector<Otus*> > creatures; // sis‰lt‰‰ pointterit kaikkiin Maailman Otuksiin (st‰ckiss‰). Solu t‰ynn‰ tai NULL.
    vector<Otus*> creaturesByBirth;   // pointterit samoihin luomisj‰rjestyksess‰.
    int heightSize, widthSize;
    int creaturesAliveSum;
};

#endif // MAAILMA_H
