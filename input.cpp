#include"input.h"



v2 abs_mouse()
{ int x,y;
  SDL_GetMouseState(&x,&y);
  return v2(x,y);
}
	 


int digitinput()
{
 #define ifnum( _X_ ) if(ev.key.keysym.scancode == SDL_SCANCODE_ ## _X_ )
 #define retnum( _X_ ) ifnum(_X_) return _X_;
  while(true)
    { waitforevent();
      retnum( 0 );     
      retnum( 1 );     
      retnum( 2 );
      retnum( 3 );
      retnum( 4 );
      retnum( 5 );     
      retnum( 6 );     
      retnum( 7 );     
      retnum( 8 );     
      retnum( 9 );     
    }
  #undef ifnum
  #undef retnum
}



int numericinput(unsigned int places)
{ int ret = 0;
  for(int i = 0; i < places; ++i)
    { ret = 10 * ret + digitinput();
    }
  return ret;
}

