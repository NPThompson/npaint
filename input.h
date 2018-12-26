#ifndef INPUT_H
#define INPUT_H



#include<stdio.h>
#include<assert.h>
#include<SDL.h>
#include"coord.h"


/*These macro + template frankensteins are dangerous.
 *But... they make event handling readable. 
 */
#define waitforevent() SDL_Event ev; SDL_WaitEvent(&ev);
#define pollevents() SDL_Event ev; SDL_PollEvent(&ev);

//ifev is open-ended, capturing the 'then' and 'else' statements following it, so it's usable just like the regular 'if'
#define ifev( _P_ ) if( _IFEV( ev, _P_ ))


/*Query type determines left-hand side -- must manually be specialized for every input event type*/
template<typename Q> bool _IFEV( SDL_Event ev, Q query )
{ fprintf(stderr,"Go back and add another _IFEV specialization");
  assert(0);
  return false;
}

template<typename Q = SDL_EventType> bool _IFEV(SDL_Event ev, SDL_EventType query)
{return ev.type == query;
}

template<typename Q = SDL_Scancode> bool _IFEV(SDL_Event ev, SDL_Scancode query)
{return ev.key.keysym.scancode == query;
}

template<typename Q> bool event(Q query)
{ waitforevent();
  return _IFEV( ev, query );
}



v2 abs_mouse();





#endif
