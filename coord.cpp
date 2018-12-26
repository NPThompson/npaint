#include"coord.h"










v2::v2(float _x, float _y)
{ x = _x;
  y = _y;
}



v2 operator+(v2 v, v2 w)
{ return v2( v.x + w.x,
	       v.y + w.y
	     );
}

v2 operator*(v2 v, float s)
{ return v2( v.x * s,
	     v.y * s
	     );
}

v2 operator-(v2 v, v2 w)
{ return v + (w * -1);
}

v2 operator/(v2 v, float s)
{ return v * (1/s);
}

v2 operator+=(v2& v, v2 w)
{ v = v + w;
  return v;
}

v2 operator-=(v2& v, v2 w)
{ v = v - w;
  return v;
}

v2 operator/(v2 v, v2 w)
{ return  v2(v.x / w.x,
	     v.y / w.y);
}

v2::v2()
{ x = y = 0;
}

v2 v2::operator=(v2 other)
{ x = other.x;
  y = other.y;
  return *this;
}



v2::operator wCoord()
{ return wCoord(x,y);
}

wCoord::wCoord(int x0, int y0)
{ x = x0;
  y = y0;
}

wCoord::operator v2()
{ return v2(x,y);
}


bool v2::operator==(v2 other)
{ return x == other.x && y == other.y;
}
