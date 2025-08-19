#include <SDL2/SDL.h>

void desenharFlor(SDL_Renderer * ren, int x, int y, int r, int g, int b) {
    SDL_SetRenderDrawColor(ren, r, g, b, 0);
    SDL_Rect h = {x, y, 5, 7};
    SDL_RenderFillRect(ren, &h);

    SDL_SetRenderDrawColor(ren, r+20, g+20, b+20, 0);
    SDL_Rect a = {x+5, y+7, 7, 5};
    SDL_RenderFillRect(ren, &a);

    SDL_SetRenderDrawColor(ren, r, g, b, 0);
    SDL_Rect f = {x+12, y, 5, 7};
    SDL_RenderFillRect(ren, &f);
    
    SDL_SetRenderDrawColor(ren, r-20, g-20, b-20, 0);
    SDL_Rect c = {x+5, y-3, 7, 3};
    SDL_RenderFillRect(ren, &c);

    SDL_SetRenderDrawColor(ren, 255, 255, 0, 0);
    SDL_Rect d = {x+5, y, 7, 7};
    SDL_RenderFillRect(ren, &d);

    SDL_SetRenderDrawColor(ren, 0, 200, 0, 0);
    SDL_Rect e = {x+7, y+12, 3, 6};
    SDL_RenderFillRect(ren, &e);
}
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Hello World!",
                         0,
                         0,
                         1320, 700, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_SetRenderDrawColor(ren, 0x00,0x66,0xFF,0x00);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0x66,0x00);
    SDL_Rect r = { 0,0, 1000,300 };
    SDL_RenderFillRect(ren, &r);

    SDL_SetRenderDrawColor(ren, 0x33,0x33,0x00,0x00);
    SDL_Rect a = { 200,200, 100,100 };
    SDL_RenderFillRect(ren, &a);

    SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
    SDL_Rect b = { 205,205, 90,95 };
    SDL_RenderFillRect(ren, &b);

    SDL_SetRenderDrawColor(ren, 0x66,0x44,0,0x00);
    SDL_Rect c = { 205,205, 85,95 };
    SDL_RenderFillRect(ren, &c);

    SDL_SetRenderDrawColor(ren, 0,0,0,0x00);
    SDL_Rect d = { 275,248, 5,5 };
    SDL_RenderFillRect(ren, &d);

    SDL_SetRenderDrawColor(ren, 0x55,0x33,0,0x00);
    SDL_Rect e = { 285,205, 5,95 };
    SDL_RenderFillRect(ren, &e);

    SDL_SetRenderDrawColor(ren, 0,0x66,0,0x00);
    SDL_Rect f = { 0,300, 1320,400 };
    SDL_RenderFillRect(ren, &f);
    
    int i,j;
    for(i = 0; i < 30; i++) {
        for(j = 0; j < 10; j++) {
            desenharFlor(ren, (500+337*(i+j))%1320, 300+(258*(j*i))%400, 210-j*15, (30+j*i)%100, 20+j*20);
        }
    }




    SDL_RenderPresent(ren);
    SDL_Delay(5000);

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
