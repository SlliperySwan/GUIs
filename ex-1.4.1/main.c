#include <SDL.h>

struct coord {
	int x;
	int y;
};

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um RetÃ¢ngulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÃ‡ÃƒO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    int retC = 0, i = 0, j;
    struct coord retangulos[10];
    SDL_Rect D = {0,0,5,8};
    
    while (!SDL_QuitRequested()) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        for (j = 0; j < retC; j++) {
        	D.x = retangulos[j].x;
        	D.y = retangulos[j].y;
        	SDL_SetRenderDrawColor(ren, 255-25*j,0, 25*j, 255);
        	SDL_RenderFillRect(ren, &D);
		}
		SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
		
        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                	if (r.y > 0) {
                		r.y -= 5;
					} else {
						r.y=0;
					}
                    break;
                case SDLK_DOWN:
                	if (r.y+10 < 100) {
                    	r.y += 5;
                	} else {
                		r.y=90;
					}
                	 
                    break;
                case SDLK_LEFT:
                	if (r.x > 0) {
                    	r.x -= 5;
                	} else {
                		r.x=0;
					}
                    break;
                case SDLK_RIGHT:
                	if (r.x+10 < 200) {
                    	r.x += 5;
                	} else {
                		r.x = 190;
					}
                    break;
            }
        }
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
        	switch (evt.button.button) {
        		case SDL_BUTTON_LEFT:
        			retangulos[i%10].x = evt.button.x;
        			retangulos[i%10].y = evt.button.y;
        			i++;
        			retC++;
        			if (retC >= 10) {
        				retC=10;
					}
					break;
			}
		}
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
