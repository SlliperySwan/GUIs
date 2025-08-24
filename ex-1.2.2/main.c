#include <SDL.h>
#include "SDL2_gfxPrimitives.h"


#define MAX(x,y) x>=y?x:y
#define MIN(x,y) x<=y?x:y


#define WIDTH 1000
#define HEIGHT 700

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * window = SDL_CreateWindow("ex-1.2.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer * ren = SDL_CreateRenderer(window, -1, 0);
	
	
	SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
	
	int i, RANGE = WIDTH/2+300;
	for (i = RANGE; i > 0; i--) {
		filledPieRGBA(ren,WIDTH/2,HEIGHT/2,i,0,180,MAX(255*(RANGE-i)/RANGE-100, 0),MAX(255*(RANGE-i)/RANGE-100, 0),255*(RANGE-i)/RANGE,255);
	}
	
	
	for (i = RANGE; i > 50; i--) {
		filledPieRGBA(ren,WIDTH/2,HEIGHT/2,i,180,360,255,255*(RANGE-i)/RANGE,0,255);
	}
	filledPieRGBA(ren,WIDTH/2,HEIGHT/2,50,180,360,255,255,255,255);
	
	
	for (i = 0; i < 30; i++) {
		boxRGBA(ren,0,HEIGHT/2-29+i,WIDTH,HEIGHT/2-28+i,255,80,0,60*i/15);
	}
	
	
	
	SDL_RenderPresent(ren);
	SDL_Delay(5000);
	
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


