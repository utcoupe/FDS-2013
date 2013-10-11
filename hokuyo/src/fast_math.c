/*******************************
* Quentin CHATEAU pour UTCOUPE *
* quentin.chateau@gmail.com    *
* Last edition : 30/09/2013    *
*******************************/

#include "fast_math.h"

double f_sin(enum action action, urg_t *urg, int index){
	static double sin_table[DATA_MAX];
	if(action == get)
		return sin_table[index];
	else{
		int i,n;
		n = urg_max_data_size(urg);
		for(i=0;i<n;i++){
			sin_table[i] = sin(urg_index2rad(urg, i));
		}
		return (double)n;
	}
}

double f_cos(enum action action, urg_t *urg, int index){
	static double cos_table[DATA_MAX];
	if(action == get)
		return cos_table[index];
	else{
		int i,n;
		n = urg_max_data_size(urg);
		for(i=0;i<n;i++){
			cos_table[i] = cos(urg_index2rad(urg, i));
		}
		return (double)n;
	}
}

void set_sin_cos(urg_t *urg){
	f_cos(calculate, urg, 0);
	f_sin(calculate, urg, 0);
}

int dist_to_edge(struct coord p){
	int x_to_edge = min(p.x, LX - p.x);
	int y_to_edge = min(p.y, LY - p.y);
	int res = min(x_to_edge, y_to_edge);
	return res;
}

int dist(struct coord p1, struct coord p2){
	int res = abs(p1.x - p2.x) + abs(p1.y - p2.y); //distance = abs( ( x1 - x2 ) + ( y1 - y2) )
	return res;
}
