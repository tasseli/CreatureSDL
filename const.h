#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

                                        // TODO: Jussin neuvo, omaks fileekseen
const short WIDTH           = 340   ;   // Petrimaljan x
const short HEIGHT          = 280   ;   // Petrimaljan y
const short BPP             = 4     ;
const short DEPTH           = 32    ;
const short GRAPH_ACCURACY  = 5     ;   // kuinka suurta eroa alkuper�isen v�rin poikkeamasta kunnioitetaan

const short MAX_CREATURES   = 20000   ;
const short INIT_CREATURES  = 10  ;
const short WAIT_AFTER      = 230  ;   // montako askelta otuksen on otettava palautuakseen, ennen kuin jaksaa taas lis��nty�
const short WAIT_FIRST      = 130   ;   // mink� verran otukset on lis��ntym�tt� demon aluksi

struct coordinates {
  int x;
  int y;
  bool operator==(const coordinates& that) const { return x == that.x && y == that.y; }
  bool operator!=(const coordinates& that) const { return x != that.x || y != that.y; }
  coordinates operator+ (const coordinates& that) const { return coordinates (x + that.x, y + that.y); }
  coordinates(int x_, int y_) {x = x_; y = y_;}
  coordinates() {}
};

struct rgb {
  int r;
  int g;
  int b;
  bool operator==(const rgb& that) const { return r == that.r && g == that.g && b == that.b; }
  bool operator!=(const rgb& that) const { return r != that.r || g != that.g || b != that.b; }
  rgb(int r_, int g_, int b_) {r = r_; g = g_; b = b_;}
  rgb() {}
};

#endif // CONST_H_INCLUDED
