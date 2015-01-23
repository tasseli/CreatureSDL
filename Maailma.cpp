#include <iostream>
#include "Maailma.h"

Maailma::Maailma(int width, int height) {
  creatures = vector<vector<Otus*> >();
  creaturesByBirth = vector<Otus*>();
  heightSize = height;
  widthSize = width;
  //creaturesAliveSum = 0;
  for (int i = 0; i < width; ++i) {
    creatures.push_back(vector<Otus*>());
    for (int j = 0; j < height; ++j) {
      creatures.back().push_back(NULL);
    }
  }
}

bool Maailma::createCreature(Otus* mother, Otus* father) {
  coordinates whereTo = findEmptyNeighbor(mother->myCoord);
  if (whereTo!=mother->myCoord) {
    creatures[whereTo.x][whereTo.y]=new Otus(rgb{mother->RGBgenome.r, mother->RGBgenome.g, mother->RGBgenome.b},coordinates{whereTo.x, whereTo.y});
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    return true;
    // todo use father's genome too
  }
  else return false;
}

bool Maailma::createCreature(coordinates whereTo) { // create a red creature
  if (creatures[whereTo.x][whereTo.y]==NULL) {
    creatures[whereTo.x][whereTo.y]=new Otus(rgb{255, 0, 0}, coordinates {whereTo.x, whereTo.y});
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    return true;
    // todo use father's genome too
  }
  else return false;
}

bool Maailma::createCreature(rgb genome, coordinates whereTo) { // create a red creature
  if (creatures[whereTo.x][whereTo.y]==NULL) {
    creatures[whereTo.x][whereTo.y]=new Otus(rgb{genome.r, genome.g, genome.b}, coordinates {whereTo.x, whereTo.y});
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    return true;
    // todo use father's genome too
  }
  else return false;
}

bool Maailma::nextTo(coordinates myCoords, coordinates herCoords) {
  if ((myCoords == herCoords) == false) {
    if (myCoords.x+1 == herCoords.x || myCoords.x-1 == herCoords.x) {
      if (myCoords.y+1 == herCoords.y || myCoords.y-1 == herCoords.y) {
        return true;
      }
    }
    else return false;
  }
  return false;
}

coordinates Maailma::findEmptyNeighbor(coordinates toThis) {
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(toThis.x!=i||toThis.y!=j) {
        if (creatures[i][j] != NULL) {
          coordinates here(i,j);
          return here;
        }
      }
    }
  }
}

coordinates Maailma::getCoords(int birthNumber_) {
  for(int j = 0; j < heightSize; j++) {
    for(int i = 0; i < widthSize; i++) {
//      cout << "getCoord: Kahden for-loopin sisällä";
//      cout << "j: " << j << " i: " << i << "\n";
//      cout << "Creatures.size() == " << creatures.size() << " x " << creatures.at(0).size() << "\n";
      if (creatures[i][j] != NULL && creatures[i][j]->birthNumber == birthNumber_) {
//        cout << "getCoord: if:n sisällä";
        coordinates toBeReturned(i,j);
//        cout << "getCoord: palautusvalmiina";
        return toBeReturned;
      }
    }
  }
} //

void Maailma::moveCreature (int ID) // muuttaa otuksen koordinaatteja
{
  cout << "Liiku: alku";
  coordinates location = getCoords(ID);
  cout << "Liiku: getCoord tehty";

//  coordinates directionWish = {-1,1};
  cout << "x: " << (location.x+1) << " y: " << (location.y+1) << "\n";
   if (location.x+1 >= 0 && location.x+1 < creatures.size() &&
      location.y+1 >= 0 && location.y+1 < creatures.at(0).size() &&
      creatures[location.x+1][location.y+1]==NULL) { // Ilpolta
    creatures[location.x+1][location.y+1] = creatures[location.x][location.y];
    delete creatures[location.x][location.y];
  }
}

/*int Maailma::feelAround (int birthNumber_) { // returns the birthNumber (or -1) of a suitable copulate-able creature using nextTo(my birthNumber)

  for (int i=0; i<creaturesAliveSum; i++) {
    if (i != birthNumber_) {
      coordinates herCoords = getCoords(i);
      coordinates myCoords = getCoords(birthNumber_);
      if (nextTo(myCoords, herCoords)) {
        return i;   // valitaan eka
      }
    }
  }
  return -1;
}*/

Otus* Maailma::feelAround(Otus* feeler) {
  for (int i=0; i<Otus::birthCounter; i++) {
    if (i != feeler->birthNumber) {
      coordinates herCoords = getCoords(i);
      coordinates myCoords = feeler->myCoord;
      if (nextTo(myCoords, herCoords)) {
        return creaturesByBirth[i];   // valitaan eka
      }
    }
  }
  return NULL;
}
/*
Otus* Maailma::copulate(Otus* A, Otus* B) {
  int lusted = feelAround();
  if (lusted != (-1)) {
//    horny();            // ilmaistaan himo hornyymällä. Otus on vasta siis löytänyt himoittavan tyypin, ja muuttuu keltaiseksi.
//    puoliso.horny();    // puolisokin on kuuma parittelusta. Vastaanottavan osapuolen palautumisaikaa ei kuitenkaan säädetä, kaksineuvoisuus <3
//    lisaantymiseenAikaa += PALAUDU;
    return Otus((r_gen+puoliso.r_gen)/2, (g_gen+puoliso.g_gen)/2, (b_gen+puoliso.b_gen)/2, x, y);
  }
  else return Otus(650,490);
}
*/
/*
void Maailma::findAllProcreators() {              // katsoo läpi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin

}

Otus* Maailma::checkProcreatingAbility() {        // palauttaa ensimmäisen parittelumahdollisuuden tai NULL

}*/


