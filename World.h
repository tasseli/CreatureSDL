#pragma once

#include <vector>
#include <cstddef>
#include <iostream>

#include "Critter.h"
#include "const.h"

using namespace std;


class World {
public:
    World(int width,int height);

    bool createCritter(Critter* mother, Critter* father);
    bool createCritter(coordinates whereTo);
    bool createCritter(rgb genome, coordinates whereTo);

    bool nextTo(coordinates myCoords, coordinates herCoords);
    bool withinBounds(coordinates c);

    void moveCritter (Critter* moved);
    void breathe(Critter* breather);
    coordinates findEmptyNeighbor(coordinates toThis);
    coordinates findNeighbor(coordinates toThis);

    void doInitialBirths();
    void doMoves();
    void doCopulations();
    void doColorChanges(int colorCounter);

    Critter* feelAround(Critter* feeler);
    void copulate(Critter* mother);

    void step(int colorCounter);

    vector<vector<Critter*> > creatures;      // sis‰lt‰‰ pointterit kaikkiin Worldn Otuksiin (st‰ckiss‰). Solu t‰ynn‰ tai NULL.
    vector<Critter*> creaturesByBirth;        // pointterit samoihin luomisj‰rjestyksess‰.
    vector<coordinates> creaturesJustMoved;   // TODO: I feel bad for doing this
    int creaturesAlive{0};
};

    /*void findAllProcreators();              // katsoo l‰pi kaikki Otukset Worldssa, kutsuu checkProcreatingAbility() kullekin
    Critter* checkProcreatingAbility();       // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL*/
