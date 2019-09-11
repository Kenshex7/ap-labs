#include <stdio.h>

void vaciarPalabra(char palabra[]);
void voltearPalabra(char palabra[], int f);

int main(){
	char palabra[30];
	char ch;
	int i=0;
		while((ch = getchar())!= EOF){
			if((ch!='\n') && i<29){
				palabra[i++]=ch;
			}
			else{
				voltearPalabra(palabra,i-1);
				printf("Palabra volteada:\n%s \n", palabra);
				i=0;
				vaciarPalabra(palabra);
			}	
		}
		printf("%s",palabra);
    return 0;
}

void vaciarPalabra(char palabra[]){
	for (int i = 0; i < 29; ++i)
	{
		palabra[i]=NULL;
	}
}

void voltearPalabra(char palabra[], int f){
	int i=0;
	char swp;
	while(i<f){
		swp=palabra[i];
		palabra[i]=palabra[f];
		palabra[f]=swp;
		i++;
		f--;
	}
}