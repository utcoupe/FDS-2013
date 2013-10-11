/*******************************
* Quentin CHATEAU pour UTCOUPE *
* quentin.chateau@gmail.com    *
* Last edition : 30/09/2013    *
*******************************/

#include "analyzer.h"

int init(urg_t *urg){
	char *device = "/dev/ttyACM0";
	int error;
	int i;

//SERIAL PORT DETECTION
	printf("List of serial ports :\n");
	int found_port_size = urg_serial_find_port();
	if (found_port_size == 0) {
		printf("could not found serial ports.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < found_port_size; ++i) {
		printf("%s", (char *)urg_serial_port_name(i));
		if (urg_serial_is_urg_port(i)) {
			device = (char *)urg_serial_port_name(i);
			printf(" [URG]");
		}
		printf("\n");
	}
	printf("\n");

	printf("Connection à %s\n", device);
	error = urg_open(urg, URG_SERIAL, device, BAUDRATE);
	if(error < 0){
		error_func(urg, "connection failed");
	}
	else{
		printf("Connection établie à %s\n", device);
		urg_set_scanning_parameter(urg, urg_rad2step(urg, -PI/2), urg_rad2step(urg, PI/2), 0);//scan en continu, on ne garde que les point entre -PI/2 et PI/2
		printf("Parameters set\n");
		error = urg_start_measurement(urg, URG_DISTANCE, URG_SCAN_INFINITY, 0);
		if(error < 0){
			error_func(urg, "failed to start measurement");
		}
	}
	set_sin_cos(urg);//calcule les tables de cos/sin à l'avance
	return error;
}

int get_points_2d(struct urg_params urg, struct coord *points){
	int data_max, n, i;
	long *data;

	data_max = urg_max_data_size(urg.ptr);//aquisition du nombre de points
	data = (long*)malloc(sizeof(long) * data_max);
	if(data == NULL){
		fprintf(stderr, "data malloc error\n");
		exit(1);
	}
	if(points == NULL){
		fprintf(stderr, "get_points_2d : points non alloué\n");
		exit(1);
	}

	n = urg_get_distance(urg.ptr, data, NULL);

	/* CONVERSION EN COORDONNEES */
	for(i=0; i<n; i++){
		
		points[i].x = data[i]*cos(urg_index2rad(urg.ptr, i)) - urg.x; //x
		points[i].y = data[i]*sin(urg_index2rad(urg.ptr, i)) - urg.y; //y
		
		/*
		points[i].x = data[i]*f_cos(get, urg.ptr, i) - urg.x; //x
		points[i].y = data[i]*f_sin(get, urg.ptr, i) - urg.y; //y
		*/
		if(urg.side == BLUE_SIDE){//si blue side, symétrie centrale
			points[i].x = LX - points[i].x;
			points[i].y = LY - points[i].y;
		}
	}
	free(data);//free raw datas

	return n;
}

int get_robots_2d(struct coord *robot_pos, struct coord *points, int n){
	/****************/
	/* DECLARATIONS */
	/****************/
	int groups_counter = 0, group_index;//groups_counter initialisé à 0 si il n'y a pas de groupes
	int valid_groups_counter = 0;//pas de groupes valides initialement
	int i, j, init = 1;
	struct points_group points_group[MAX_GROUPS];
	struct coord *groups_pos = NULL;

	/*********************************/
	/* CREATION DE GROUPES DE POINTS */
	/*********************************/

	for(i=0; i<n; i++){//analyse des points
		if(!ignore(points[i])){//si le point n'est pas à ignorer
			if(init){//identique à nouveau group, sauf qu'il est inconditionnel
				groups_counter = 1;
				group_index = groups_counter-1;
				points_group[group_index].first = points_group[group_index].last = points[i]; //on stocke le point dans un nouveau groupe de points
				points_group[group_index].size = 1; //il y a désormais 1 point dans le group
				points_group[group_index].valid = 0; //on initialise le groupe comme non valide par défaut
				init = 0;
			}
			else if(dist(points[i], points_group[group_index].last) <= DIST_DIFF_ROBOT) //si c'est le même groupe
			{
				group_index = groups_counter-1;
				points_group[group_index].last = points[i];//on remplace le deuxième point par le dernier point détecté
				points_group[group_index].size++; //il y un point de plus dans le groupe
			}
			else //enfin, si on change de groupe de point, et que ce dernier est valide (au moins 2 points)
			{
				groups_counter++; //un groupe de plus
				group_index = groups_counter-1;
				points_group[group_index].first = points_group[group_index].last = points[i]; //on stocke le point dans un nouveau groupe de points
				points_group[group_index].size = 1;//1 point dans ce groupe
				points_group[group_index].valid = 0; //invalide par défaut
			}
		}
	}

	/**************************/
	/* TRAITEMENT DES GROUPES */
	/**************************/
	for(i=0; i<groups_counter;i++){
		//LISTE D'EXEPTIONS
		if(points_group[i].size < POINTS_MIN) //si le groupe ne contiens pas au moins POINTS_MIN alors il n'est pas valide
			continue;

		points_group[i].valid = 1;//si le point passe toutes les exceptions, il est valide
		valid_groups_counter++;//un groupe valide de plus
	}

	/*****************************************/
	/* CONVERSION DES GROUPES EN COORDONNEES */
	/*****************************************/

	groups_pos = (struct coord*)malloc(sizeof(struct coord) * valid_groups_counter); //il y aura une coordonnée par groupe valide
	if(groups_pos == NULL){
		fprintf(stderr, "groups_pos : malloc error");
		exit(1);
	}

	j = 0;
	for(i=0; i<groups_counter; i++){
		if(points_group[i].valid == 1){//si le groupe est valide, on calcule ses coordonées
			groups_pos[j].x = (points_group[i].first.x + points_group[i].last.x)/2;//X du robot
			groups_pos[j].y = (points_group[i].first.y + points_group[i].last.y)/2;//Y du robot
			j++;
		}
	}
		
	/***********************************/
	/* SUPPRESSION DES GROUPES EN TROP */
	/***********************************/
	
	while(valid_groups_counter > DETECTABLE_ROBOTS) //si on a plus de groupe de point que de robots
	{
		int dist_min = LX, index_to_delete = 0;
		for(i=0; i<valid_groups_counter; i++){//on repère quel group est le plus proche du bord
			int dist = dist_to_edge(groups_pos[i]);
			if(dist_min > dist){
				dist_min = dist;
				index_to_delete = i;
			}
		}
		for(i=index_to_delete; i<valid_groups_counter ; i++){//on le supprime
			groups_pos[i] = groups_pos[i+1];
		}
		valid_groups_counter--;//on enlève un groupe
	}
	for(i=0; i<valid_groups_counter; i++){
		robot_pos[i] = groups_pos[i];
	}

	return valid_groups_counter;
}

int ignore(struct coord p){
	if(p.x > LX - MIN_DIST_TO_EDGE || p.x < MIN_DIST_TO_EDGE)
		return 1;
	if(p.y > LY - MIN_DIST_TO_EDGE || p.y < MIN_DIST_TO_EDGE)
		return 1;

		// ADD HERE OTHER EXCEPTIONS //
	return 0;
}



void error_func(urg_t *urg, const char *message){
	urg_close(urg);
	fprintf(stderr, "%s :: %s\n", message, urg_error(urg)); //print le message d'erreur perso et celui issu de l'hokuyo
}
