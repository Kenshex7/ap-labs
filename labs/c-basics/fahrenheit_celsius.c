#include <stdio.h>

/* print Fahrenheit-Celsius table */

int main(int argc, char **argv[])
{
	int fahr;
	int low, up, inc;
	if(argc==4){
		low=atoi(argv[1]);
		up=atoi(argv[2]);
		inc=atoi(argv[3]);
		for (fahr = low; fahr <= up; fahr = fahr + inc)
			printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	}
	if(argc==2){
		fahr=atoi(argv[1]);
		printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	}
	else if(argc==3 || argc<2 || argc>4){
		printf("Invalid syntax, you have to use the input like:\n./fahrenheit_celsius lowLimit UpLimit increment\nOr ./fahrenheit_celsius fahrDegreess");
	}
	return 0;
}

