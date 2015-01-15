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
    void addToIndex(Otus* syntyva);
    coordinates getCoordinates(int maailma_ID);
    void liiku (int ID);
    /*void findAllProcreators();        // katsoo l‰pi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin
    Otus* checkProcreatingAbility();  // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL*/
    vector<vector<Otus*> > creatures; // sis‰lt‰‰ pointterit kaikkiin Maailman Otuksiin (st‰ckiss‰). Solu t‰ynn‰ tai NULL.
    int height_size, width_size;
    int creatures_alive_sum;
};

#endif // MAAILMA_H
