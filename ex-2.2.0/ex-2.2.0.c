#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 700

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

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("ex-2.2.0",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         WIDTH, HEIGHT, SDL_WINDOW_SHOWN
                      	);
    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
    
    
    SDL_Rect r = {100,100,50,50};
    SDL_Point posInicialRect = {100,100}, posInicialClick;
    int clickInicial, pressionando = 0, state = 0;
    
    Uint32 espera = 16;
    SDL_Event evt;
    const Uint8 * tecP = SDL_GetKeyboardState(NULL);
    while (!SDL_QuitRequested()) {
     	int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
     	if (isevt) {
     		switch (evt.type) {
     			case SDL_KEYDOWN:
				case SDL_KEYUP:
					if (state == 2 && tecP[SDL_SCANCODE_ESCAPE]) {
						r.x = posInicialRect.x;
						r.y = posInicialRect.y;
						pressionando = 0;
						state = 3;
					}
					break;
     			case SDL_MOUSEBUTTONDOWN:
     				clickInicial = SDL_GetTicks();
     				posInicialRect = (SDL_Point){r.x,r.y};
     				posInicialClick = (SDL_Point){evt.button.x,evt.button.y};
     				if (r.x <= evt.button.x && evt.button.x <= r.x+r.w && r.y <= evt.button.y && evt.button.y <= r.y+r.h) {
     					pressionando = 1;
					}
     				break;
     			case SDL_MOUSEBUTTONUP:
     				posInicialRect.x = r.x;
					posInicialRect.y = r.y;
     				if (evt.button.x == posInicialClick.x && evt.button.y == posInicialClick.y)
     					state = 1;
					if (state == 2)
						state = 4;
					pressionando = 0;
					break;
				case SDL_MOUSEMOTION:
     				if (pressionando == 1 && (evt.button.x != posInicialClick.x || evt.button.y != posInicialClick.y)) {
     					state = 2;
     					r.x = posInicialRect.x+(evt.button.x-posInicialClick.x);
     					r.y = posInicialRect.y+(evt.button.y-posInicialClick.y);
					}
					break;
			}
		}
		if (espera == 0) {
			espera = 16;
			SDL_SetRenderDrawColor(ren,255,255,255,255);
			SDL_RenderClear(ren);
			SDL_SetRenderDrawColor(ren,0,0,255,255);
			SDL_RenderFillRect(ren, &r);
			switch (state) {
				case 0:
					break;
				case 1:
					stringRGBA(ren,3,3,"Clicou!",0,0,0,255);
					break;
				case 2:
					stringRGBA(ren,3,3,"Arrastando...",0,0,0,255);
					break;
				case 3:
					stringRGBA(ren,3,3,"Acao cancelada.",0,0,0,255);
					break;
				case 4:
					stringRGBA(ren,3,3,"Soltou!",0,0,0,255);
					break;
			}
			SDL_RenderPresent(ren);
		}
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
