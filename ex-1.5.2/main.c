#include <SDL.h>

#define WIDTH 1000
#define HEIGHT 700

struct coord {
	int x;
	int y;
};

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32 * ms) {
	Uint32 antes = SDL_GetTicks();
	int isevt = SDL_WaitEventTimeout(evt, *ms);
	Uint32 deltaEspera = SDL_GetTicks()-antes, novaEspera = *ms-deltaEspera;
	if (novaEspera > *ms)
		*ms = 0;
	else
		*ms -= deltaEspera;
	return isevt;
}

int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("ex-1.5.2",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         WIDTH, HEIGHT, SDL_WINDOW_SHOWN
                      	);
    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
	
	struct coord p1 = {.x = 100, .y = 100},
				 p2 = {.x = 100, .y = 150},
				 p3 = {.x = 100, .y = 200};
    SDL_Rect r1 = {p1.x,p1.y,100,20},
			 r2 = {p2.x,p2.y,100,20},
			 r3 = {p3.x,p3.y,100,20};
    
    
    Uint32 espera = 25;
    SDL_Event evt;
    
    while (!SDL_QuitRequested()) {

    	
    	
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        
        
		SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r1);
        SDL_RenderFillRect(ren, &r2);
        SDL_RenderFillRect(ren, &r3);
        
        
        SDL_RenderPresent(ren);
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt) {
	        if (evt.type == SDL_KEYDOWN) {
	            switch (evt.key.keysym.sym) {
	                case SDLK_UP:
	                	if (r2.y > 0) {
	                		r2.y -= 10;
						} else {
							r2.y=0;
						}
	                    break;
	                case SDLK_DOWN:
	                	if (r2.y+20 < 700) {
	                    	r2.y += 10;
	                	} else {
	                		r2.y=680;
						}
	                    break;
	                case SDLK_LEFT:
	                	if (r2.x > 0) {
	                    	r2.x -= 10;
	                	} else {
	                		r2.x=0;
						}
	                    break;
	                case SDLK_RIGHT:
	                	if (r2.x+100 < 1000) {
	                    	r2.x += 10;
	                	} else {
	                		r2.x = 900;
						}
	                    break;
	            }
	        } else if (evt.type == SDL_MOUSEMOTION) {
				r3.x = evt.motion.x;
				r3.y = evt.motion.y;
			}
		}
		if (espera == 0) {
		
			espera = 25;
			if (r1.x < 800 && r1.y == 100)
				r1.x++;
			else if (r1.y < 450 && r1.x == 800) 
				r1.y++;
			else if (r1.x > 100)
				r1.x--;
			else
				r1.y--;
		}
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
