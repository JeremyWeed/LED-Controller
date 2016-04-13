#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calcThetaWalk(int cur, int target){
	double theta = target - cur;
	theta = theta / 128.0; //this is the amount of "steps" remianing to get to the 
				//desired value, but since this sould run indefinately,
				//its currently hardcoded
	theta = 1.0 - theta;
	theta = theta / 2.0;
	return theta;
}

void setup(){
	srand(time(NULL));
}

void testWalk(){
	int start = 0; 
	printf("enter start: ");
	scanf("%d", &start);
	int cur = start;
	while(1){
		getchar();
		double per = calcThetaWalk(cur, start);
		if(per * 1000 < rand() % 1000){
			cur += 10;
		}else{
			cur -= 10;
		}
		printf("%d, %lf", cur, per);
		
	}
}

static unsigned char scale_c(unsigned char col, unsigned char inten){
	float ratio =  inten / (float) 0xFF;
	printf("%f\n", ratio);
	ratio *= col;
	return (char) ratio;
}

int scale(int num, double scale){
	return (int) ((double) num * scale);
}

double scaleFactor(int startMax, int endMax){
	return (double) startMax / (double) endMax;
}

void testScale_c(){
	int scal = 0;
	double fact = 0;
	printf("enter scale: ");
	scanf(" %d", &scal);
	printf("factor: %f\n", fact);
	while(1){
		int num = 0;
		printf("scales %d between 0 and 255:\nNumber: ", scal);
		scanf("%d", &num);
		printf("entered: %d  Calc: %d\n", num, scale_c(num, scal));
	}
}

void testScale(){
	int scal = 0;
	double fact = 0;
	printf("enter scale: ");
	scanf(" %d", &scal);
	fact = scaleFactor(scal, 255);
	printf("factor: %f\n", fact);
	while(1){
		int num = 0;
		printf("scales %d between 0 and 255:\nNumber: ", scal);
		scanf("%d", &num);
		printf("entered: %d  Calc: %d\n", num, scale(num, fact));
	}
}

void testColorScale(){
	double scaleFact[3];
	int color[3];
	printf("Enter color code: ");
	scanf(" %d %d %d", &color[0], &color[1], &color[2]);
	scaleFact[0] = scaleFactor(color[0], 255);
	scaleFact[1] = scaleFactor(color[1], 255);
	scaleFact[2] = scaleFactor(color[2], 255);
	printf("Factor: {%f, %f, %f}", scaleFact[0], scaleFact[1], scaleFact[2]);

	while(1){
		int num = 0;
		printf("Enter scaling factor between 0 and 255: ");
		scanf("%d", &num);
		printf("Color: {%d, %d, %d}", scale(num, scaleFact[0]), scale(num, scaleFact[1]), scale(num, scaleFact[2]));
	}
}

int main(){
	//setup();
	testScale_c();
	return 0;
}