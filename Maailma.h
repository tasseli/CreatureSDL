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
//    void addToIndex(Otus* syntyva);
    bool nextTo(coordinates myCoords, coordinates herCoords);
    coordinates getCoords(int birthNumber);
    void liiku (int ID);
    int feelAround(int bithNumber_);  // returns the birthNumber of the first copulateable spouce-to-be near creature #birthNumber_
/*    Otus* copulate(Otus* spouce);
    */
    /*void findAllProcreators();        // katsoo l‰pi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin
    Otus* checkProcreatingAbility();  // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL*/
    vector<vector<Otus*> > creatures; // sis‰lt‰‰ pointterit kaikkiin Maailman Otuksiin (st‰ckiss‰). Solu t‰ynn‰ tai NULL.
    int heightSize, widthSize;
    int creaturesAliveSum;
};

#endif // MAAILMA_H
