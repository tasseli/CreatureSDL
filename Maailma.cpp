#include <iostream>
#include "Maailma.h"

Maailma::Maailma(int width, int height) {
  creatures = vector<vector<Otus*> >();
  creaturesByBirth = vector<Otus*>();
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

void Maailma::breathe(Otus* breather) {
  short breathingSpacesNeeded = 5;
  coordinates toThis = breather->myCoord;
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(toThis.x!=i||toThis.y!=j) {
        if (creatures[i][j] == NULL) {
          breathingSpacesNeeded-=1;
        }
      }
    }
  }
  if (breathingSpacesNeeded>0)
    breather->isAlive = false;
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

coordinates Maailma::findNeighbor(coordinates toThis) {
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

void Maailma::moveCreature (Otus* moved) // muuttaa otuksen koordinaatteja
{
  cout << "Liiku: alku";
  coordinates location = moved->myCoord;

  coordinates directionWish(rand()%3-1,rand()%3-1);
  coordinates wp = location+directionWish;
  cout << "x: " << (wp.x) << " y: " << (wp.y) << "\n";
  if (wp.x >= 0 && wp.x < WIDTH && wp.y >= 0 && wp.y < HEIGHT && creatures[wp.x][wp.y]==NULL) {
    cout << "Yrit�n liikkua!" << endl;
    creatures[wp.x][wp.y] = creatures[location.x][location.y];
    creatures[location.x][location.y] = NULL;
    creatures[wp.x][wp.y]->myCoord = coordinates(wp.x,wp.y);
  }
}

Otus* Maailma::feelAround(Otus* feeler) { // returns NULL if none around, else pointer to lusted
  for (int i=0; i<creaturesByBirth.size(); i++) {
    if (i != feeler->birthNumber) {
      coordinates theirCoords = findNeighbor(feeler->myCoord);
      coordinates myCoords = feeler->myCoord;
      if (nextTo(myCoords, theirCoords)) {
        return creaturesByBirth[i];   // valitaan eka
      }
    }
  }
  return NULL;
}

void Maailma::copulate(Otus* mommy) {
  Otus* daddy = feelAround(mommy);
  if (daddy != NULL && mommy->waitSex == 0 && creaturesByBirth.size()<MAX_CREATURES) {
    bool didIt = createCreature(mommy, daddy);
    mommy->freak();            // ilmaistaan himo hornyym�ll�. Otus on vasta siis l�yt�nyt himoittavan tyypin, ja muuttuu keltaiseksi.
    daddy->freak();    // puolisokin on kuuma parittelusta. Vastaanottavan osapuolen palautumisaikaa ei kuitenkaan s��det�, kaksineuvoisuus <3
    mommy->waitSex += WAIT_AFTER;
  }
}

/*
void Maailma::findAllProcreators() {              // katsoo l�pi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin

}

Otus* Maailma::checkProcreatingAbility() {        // palauttaa ensimm�isen parittelumahdollisuuden tai NULL

}*/


