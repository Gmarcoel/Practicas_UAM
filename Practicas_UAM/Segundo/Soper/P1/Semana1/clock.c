#include <stdio.h>
#include <time.h>
int main(){
	double t=0;
	while(t<10){
		t = clock()/CLOCKS_PER_SEC;
	}
}
