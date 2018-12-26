/*pixel_op.h*/
#ifndef PIXEL_OP_H
#define PIXEL_OP_H

#include<SDL.h>

//taken from <https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html#AEN90>

void   putpixel(SDL_Surface*, int, int, Uint32 );
Uint32 getpixel(SDL_Surface*, int, int );


#endif
