#include <iostream>
#include "Maailma.h"


Maailma::Maailma(int width, int height) {
  creatures = vector<vector<Otus*> >();
  heightSize = height;
  widthSize = width;
  creaturesAliveSum = 0;

  for (int i = 0; i < width; ++i) {
    creatures.push_back(vector<Otus*>());
    for (int j = 0; j < height; ++j) {
      creatures.back().push_back(NULL);
    }
  }
}

void Maailma::addToIndex(Otus* syntyva) {
  creaturesAliveSum++;
  syntyva->maailma_ID = creaturesAliveSum;
}

coordinates Maailma::getCoordinates(int maailmaID) {
  for(int j = 0; j < heightSize; j++) {
    for(int i = 0; i < widthSize; i++) {
//      cout << "getCoord: Kahden for-loopin sisällä";
//      cout << "j: " << j << " i: " << i << "\n";
//      cout << "Creatures.size() == " << creatures.size() << " x " << creatures.at(0).size() << "\n";
      if (creatures[i][j] != NULL && creatures[i][j]->maailma_ID == maailmaID) {
//        cout << "getCoord: if:n sisällä";
        coordinates toBeReturned;
        toBeReturned.x = i;
        toBeReturned.y = j;
//        cout << "getCoord: palautusvalmiina";
        return toBeReturned;
      }
    }
  }
} //

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
void Otus::feelAround () {

  for (int i=0; i<creatures->size(); i++) {
    if (((x-tunnusteltavatOtukset->at(i).x)==0) && ((y-tunnusteltavatOtukset->at(i).y)==0)) {//&&(omaJarjestysNro!=i) // jos otus on samalla paikalla kuin mä
      himoittu = i;   // valitaan viimeinen halun kohteeksi.
    }
  }
}

Otus* Otus::copulate(Otus* spouce) {
  if ((himoittu != (-1))&&(lisaantymiseenAikaa==0)&&(puoliso.lisaantymiseenAikaa==0)&&(omaJarjestysNro!=puoliso.omaJarjestysNro)) {
    himoittu = -1;
    horny();            // ilmaistaan himo hornyymällä. Otus on vasta siis löytänyt himoittavan tyypin, ja muuttuu keltaiseksi.
    puoliso.horny();    // puolisokin on kuuma parittelusta. Vastaanottavan osapuolen palautumisaikaa ei kuitenkaan säädetä, kaksineuvoisuus <3
    lisaantymiseenAikaa += PALAUDU;
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


