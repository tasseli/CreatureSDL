#include <iostream>
#include "Maailma.h"


Maailma::Maailma(int width, int height) {
  creatures = vector<vector<Otus*> >();
  height_size = height;
  width_size = width;
  creatures_alive_sum = 0;

  for (int i = 0; i < width; ++i) {
    creatures.push_back(vector<Otus*>());
    for (int j = 0; j < height; ++j) {
      creatures.back().push_back(NULL);
    }
  }
}

void Maailma::addToIndex(Otus* syntyva) {
  creatures_alive_sum++;
  syntyva->maailma_ID = creatures_alive_sum;
}

coordinates Maailma::getCoordinates(int maailmaID) {
  for(int j = 0; j < height_size; j++) {
    for(int i = 0; i < width_size; i++) {
//      cout << "getCoord: Kahden for-loopin sisällä";
//      cout << "j: " << j << " i: " << i << "\n";
//      cout << "Creatures.size() == " << creatures.size() << " x " << creatures.at(0).size() << "\n";
      if (creatures[i][j] != NULL && creatures[i][j]->maailma_ID == maailmaID) {
//        cout << "getCoord: if:n sisällä";
        coordinates palautettavat;
        palautettavat.x = i;
        palautettavat.y = j;
//        cout << "getCoord: palautusvalmiina";
        return palautettavat;
      }
    }
  }
}

void Maailma::liiku (int ID) // muuttaa otuksen koordinaatteja
{
  cout << "Liiku: alku";
  coordinates location = getCoordinates(ID);
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

/*
void Maailma::findAllProcreators() {              // katsoo läpi kaikki Otukset Maailmassa, kutsuu checkProcreatingAbility() kullekin

}

Otus* Maailma::checkProcreatingAbility() {        // palauttaa ensimmäisen parittelumahdollisuuden tai NULL

}*/


