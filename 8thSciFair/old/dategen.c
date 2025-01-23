#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int* dategen();

int main(int argc, char* argv) {
	int* date = dategen();
	printf("%i/%i/%i\n", date[0],date[1],date[2]);
	free(date);
	return 0;
}

int* dategen() {
	srand(time(NULL));
	int m = rand() % (12 + 1);
	int y = rand() % (2025 - 2000 + 1) + 2000;

	// this fucking suxxxxxxx
	// basically just calculates how many days are in a month
	int ud;
	if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) {
		ud = 31;
	} else if(m==4 || m==6 || m==9 || m==11) {
		ud = 30;
	} else {
		// calc if leap year (calc is short for calculator for those new to the stream)
		if(y % 4 == 0) {
			if(y % 100 == 0 && y % 400 == 0) {
				ud = 29;
			} else {
				ud = 28;
			}
		} else {
			ud = 28;
		}
	}

	int d = rand() % (ud - 1 + 1) + 1;

	int* r = (int*)malloc(sizeof(int) * 3);
	r[0] = d;
	r[1] = m;
	r[2] = y;

	return r;
}
