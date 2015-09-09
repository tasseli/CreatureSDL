#include "World.h"

World::World(int width, int height) {
  creatures = vector<vector<Critter*> >();
  creaturesByBirth = vector<Critter*>();
  creaturesJustMoved = vector<coordinates>();
  for (int i = 0; i < width; ++i) {
    creatures.push_back(vector<Critter*>());
    for (int j = 0; j < height; ++j) {
      creatures.back().push_back(NULL);
    }
  }
}

bool World::createCritter(Critter* mother, Critter* father) {   // use parents' colors evenly
  if(MORTALITY==false || (mother->isAlive && father->isAlive)) {
    coordinates whereTo = findEmptyNeighbor(mother->myCoord);
    if (withinBounds(whereTo) && whereTo!=mother->myCoord) {
      creatures[whereTo.x][whereTo.y]=new Critter(rgb((mother->RGBgenome.r+father->RGBgenome.r)/2, (mother->RGBgenome.g+father->RGBgenome.g)/2,
                                                      (mother->RGBgenome.b+father->RGBgenome.b)/2), coordinates(whereTo.x, whereTo.y));
      creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
      ++creaturesAlive;
      return true;
    }
  }
  return false;  // (else)
}

bool World::createCritter(coordinates whereTo) {                // create a red creature
  if (withinBounds(whereTo) && creatures[whereTo.x][whereTo.y]==NULL) {
    creatures[whereTo.x][whereTo.y]=new Critter(rgb(255, 0, 0), coordinates(whereTo.x, whereTo.y));
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    ++creaturesAlive;
    return true;
  }
  return false;
}

bool World::createCritter(rgb genome, coordinates whereTo) {    // create a specified color creature
  if (withinBounds(whereTo) && creatures[whereTo.x][whereTo.y]==NULL) {
    creatures[whereTo.x][whereTo.y]=new Critter(rgb(genome.r, genome.g, genome.b), coordinates(whereTo.x, whereTo.y));
    creaturesByBirth.push_back(creatures[whereTo.x][whereTo.y]);
    ++creaturesAlive;
    return true;
  }
  return false;
}

bool World::nextTo(coordinates myCoords, coordinates herCoords) {
  if (myCoords != herCoords) {
    if (myCoords.x+1 == herCoords.x || myCoords.x == herCoords.x || myCoords.x-1 == herCoords.x) {
      if (myCoords.y+1 == herCoords.y || myCoords.y == herCoords.y || myCoords.y-1 == herCoords.y) {
        return true;
      }
    }
  }
  return false;
}

bool World::withinBounds(coordinates c) {
  if((c.x >= 0) && (c.x < WIDTH) && (c.y >= 0) && (c.y < HEIGHT)) {
    return true;
  }
  return false;
}

void World::breathe(Critter* breather) {
  if (MORTALITY == true) {
    short breathingSpacesNeeded = BREATHING_SPACE_NEEDED;
    coordinates toThis = breather->myCoord;
    for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
      for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
        if(withinBounds(coordinates(i,j)) && (toThis.x!=i||toThis.y!=j)) {
          if (creatures[i][j] == NULL) {
            breathingSpacesNeeded-=1;
          }
        }
      }
    }
    if (breathingSpacesNeeded>0)
      breather->isAlive = false;
      breather->rot();
      --creaturesAlive;
  }
}

coordinates World::findEmptyNeighbor(coordinates toThis) {
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(withinBounds(coordinates(i,j)) && (toThis.x!=i||toThis.y!=j)) {
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

coordinates World::findNeighbor(coordinates toThis) {
  for (int i=toThis.x-1; i<= toThis.x+1; ++i) {
    for (int j=toThis.y-1; j<= toThis.y+1; ++j) {
      if(withinBounds(coordinates(i,j)) && (toThis.x!=i||toThis.y!=j)) {
        if (creatures[i][j] != NULL) {
          coordinates here(i,j);
          return here;
        }
      }
    }
  }
  return coordinates(-3,-3);
}

void World::moveCritter (Critter* moved) { // muuttaa otuksen koordinaatteja
  coordinates location = moved->myCoord;
  coordinates directionWish(rand()%3-1,rand()%3-1);
  coordinates wp = location+directionWish;
  if (wp.x >= 0 && wp.x < WIDTH && wp.y >= 0 && wp.y < HEIGHT && creatures[wp.x][wp.y]==NULL) {
    creaturesJustMoved.push_back(coordinates(location.x, location.y));
    creatures[wp.x][wp.y] = creatures[location.x][location.y];
    creatures[location.x][location.y] = NULL;
    creatures[wp.x][wp.y]->myCoord = coordinates(wp.x,wp.y);
  }
}

void World::doInitialBirths() {
  // luodaan otukset
  for (int i=creaturesByBirth.size(); i<INIT_CREATURES; i++) {
    int x_syntyva = (317+3*i)%WIDTH;
    int y_syntyva = (237+2*i)%HEIGHT;
    if (creatures[x_syntyva][y_syntyva]==NULL) {
//      createCritter(rgb((215-24*i)%256,(3+15*i)%256,(255+252*i)%256),coordinates(x_syntyva,y_syntyva));
      createCritter(rgb((215-25*i)%256,(3+15*i)%256,(255+252*i)%256),coordinates(x_syntyva,y_syntyva));
    }
  }
}

void World::doMoves() {
      // Liikkumiset, latautumiset
      creaturesJustMoved.clear();
      for(unsigned int i=0; i<creaturesByBirth.size(); i++) {
        if(creaturesByBirth[i]->isAlive) {
          moveCritter(creaturesByBirth[i]);
          if(creaturesByBirth[i]->waitSex>=1) {
            --creaturesByBirth[i]->waitSex;
          }
        }
      }
}

void World::doCopulations() {
      // Parittelut
      int bz = creaturesByBirth.size();
      for(int i=0; i<bz; i++) {
        if(creaturesByBirth[i]->isAlive)
          copulate(creaturesByBirth[i]);
      }
}

void World::doColorChanges(int colorCounter) {
      // V‰rien palauttelu genotyyppi‰ kohti
      if( colorCounter%10 == 9) {
        for(unsigned int i=0; i<creaturesByBirth.size(); i++) {
          creaturesByBirth[i]->relax();
          breathe(creaturesByBirth[i]);
//          myfile << "Otuksia elossa " << creaturesAlive << std::endl;
        }
      }
}

Critter* World::feelAround(Critter* feeler) { // returns NULL if none around, else pointer to lusted
  for (unsigned int i=0; i<creaturesByBirth.size(); i++) {
    int j = (int)i;
    if (j != feeler->birthNumber) {
      coordinates theirCoords = findNeighbor(feeler->myCoord);
      if(theirCoords!=coordinates(-3,-3)) {
        return creaturesByBirth[i];   // valitaan eka
      }
    }
  }
  return NULL;
}

void World::copulate(Critter* mommy) {
  Critter* daddy = feelAround(mommy);
  if (daddy != NULL && mommy->waitSex == 0 && creaturesByBirth.size()<MAX_CREATURES) {
    bool didIt = createCritter(mommy, daddy);
    if (didIt==true) {
      mommy->freak();            // ilmaistaan himo hornyym‰ll‰. Critter on vasta siis lˆyt‰nyt himoittavan tyypin, ja muuttuu keltaiseksi.
      daddy->freak();    // puolisokin on kuuma parittelusta. Vastaanottavan osapuolen palautumisaikaa ei kuitenkaan s‰‰det‰, kaksineuvoisuus <3
      mommy->waitSex += WAIT_AFTER;
    }
  }
}

/*
void World::findAllProcreators() {              // katsoo l‰pi kaikki Otukset Worldssa, kutsuu checkProcreatingAbility() kullekin

}

Critter* World::checkProcreatingAbility() {        // palauttaa ensimm‰isen parittelumahdollisuuden tai NULL

}*/


