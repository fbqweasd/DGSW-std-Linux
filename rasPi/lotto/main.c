#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int test_n(int *arr);

int main(){
	int lotto[7];
	int i;
	srand(time(NULL));

	for(i=0;i<7;i++){
		lotto[i]=rand()%45+1;
	}

	hi:

	for(i=0;i<7;i++) printf("%d ",lotto[i]);
	printf("\n");

	if(test_n(lotto)){
		goto hi;
	}

	for(i=0;i<7;i++)
		printf("%d ",lotto[i]);
	printf("\n");
	return 0;
}

int test_n(int *arr){
	int i,j;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if(i != j && arr[i] == arr[j])
				arr[i]=rand()%45+1;
				return 1;
		}
	}
	return 0;
}
