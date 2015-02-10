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
  creaturesAlive = 0;
}

bool Maailma::createCreature(Otus* mother, Otus* father) {
  if(mother->isAlive && father->isAlive) {
    coordinates whereTo = findEmptyNeighbor(mother->myCoord);
    if (withinBounds(whereTo) && whereTo!=mother->myCoord) {
      creatures[whereTo.x][whereTo.y]=new Otus(rgb{mother->RGBgenome.r, mother->RGBgenome.g, mother->RGBgenome.b},coordinates{whereTo.x, whereTo.y});
      creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
      ++creaturesAlive;
      return true;
      // todo use father's genome too
    }
  }
  else return false;
}

bool Maailma::createCreature(coordinates whereTo) { // create a red creature
  if (withinBounds(whereTo) && creatures[whereTo.x][whereTo.y]==NULL) {
    creatures[whereTo.x][whereTo.y]=new Otus(rgb{255, 0, 0}, coordinates {whereTo.x, whereTo.y});
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    ++creaturesAlive;
    return true;
    // todo use father's genome too
  }
  else return false;
}

bool Maailma::createCreature(rgb genome, coordinates whereTo) { // create a red creature
  if (withinBounds(whereTo) && creatures[whereTo.x][whereTo.y]==NULL) {
    creatures[whereTo.x][whereTo.y]=new Otus(rgb{genome.r, genome.g, genome.b}, coordinates {whereTo.x, whereTo.y});
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    ++creaturesAlive;
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

bool Maailma::withinBounds(coordinates c) {
  if((c.x >= 0) && (c.x < WIDTH) && (c.y >= 0) && (c.y < HEIGHT)) {
    return true;
  }
  else {return false;}
}

void Maailma::breathe(Otus* breather) {
  short breathingSpacesNeeded = 5;
  coordinates toThis = breather->myCoord;
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(withinBounds(coordinates{i,j}) && (toThis.x!=i||toThis.y!=j)) {
        if (creatures[i][j] == NULL) {
          breathingSpacesNeeded-=1;
        }
      }
    }
  }
  if (breathingSpacesNeeded>0)
    breather->isAlive = false;
    --creaturesAlive;
}

coordinates Maailma::findEmptyNeighbor(coordinates toThis) {
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(withinBounds(coordinates{i,j}) && (toThis.x!=i||toThis.y!=j)) {
        if (creatures[i][j] == NULL) {
          coordinates here(i,j);
          return here;
        }
        if (!creatures[i][j]->isAlive) {
          delete creatures[i][j];
          coordinates here(i,j);
          return here;
        }
      }
    }
  }
  return coordinates(-3,-3);
}

coordinates Maailma::findNeighbor(coordinates toThis) {
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(withinBounds(coordinates{i,j}) && (toThis.x!=i||toThis.y!=j)) {
        if (creatures[i][j] != NULL) {
          coordinates here(i,j);
          return here;
        }
      }
    }
  }
  return coordinates(-3,-3);
}

void Maailma::moveCreature (Otus* moved) { // muuttaa otuksen koordinaatteja
  coordinates location = moved->myCoord;
  coordinates directionWish(rand()%3-1,rand()%3-1);
  coordinates wp = location+directionWish;
  if (wp.x >= 0 && wp.x < WIDTH && wp.y >= 0 && wp.y < HEIGHT && creatures[wp.x][wp.y]==NULL) {
    creatures[wp.x][wp.y] = creatures[location.x][location.y];
    creatures[location.x][location.y] = NULL;
    creatures[wp.x][wp.y]->myCoord = coordinates(wp.x,wp.y);
  }
}

void Maailma::doInitialBirths() {
  // luodaan otukset
  for (int i=creaturesByBirth.size(); i<INIT_CREATURES; i++) {
    int x_syntyva = (317+3*i)%WIDTH;
    int y_syntyva = (237+3*i)%HEIGHT;
    if (creatures[x_syntyva][y_syntyva]==NULL) {
      bool hmm = createCreature(rgb{(255-18*i)%256,(3+20*i)%256,220*i%256},coordinates{x_syntyva,y_syntyva});
    }
  }
}

void Maailma::doMoves() {
      // Liikkumiset, latautumiset
      for(int i=0; i<creaturesByBirth.size(); i++) {
        if(creaturesByBirth[i]->isAlive) {
          moveCreature(creaturesByBirth[i]);
          if(creaturesByBirth[i]->waitSex>=1) {
            --creaturesByBirth[i]->waitSex;
          }
        }
      }
}

void Maailma::doCopulations() {
      // Parittelut
      int bz = creaturesByBirth.size();
      for(int i=0; i<bz; i++) {
        if(creaturesByBirth[i]->isAlive)
          copulate(creaturesByBirth[i]);
      }
}

void Maailma::doColorChanges(int colorCounter) {
      // V‰rien palauttelu genotyyppi‰ kohti
      if( colorCounter%10 == 9) {
        for(int i=0; i<creaturesByBirth.size(); i++) {
          creaturesByBirth[i]->relax();
          breathe(creaturesByBirth[i]);
//          myfile << "Otuksia elossa " << creaturesAlive << std::endl;
        }
      }
}

Otus* Maailma::feelAround(Otus* feeler) { // returns NULL if none around, else pointer to lusted
  for (int i=0; i<creaturesByBirth.size(); i++) {
    if (i != feeler->birthNumber) {
      coordinates theirCoords = findNeighbor(feeler->myCoord);
      coordinates myCoords = feeler->myCoord;
      if(theirCoords!=coordinates{-3,-3}) {
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
    if (didIt==true) {
      mommy->freak();            // ilmaistaan himo hornyym‰ll‰. Otus on vasta siis lˆyt‰nyt himoittavan tyypin, ja muuttuu keltaiseksi.
      daddy->freak();    // puolisokin on kuuma parittelusta. Vastaanottavan osapuolen palautumisaikaa ei kuitenkaan s‰‰det‰, kaksineuvoisuus <3
      mommy->waitSex += WAIT_AFTER;
    }
  }
}

/*
void Maailma::findAllProcreators() {              // katsoo l‰pi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin

}

Otus* Maailma::checkProcreatingAbility() {        // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL

}*/


