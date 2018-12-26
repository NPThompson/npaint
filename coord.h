#ifndef COORD_H
#define COORD_H










class wCoord;

class v2{
 public:
  float x,y;
  v2(float,float);
  v2();
  v2 operator=(v2);
  bool operator==(v2);
  operator wCoord();
};



v2 operator+(v2,v2);
v2 operator-(v2,v2);
v2 operator*(v2,float);
v2 operator/(v2,float);

v2 operator+=(v2&, v2);
v2 operator-=(v2&, v2);
v2 operator/(v2,v2);

class wCoord{
 public:
  wCoord(int,int);
  int x,y;
  operator v2();
};


#endif
