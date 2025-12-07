#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int	Setup_WindowRenderer(SDL_Window **window, SDL_Renderer **renderer, SDL_RendererInfo *renderer_info)
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
		SDL_Quit();
		return (-1);
	}
	if (renderer_info->flags & SDL_RENDERER_ACCELERATED)
		printf("Renderer is using the GPU\n");
	else
		printf("Renderer is using software rendering\n");
	return (0);
}
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
	if (Setup_WindowRenderer(&window, &renderer, &renderer_info) != 0)
		return (EXIT_FAILURE);
	SDL_Delay(3000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (EXIT_SUCCESS);
}