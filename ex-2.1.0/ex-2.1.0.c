#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 700

typedef struct Objeto {
	int n;
	SDL_Point local;
} Objeto;

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

void eventGenerator(int n) {
	SDL_Event new_evt;
    SDL_UserEvent u_evt;
    u_evt.type = SDL_USEREVENT;
    u_evt.code = n;
    u_evt.data1 = NULL;
    u_evt.data2 = NULL;
    new_evt.user = u_evt;
    SDL_PushEvent(&new_evt);
}

void multiClickEvent(SDL_Event * evt, int * contagemDeClicks, int * contando, Uint32 * ultimoClick, SDL_Point * posicao) {
	int posicaoIgual = evt->button.x == posicao->x && evt->button.y == posicao->y;
	switch (evt->type) {
		case SDL_MOUSEBUTTONDOWN:
			if (!(*contando)) {
				*contando = 1;
				*ultimoClick = SDL_GetTicks();
				*posicao = (SDL_Point){evt->button.x,evt->button.y};
				*contagemDeClicks = 1;
			} else {
				if (posicaoIgual && SDL_GetTicks()-*ultimoClick < 250) {
					*ultimoClick = SDL_GetTicks();
					(*contagemDeClicks)++;
				} else {
				    *contando = 0;
					eventGenerator(*contagemDeClicks);
				}
			}
			break;
		case SDL_MOUSEMOTION:
			if (*contando) {
				*contando = 0;
				eventGenerator(*contagemDeClicks);
				break;
			}
		default:
			if (*contando && SDL_GetTicks()-*ultimoClick >= 250) {
				*contando = 0;
				eventGenerator(*contagemDeClicks);
			}
			break;
	}

}

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("ex-2.1.0",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         WIDTH, HEIGHT, SDL_WINDOW_SHOWN
                      	);
    SDL_Renderer* ren = SDL_CreateRenderer(window, -1, 0);
    
    Uint32 espera = 25;
    SDL_Event evt;
    
    int contagemDeClicks = 0,
    	contando = 0;
    SDL_Point local = {0,0};
    Uint32 ultimoClick = 0;
    
    Objeto colecao[30];
    int oCount = 0;
    while (!SDL_QuitRequested()) {
     	int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
     	multiClickEvent(&evt,&contagemDeClicks,&contando,&ultimoClick,&local);
        if (isevt) {
        	if (evt.type == SDL_USEREVENT && evt.user.code > 1) {
    			colecao[oCount%30].n = evt.user.code;
				colecao[oCount%30].local =(SDL_Point){local.x,local.y};
				oCount++;
			}
        }

		if (espera == 0) {
			espera = 25;
			SDL_SetRenderDrawColor(ren,255,255,255,255);
			SDL_RenderClear(ren);
			int i;
			for (i = 0; i < ((oCount>30)?30:oCount); i++) {
				filledCircleRGBA(ren,colecao[i].local.x,colecao[i].local.y,colecao[i].n*10,255-(colecao[i].n)%256*25,0,colecao[i].n%256*25,255);
			}
			char stringao[1000];
			sprintf(stringao,"%d %d %d %d %d %d",contando,contagemDeClicks,ultimoClick,local.x,local.y,oCount);
			stringRGBA(ren,100,100,stringao,255,0,0,255);
			SDL_RenderPresent(ren);
		}
    }
    
    
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
