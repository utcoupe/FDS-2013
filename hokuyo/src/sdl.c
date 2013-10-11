/*******************************
* Quentin CHATEAU pour UTCOUPE *
* quentin.chateau@gmail.com    *
* Last edition : 30/09/2013    *
*******************************/

#include "sdl.h"

void affichage_sdl(struct urg_params hokuyo){
	struct coord data[DATA_MAX], robots_pos[DETECTABLE_ROBOTS];
	int i, n_data, n_robots, continuer = 1;

	//INITIALISATION DES ELEMENTS SDL

	//Initialisation de la fenetre
	SDL_Surface *ecran = NULL, *sdl_points, *sdl_robots;
	SDL_Rect sdl_points_position[DATA_MAX], sdl_robots_position[DETECTABLE_ROBOTS];
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;
	ecran = SDL_SetVideoMode(X_WINDOW_RESOLUTION, Y_WINDOW_RESOLUTION, 32, SDL_HWSURFACE);
	if(ecran == NULL){
		fprintf(stderr, "Erreur chargement SDL");
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("Hokuyo", NULL);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	//Creation des points et des robots
	sdl_points = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 3, 32, 0, 0, 0, 0);
	SDL_FillRect(sdl_points, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
	sdl_robots = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(sdl_robots, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	printf("SDL Initialized\n");
	
	//RECUPERATION ET AFFICHAGE DES POINTS
	while(continuer){
		SDL_PollEvent(&event); // On doit utiliser PollEvent car il ne faut pas attendre d'évènement de l'utilisateur pour mettre à jour la fenêtre
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
			        break;
		}
		//Recuperation des poins
		n_data = get_points_2d(hokuyo, data);
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 200, 200, 200));//on clean l'ecran
		//Recuperation des robots
		n_robots = get_robots_2d(robots_pos, data, n_data);
		for(i=0;i<n_robots;i++){
			//affichage des robots
			sdl_robots_position[i].x = (robots_pos[i].x*X_WINDOW_RESOLUTION)/LX;
			sdl_robots_position[i].x -= 30/2; //pour que le robot soit CENTRE sur son point
			sdl_robots_position[i].y = Y_WINDOW_RESOLUTION - (Y_WINDOW_RESOLUTION/2 + robots_pos[i].y*Y_WINDOW_RESOLUTION)/LY;//attention, l'origine en SDL est en haut à gauche
			sdl_robots_position[i].y -= 30/2; //pour que le robot soit CENTRE sur son point
			SDL_BlitSurface(sdl_robots, NULL, ecran, &sdl_robots_position[i]);
		}
		for(i=0;i<n_data;i++){
			//affichage des points
			sdl_points_position[i].x = (data[i].x*X_WINDOW_RESOLUTION)/LX;
			sdl_points_position[i].y = Y_WINDOW_RESOLUTION - (Y_WINDOW_RESOLUTION/2 + data[i].y*Y_WINDOW_RESOLUTION)/LY;//attention, l'origine en SDL est en haut à gauche
			SDL_BlitSurface(sdl_points, NULL, ecran, &sdl_points_position[i]);
		}
		SDL_Flip(ecran);
	}
	SDL_FreeSurface(sdl_points);
	SDL_FreeSurface(sdl_robots);
	SDL_Quit();
}
