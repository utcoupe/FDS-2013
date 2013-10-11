/*******************************
* Quentin CHATEAU pour UTCOUPE *
* quentin.chateau@gmail.com    *
* Last edition : 30/09/2013    *
*******************************/

#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <stdlib.h>
#include <urg_utils.h>
#include <math.h>
#include "global.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

#define PI 3.14159265358979323846264338327950288

struct coord{
	int x;
	int y;
};

enum action{get, calculate};

double f_sin(enum action action, urg_t *urg, int index);
double f_cos(enum action action, urg_t *urg, int index);
void set_sin_cos(urg_t *urg);

int dist_to_edge(struct coord p);
int dist(struct coord p1, struct coord p2);

#endif
