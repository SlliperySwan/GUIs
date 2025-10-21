#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

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

void segmentoLinhaDeChegada(SDL_Renderer * ren, int x, int y) {
	int i, j;
	SDL_Rect r = {0,0,30,30};
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			r.x = x+i*30;
			r.y = y+j*30;
			SDL_SetRenderDrawColor(ren,255*((i+j)%2),255*((i+j)%2),255*((i+j)%2),255);
			SDL_RenderFillRect(ren,&r);
		}
	}
}

void linhaDeChegada(SDL_Renderer * ren, int x, int height) {
	int j;
	for (j = 0; j < height; j+=60) {
		segmentoLinhaDeChegada(ren,x,j);
	}
}

int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("ex-1.6.0",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         WIDTH, HEIGHT, SDL_WINDOW_SHOWN
                      	);
    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
	
	while (!SDL_QuitRequested()) {
		struct coord p1 = {.x = 100, .y = 100},
					 p2 = {.x = 100, .y = 350},
					 p3 = {.x = 100, .y = 600};
	    SDL_Rect r1 = {p1.x,p1.y,100,20},
				 r2 = {p2.x,p2.y,100,20},
				 r3 = {p3.x,p3.y,100,20};
	    int podeMover[] = {1,1,1},
	        terminou = 0,
	        chegouPrimeiro = -1;
	    
	    Uint32 espera = 25;
	    SDL_Event evt;
	    
	    while (terminou != 3 && !SDL_QuitRequested()) {
	        SDL_SetRenderDrawColor(ren, 0,0xFF,0,0x00);
	        SDL_RenderClear(ren);
	        linhaDeChegada(ren,800,HEIGHT);
	        if (r1.x >= 800 && podeMover[0]) {
	        	podeMover[0] = 0;
	        	chegouPrimeiro = (chegouPrimeiro!=-1)?chegouPrimeiro:0;
	        	terminou++;
	        } 
			if (r2.x >= 800 && podeMover[1]) {
	        	podeMover[1] = 0;
	        	chegouPrimeiro = (chegouPrimeiro!=-1)?chegouPrimeiro:1;
	        	terminou++;
	        } 
			if (r3.x >= 800 && podeMover[2]) {
	        	podeMover[2] = 0;
	        	chegouPrimeiro = (chegouPrimeiro!=-1)?chegouPrimeiro:2;
	        	terminou++;
	    	}
	        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
	        if (isevt) {
		        if (evt.type == SDL_KEYDOWN && podeMover[1]) {
		            switch (evt.key.keysym.sym) {
		                case SDLK_LEFT:
		                	if (r2.x > 0) {
		                    	r2.x -= 8;
		                	} else {
		                		r2.x=0;
							}
		                    break;
		                case SDLK_RIGHT:
		                	if (r2.x+100 < WIDTH) {
		                    	r2.x += 8;
		                	} else {
		                		r2.x = WIDTH-100;
							}
		                    break;
		            }
		        } else if (evt.type == SDL_MOUSEMOTION && podeMover[2]) {
					r3.x = (evt.motion.x>WIDTH-100)?WIDTH-100:evt.motion.x;
				}
			}
			if (espera == 0) {
				espera = 25;
				if (podeMover[0])
					r1.x+=3;
				SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
		        SDL_RenderFillRect(ren, &r1);
		        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
		        SDL_RenderFillRect(ren, &r2);
		        SDL_SetRenderDrawColor(ren, 0xFF,0xAA,0x00,0x00);
		        SDL_RenderFillRect(ren, &r3);
		        stringRGBA(ren,r1.x+46,r1.y+6,"1",255,255,255,255);
		        stringRGBA(ren,r2.x+46,r2.y+6,"2",255,255,255,255);
		        stringRGBA(ren,r3.x+46,r3.y+6,"3",255,255,255,255);
		        SDL_RenderPresent(ren);
			}
		}
		if (terminou == 3) {
			Uint32 primeiroFrame = SDL_GetTicks();
			char string[20],timer[22];
			sprintf(string,"O carro %d ganhou!",chegouPrimeiro+1);
			while (SDL_GetTicks()-primeiroFrame < 3000) {
				Uint32 ultimoFrame = SDL_GetTicks();
				if ((SDL_GetTicks()-ultimoFrame)%50 == 0) {
					ultimoFrame = SDL_GetTicks();
					sprintf(timer,"Reiniciando em %2.1fs",(3000-(float)(SDL_GetTicks()-primeiroFrame))/1000);
					boxRGBA(ren,WIDTH/2-100,HEIGHT/2-9,WIDTH/2+100,HEIGHT/2+16,0,0,0,255);
					rectangleRGBA(ren,WIDTH/2-100,HEIGHT/2-9,WIDTH/2+101,HEIGHT/2+17,255,255,255,255);
					stringRGBA(ren,WIDTH/2-69,HEIGHT/2-6,string,255,255,255,255);
					stringRGBA(ren,WIDTH/2-77,HEIGHT/2+5,timer,255,255,255,255);
					SDL_RenderPresent(ren);
				}
			}
		}
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
