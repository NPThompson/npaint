/* npaint 
| The most elegant, free, open-source pixel editor on the internet! 
| N.P.Thompson <noahpthomp@gmail.com>

put/get pixel 'should' call lock/unlock surface.
But so far npaint works without calling those.
Maybe it will crash when more than one surface is involved?
*/
#include"input.h"
#include"pixel_op.h"











struct color{
  Uint8 r,g,b;
};










SDL_Surface*  canvas;
SDL_Renderer* render;//software renderer to canvas, not to window
SDL_Window*   window;
color         pencolor   = { 0xFF, 0xFF, 0xFF };
double        zoom       = 1.0;
double        zoomfactor = 1.35;
v2            view(320,240);








void initSDL();
void closeSDL();
bool loop();
void redraw();
void penmode();
void pickcolor();
v2   mouse();//returns mouse relatative to canvas, not relative to window
v2   windim();//window dimensions;







int main(int argc, char** argv)
{ initSDL();
  while(loop()){}
  closeSDL();
}







bool loop()
{ waitforevent();

  ifev(SDL_SCANCODE_ESCAPE) return false;
  ifev(SDL_QUIT)            return false;

  ifev(SDL_SCANCODE_R)
    { pencolor.r = numericinput( 3 );
    }
    
  ifev(SDL_SCANCODE_G)
    { pencolor.g = numericinput( 3 );
    }
    
  ifev(SDL_SCANCODE_B)
    { pencolor.b = numericinput( 3 );
    }
    
  
  ifev(SDL_MOUSEBUTTONDOWN)
   { if(ev.button.button ==  SDL_BUTTON_LEFT)
       penmode();
     if(ev.button.button == SDL_BUTTON_RIGHT )
       pickcolor();
   }

  ifev(SDL_MOUSEWHEEL)
    { if(ev.wheel.y < 0 )
        zoom /= zoomfactor;//zoom in
      else
	zoom *= zoomfactor;//zoom out
    }
  
  ifev(SDL_SCANCODE_RIGHT)
    view.x += 50 / zoom;

  ifev(SDL_SCANCODE_DOWN)
    view.y += 50 / zoom;

  ifev(SDL_SCANCODE_UP)
    view.y -= 50 / zoom;

  ifev(SDL_SCANCODE_LEFT)
    view.x -= 50 / zoom;
  
  redraw();
  return true;
}



void penmode()
{ //on first click, place single pixel
  v2 p0 = mouse()/zoom;
  putpixel( canvas,
            p0.x,
	    p0.y,
	    SDL_MapRGB( canvas->format, pencolor.r, pencolor.g, pencolor.b)
	   );
  //Until user releases mouse, draw straight line between last mouse position and current mouse position
  while(!event(SDL_MOUSEBUTTONUP)){
    v2 p1 = mouse()/zoom;
    SDL_SetRenderDrawColor(render, pencolor.r,pencolor.g,pencolor.b,0xFF);
    SDL_RenderDrawLine(render,p0.x,p0.y,p1.x,p1.y);
    p0 = p1;
    redraw();
  }
}



void scroll()
{ SDL_Event ev;
  do{
    SDL_WaitEvent(&ev);
    if(ev.type == SDL_MOUSEMOTION){
      view.x += ev.motion.xrel / (zoom / 2);
      view.y += ev.motion.yrel / (zoom / 2);
      redraw();
    }
  }while(ev.type != SDL_MOUSEBUTTONUP);
}



void pickcolor()
{ waitforevent();
  //if hold, use color palette
  ifev(SDL_MOUSEMOTION)
    { scroll();
    } else
	{ v2 p = mouse()/zoom;
          Uint32 newcolor = getpixel( canvas, p.x, p.y );
          SDL_GetRGB( newcolor,
	              canvas->format,
 	              &pencolor.r,
	              &pencolor.g,
	              &pencolor.b
	              );
	}
}



void redraw()
{ SDL_Surface* wsurface = SDL_GetWindowSurface(window);

  //Zooming got much easier when I relegated it all to the source rectangle  
  SDL_Rect src = {view.x - wsurface->w / (zoom*2),
		  view.y - wsurface->h / (zoom*2),
		  wsurface->w / zoom,
		  wsurface->h / zoom};
  //Fill w/ Grey
  SDL_FillRect( wsurface,
		NULL,
		SDL_MapRGB( wsurface->format,
		            0x80,
		            0x80,
			    0x80)
                );
  
  SDL_BlitScaled( canvas,
		  &src,
		  wsurface,
		  NULL
		  );
  
  SDL_UpdateWindowSurface( window );
}



v2 mouse()
{ return abs_mouse() - windim()/2.0 + view*zoom;//(1.5,1.5) corrects for cursor 
}



v2 windim()
{ int w,h;
  SDL_GetWindowSize(window,&w,&h);//SDL_Surface* wsurf = SDL_GetWindowSurface(window);
    return v2(w,h);
}



void initSDL()
{window = SDL_CreateWindow("npaint v 0.0",
			   SDL_WINDOWPOS_UNDEFINED,
			   SDL_WINDOWPOS_UNDEFINED,
			   640,
			   480,
			   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE /* | SDL_WINDOW_BORDERLESS */ );

  canvas = SDL_CreateRGBSurface(0, 640, 480, 32, 0,0,0,0);

  render = SDL_CreateSoftwareRenderer( canvas );
}



void closeSDL()
{ SDL_DestroyWindow(   window );
  SDL_DestroyRenderer( render );
  SDL_FreeSurface(     canvas );
}


