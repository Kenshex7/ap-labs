#include <stdio.h>
#include <string.h>

#define REPORT_FILE "packages_report.txt"

typedef struct{
	char name[50];
	char instDate[50];
	char upgrDate[50];
    int upgrNum;
	char remvDate[50];
}package;

void analizeLog(char *logFile, char *report);


int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./pacman-analizer.o pacman.log\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);
    package Packages[1000];
    int j;
    char markup[50];
    for (j = 0; j < 1000; ++j)
    {
        Packages[j].name[0]='\0'; 
        Packages[j].instDate[0]='\0';
        Packages[j].upgrDate[0]='\0';
        Packages[j].remvDate[0]='\0';
    }
    int i=0;
    // Implement your solution here.
    int pInst=0,pUpgr=0,pRemv=0,pCurr=0;
    FILE *origen;
    FILE *destino;
    origen=fopen(logFile,"r");
    destino=fopen(report,"w");
    char buff[1000];
    char tmpDate[50];
    char *line;
    while(fgets(buff,300,(FILE*)origen)){
    	if(strstr(buff,"installed")!=NULL){
            line = strtok(buff," ");
            line++;
            strcpy(Packages[i].instDate,line);
            strcpy(Packages[i].upgrDate,line);
            //printf("package no: %d\n", i);
            //printf("El nombre del elemento de la linea es -%s-\n", line);
            line=strtok(NULL,"]");
            strcat(Packages[i].instDate," ");
            strcat(Packages[i].upgrDate," ");
            //printf("El nombre del siguiente elemento de la linea es -%s-\n", line);
            strcat(Packages[i].instDate,line);
            strcat(Packages[i].upgrDate,line);
            line=strtok(NULL," ");
            line=strtok(NULL," ");
            line=strtok(NULL," ");
            strcpy(Packages[i].name,line);
            //printf("El nombre del elemento de la linea es %s\n", line);
            pInst++;
            i++;
    	}
    	else if(strstr(buff,"upgraded")!=NULL){
            line = strtok(buff," ");
            line++;
            strcpy(tmpDate,line);
            line=strtok(NULL,"]");
            strcat(tmpDate," ");
            strcat(tmpDate,line);
            line=strtok(NULL," ");
            line=strtok(NULL," ");
            line=strtok(NULL," ");
            //Hasta aqui encuentra el nombre
    		strcpy(markup,line);
            j=0;
            while((strcmp(markup,Packages[j].name))){
                j++;
            }
            strcpy(Packages[j].upgrDate,tmpDate);
            Packages[j].upgrNum++;
            pUpgr++;
    	}
    	else if(strstr(buff,"removed")!=NULL){
            line = strtok(buff," ");
            line++;
            strcpy(tmpDate,line);
            line=strtok(NULL,"]");
            strcat(tmpDate," ");
            strcat(tmpDate,line);
            line=strtok(NULL," ");
            line=strtok(NULL," ");
            line=strtok(NULL," ");
            //Hasta aqui encuentra el nombre
            strcpy(markup,line);
            j=0;
            while((strcmp(markup,Packages[j].name))){
                j++;
            }
            strcpy(Packages[j].remvDate,tmpDate);
    		pRemv++;
    	}
    	memset(buff,' ',1000);
    }

    pCurr=pInst-pRemv;
    fprintf(destino,"Pacman Packages Report\n");
    fprintf(destino,"----------------------\n");
    fprintf(destino,"- Installed Packages\t: %d\n", pInst);
    fprintf(destino,"- Removed Packages\t: %d\n", pRemv);
    fprintf(destino,"- Upgraded Packages\t: %d\n", pUpgr);
    fprintf(destino,"- Current Installed\t: %d\n\n", pCurr);
    fprintf(destino,"List Of Packages\n");
    fprintf(destino,"----------------\n");
    i=0;
    while(Packages[i].name[0]!='\0'){
    	fprintf(destino,"-Package Name\t: %s\n", Packages[i].name);
    	fprintf(destino,"   -Install Date\t: %s\n", Packages[i].instDate);
    	fprintf(destino,"   -Last Update Date\t: %s\n", Packages[i].upgrDate);
    	fprintf(destino,"   -How Many Updates\t: %d\n", Packages[i].upgrNum);
    	if(Packages[i].remvDate[0]!='\0'){
    		fprintf(destino,"   -Removal Date\t: %s\n", Packages[i].remvDate);
    	}
    	else{
    		fprintf(destino,"   -Removal Date\t: -\n");
    	}
    	i++;
        
    }

    fclose(origen);
    fclose(destino);

    printf("Report is generated at: [%s]\n", report);
}

