#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

void clear();
void readFile();

int main(){
  // Place your magic here
	int fd;
	struct dirent *de;
	char *direct=(char*)calloc(10,sizeof(char));
	char *pth=(char*)calloc(10,sizeof(char));
	int cont;
	
	for(;;){
		printf("|PID\t|Parent\t|Name\t\t|State\t\t|Memory\t\t|# Threads\t|Open Files\t|\n");
		DIR *dr=opendir("/proc");

		if(dr==NULL){
			printf("Could not open current directory\n");
			return 1;
		}
		cont=0;
		while((de=readdir(dr))!=NULL){
			//printf("%s\n", de->d_name);

			struct stat st;

			if (fstatat(dirfd(dr), de->d_name, &st, 0) < 0)
	        {
	            perror(de->d_name);
	            continue;
	        }
	        if (S_ISDIR(st.st_mode)){
	        	if(cont>15){
		        	strcpy(direct,"/proc/");
					strcat(direct,de->d_name);
					strcat(direct,"/status");     
					//printf("El directorio es: %s\n", direct);  	
		        	fd=open(direct,O_RDONLY);
					if(fd==-1){
						printf("Error opening file\n");
						return 1;
					}
					else{
						readFile(fd);
					}
				} 
	        cont++;
	        }
		}
		sleep(1);
		clear();
		closedir(dr);
	}
  	return 0;
}

void clear() {
  printf("\e[1;1H\e[2J"); 
}

void readFile(int fd){
	int rd;
	char *buff=(char*)calloc(10,sizeof(char));
	char *archivo=(char*)calloc(10000,sizeof(char));
	char *texto=(char*)calloc(10000,sizeof(char));
	char *token;
	char *PID=(char*)calloc(20,sizeof(char));
	char *Parent=(char*)calloc(20,sizeof(char));
	char *Name=(char*)calloc(20,sizeof(char));
	char *State=(char*)calloc(20,sizeof(char));
	char *Memory=(char*)calloc(20,sizeof(char));
	char *Threads=(char*)calloc(20,sizeof(char));
	char *oFiles=(char*)calloc(20,sizeof(char));

	while(rd=read(fd,buff,1)>0){
		strcat(archivo,buff);
	}
	strcpy(texto,archivo);
	token=strtok(texto," ");
	token=strtok(token,"\t");
	token=strtok(NULL,"\n");
	strcpy(Name,token);
	//Hasta aqui guarda el Name
	strcpy(texto,archivo);
	token=strtok(texto,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\t");
	token=strtok(NULL,"\t");
	token=strtok(token,"\n");
	strcpy(State,token);
	//Hasta aqui guarda el State
	strcpy(texto,archivo);
	token=strtok(texto,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\t");
	token=strtok(NULL,"\t");
	token=strtok(token,"\n");
	strcpy(PID,token);
	//Hasta aqui se guarda el PID
	strcpy(texto,archivo);
	token=strtok(texto,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\t");
	token=strtok(NULL,"\t");
	token=strtok(token,"\n");
	strcpy(Parent,token);
	//Hasta aqui se guarda el Parent
	strcpy(texto,archivo);
	token=strtok(texto,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\t");
	token=strtok(NULL,"\t");
	token=strtok(token,"\n");
	strcpy(oFiles,token);
	//Hasta aqui se guardan los OPEN FILES
	strcpy(texto,archivo);
	token=strtok(texto,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\t");
	token=strtok(NULL,"\t");
	token=strtok(token,"\n");
	strcpy(Memory,token);
	//Hasta aqui se guarda la Memory
	strcpy(texto,archivo);
	token=strtok(texto,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\n");
	token=strtok(NULL,"\t");
	token=strtok(NULL,"\t");
	token=strtok(token,"\n");
	strcpy(Threads,token);
	//Hasta aqui se guardan los Threads

	printf("|%s\t", PID);
	printf("|%s\t", Parent);
	printf("|%s\t", Name);
	printf("|%s\t", State);
	printf("|%s\t", Memory);
	printf("|%s\t\t", Threads);
	printf("|%s\t\t|\n", oFiles);
}
