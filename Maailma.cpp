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
  if (myCoords != herCoords) {
    if (myCoords.x+1 == herCoords.x || myCoords.x == herCoords.x || myCoords.x-1 == herCoords.x) {
      if (myCoords.y+1 == herCoords.y || myCoords.y == herCoords.y || myCoords.y-1 == herCoords.y) {
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
        if (creatures[i][j] == NULL) {
          coordinates here(i,j);
          return here;
        }
      }
    }
  }
}

coordinates Maailma::getCoords(int birthNumber_) {
  for (int i=0; i<creaturesByBirth.size(); i++) {
    if (creaturesByBirth[i] != NULL && creaturesByBirth[i]->birthNumber == birthNumber_) {
      coordinates toBeReturned = creaturesByBirth[i]->myCoord;
      return toBeReturned;
    }
  }
} //

void Maailma::moveCreature (Otus* moved) // muuttaa otuksen koordinaatteja
{
  cout << "Liiku: alku";
  coordinates location = moved->myCoord;

  coordinates directionWish(rand()%3-1,rand()%3-1);
  coordinates wp = location+directionWish;
  cout << "x: " << (wp.x) << " y: " << (wp.y) << "\n";
  if (wp.x >= 0 && wp.x < widthSize && wp.y >= 0 && wp.y < heightSize && creatures[wp.x][wp.y]==NULL) {
    cout << "Yritän liikkua!" << endl;
    creatures[wp.x][wp.y] = creatures[location.x][location.y];
    creatures[location.x][location.y] = NULL;
    creatures[wp.x][wp.y]->myCoord = coordinates(wp.x,wp.y);
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

Otus* Maailma::feelAround(Otus* feeler) { // returns NULL if none around, else pointer to lusted
  for (int i=0; i<creaturesByBirth.size(); i++) {
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

void Maailma::copulate(Otus* mommy) {
  Otus* daddy = feelAround(mommy);
  if (daddy != NULL && mommy->waitSex == 0) {
    bool didIt = createCreature(mommy, daddy);
//    horny();            // ilmaistaan himo hornyymällä. Otus on vasta siis löytänyt himoittavan tyypin, ja muuttuu keltaiseksi.
//    puoliso.horny();    // puolisokin on kuuma parittelusta. Vastaanottavan osapuolen palautumisaikaa ei kuitenkaan säädetä, kaksineuvoisuus <3
    mommy->waitSex += PALAUDU;
//    myfile << "createCreature(suvullinen): " << didIt << endl;
  }
//  myfile << "Ei löytynyt ketään :( " << endl;
}

/*
void Maailma::findAllProcreators() {              // katsoo läpi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin

}

Otus* Maailma::checkProcreatingAbility() {        // palauttaa ensimmäisen parittelumahdollisuuden tai NULL

}*/


