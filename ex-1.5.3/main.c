#include <SDL.h>


#define WIDTH 1000
#define HEIGHT 700

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32 * ms) {
	Uint32 antes = SDL_GetTicks();
	int isevt = SDL_WaitEventTimeout(evt, *ms);
	
	(*ms)-=(SDL_GetTicks()-antes);
	if (*ms < 0)
		(*ms) = 0;
	return isevt;
}

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * window = SDL_CreateWindow("ex-1.5.3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer * ren = SDL_CreateRenderer(window, -1, 0);
	
	SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
	
	int i = 0, x = 0, y = 0, CX = WIDTH/2, CY = HEIGHT/2;
	int r = 255, g = 0, b = 255;
	SDL_Rect rect1 = {CX-50, CY-50, 25, 25};
	SDL_Rect rect2 = {CX+50, CY+50, 25, 25};
	SDL_Rect outerBox = {CX-51, CY-51, 127, 127};
	SDL_Rect innerBox = {CX-25, CY-25, 75, 75};
	
	Uint32 espera;
    SDL_Event evt;
    int isevt;
    
	while (!SDL_QuitRequested()) {
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		
		SDL_SetRenderDrawColor(ren,255,255,255,255);
		SDL_RenderDrawRect(ren, &outerBox);
		SDL_RenderDrawRect(ren, &innerBox);
		
		SDL_SetRenderDrawColor(ren,255-r,g,b,255);
		SDL_RenderFillRect(ren, &rect1);
		SDL_SetRenderDrawColor(ren,r,g,255-b,255);
		SDL_RenderFillRect(ren, &rect2);
		
		espera = 50;
		isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
		if (isevt) {
	        if (evt.type == SDL_KEYDOWN) {
	            switch (evt.key.keysym.sym) {
	                case SDLK_UP:
						i = 0;
						rect1.x = CX-50;
						rect1.y = CY-50;
						rect2.x = CX+50;
						rect2.y = CY+50;
						r+=50;
	                    break;
	                case SDLK_DOWN:
						i = 40;
						rect1.x = CX+50;
						rect1.y = CY+50;
						rect2.x = CX-50;
						rect2.y = CY-50;
						b+=50;
	                    break;
	                case SDLK_LEFT:
						i = 60;
						rect1.x = CX-50;
						rect1.y = CY+50;
						rect2.x = CX+50;
						rect2.y = CY-50;
						g+= 200;
	                    break;
	                case SDLK_RIGHT:
						i = 20;
						rect1.x = CX+50;
						rect1.y = CY-50;
						rect2.x = CX-50;
						rect2.y = CY+50;
	                    break;
	                    r-=50;
	                	g-=50;
	                	b-=50;
	            }
	        } else {
	        	SDL_Delay(espera);
			}
		} 
		if (i%80 < 20) {
			rect1.x += 5;
			rect2.x -= 5;
		} else if (i%80 < 40) {
			rect1.y += 5;
			rect2.y -= 5;
		} else if (i%80 < 60) {
			rect1.x -= 5;
			rect2.x += 5;
		} else {
			rect1.y -= 5;
			rect2.y += 5;
		}
		
		SDL_RenderPresent(ren);
		i++;
	}	
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
