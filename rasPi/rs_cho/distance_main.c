#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
extern float get_distance();

int main (int argc, char *argv[]){

	float distance;
	while(1){
		distance=get_distance();
		printf("main -> get_distance: %.2fcm \n",distance);
	}
	return 0;
}
