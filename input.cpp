#include"input.h"



v2 abs_mouse()
{ int x,y;
  SDL_GetMouseState(&x,&y);
  return v2(x,y);
}
	 
