#include <SDL.h>


#define WIDTH 1000
#define HEIGHT 700


int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * window = SDL_CreateWindow("ex-1.3.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer * ren = SDL_CreateRenderer(window, -1, 0);
	
	SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
	
	int i, x = 0, y = 0, CX = WIDTH/2, CY = HEIGHT/2;
	SDL_Rect rect1 = {CX-50, CY-50, 25, 25};
	SDL_Rect rect2 = {CX+50, CY+50, 25, 25};
	SDL_Rect outerBox = {CX-51, CY-51, 127, 127};
	SDL_Rect innerBox = {CX-25, CY-25, 75, 75};
	
	for (i = 0; i < 80+1; i++) {
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		
		SDL_SetRenderDrawColor(ren,255,255,255,255);
		SDL_RenderDrawRect(ren, &outerBox);
		SDL_RenderDrawRect(ren, &innerBox);
		
		SDL_SetRenderDrawColor(ren,0,0,255,255);
		SDL_RenderFillRect(ren, &rect1);
		SDL_SetRenderDrawColor(ren,255,0,0,255);
		SDL_RenderFillRect(ren, &rect2);
		
		if (i < 20) {
			rect1.x += 5;
			rect2.x -= 5;
		} else if (i < 40) {
			rect1.y += 5;
			rect2.y -= 5;
		} else if (i < 60) {
			rect1.x -= 5;
			rect2.x += 5;
		} else {
			rect1.y -= 5;
			rect2.y += 5;
		}
		
		SDL_RenderPresent(ren);
		if (i == 0) {
			SDL_Delay(1450);
		}
		SDL_Delay(50);
	}
	SDL_Delay(1500);
	
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
