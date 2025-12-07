#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int	setup_WindowRenderer(SDL_Window **window, SDL_Renderer **renderer, SDL_RendererInfo *renderer_info)
{
	*window = SDL_CreateWindow("Ramdom Walk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								640, 480, SDL_WINDOW_SHOWN);
	if (!(*window))
	{
		fprintf(stderr, "Error while creating the window : %s\n", SDL_GetError());
		SDL_Quit();
		return (-1);	
	}
	// Initialize the renderer using the GPU
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (!(*renderer))
	{
		fprintf(stderr, "Using GPU Accel failed : %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return (-1);
	}
	int ret = SDL_GetRendererInfo(*renderer, renderer_info);
	if (ret != 0)
	{
		fprintf(stderr, "Getting renderer's info failed : %s\n", SDL_GetError());
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return (-1);
	}
	if (renderer_info->flags & SDL_RENDERER_ACCELERATED)
		printf("Renderer is using the GPU\n");
	else
		printf("Renderer is using software rendering\n");
	return (0);
}

void	display_rectangles(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Rect rect = {100, 100, 50, 50};

	SDL_SetRenderDrawColor(renderer, 255, 127, 40, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	SDL_Delay(500);
	rect.x = 50;
	rect.y = 50;
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}

int	set_window_color(SDL_Renderer *renderer, SDL_Color color)
{
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
		return (-1);
	if (SDL_RenderClear(renderer) < 0)
		return (-1);
	return (0);
}
// Ajouter le delay puis changet le fond avec set window color
int main (void)
{
    SDL_Window			*window = NULL;
	SDL_Renderer		*renderer = NULL;
	SDL_RendererInfo	renderer_info;

	//	Initialize SDL services
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error while initializing SDL : %s\n", SDL_GetError());
		SDL_Quit();
		return (EXIT_FAILURE);
	}
	// Setup the window and the renderer
	if (setup_WindowRenderer(&window, &renderer, &renderer_info) != 0)
		return (EXIT_FAILURE);
	display_rectangles(window, renderer);
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return (EXIT_SUCCESS);
}