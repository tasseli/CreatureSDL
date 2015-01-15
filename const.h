#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

                                        // TODO: Jussin neuvo, omaks fileekseen
const short WIDTH           = 640   ;   // Petrimaljan x
const short HEIGHT          = 480   ;   // Petrimaljan y
const short BPP             = 4     ;
const short DEPTH           = 32    ;
const short TARKKUUS        = 3     ;   // kuinka suurta eroa alkuper‰isen v‰rin poikkeamasta kunnioitetaan

const short OTUKSIAMAX      = 2400   ;
const short OTUKSIA_ALUSSA  = 10  ;
const short PALAUDU         = 330  ;   // montako askelta otuksen on otettava palautuakseen, ennen kuin jaksaa taas lis‰‰nty‰
const short ALKUUN_ILMAN    = 30   ;   // mink‰ verran otukset on lis‰‰ntym‰tt‰ demon aluksi

struct coordinates {
  int x;
  int y;
};



#endif // CONST_H_INCLUDED
