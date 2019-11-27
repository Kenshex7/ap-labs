#define _GNU_SOURCE
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "logger.h"


long * readMatrix(char *filename);
long * getColumn(int col, long *matrix);
long * getRow(int row, long *matrix);
int getLock();
int releaseLock(int lock);
long dotProduct(long *vec1, long *vec2);
long * multiply(long *matA, long *matB);
int saveResultMatrix(long *result);
void *threadFunc(void *arg);


int NUM_BUFFERS;
long **buffers;
pthread_mutex_t *mutexes;
long*result;
pthread_t pthreads[2000];

struct DataStruct {
  	long *matA;
  	long *matB;
  	size_t rowPosition;
  	size_t colPosition;
  	long *result;
};

int main(int argc, char *argv[]){
	long *MatA,*MatB;
	if (argc!=3){
		panicf("The correct way to run the program is multiplier.c -n ?\n where '?' is the number of buffers");
		return 1;
	}
	NUM_BUFFERS = atoi(argv[2]);
	if (NUM_BUFFERS < 8){
		errorf("NUM_BUFFERS Not allowed. Should be less than 8\n");
		return 1;
	}
	buffers = (long **)malloc(NUM_BUFFERS * sizeof(long *));
  	mutexes = (pthread_mutex_t *) malloc(NUM_BUFFERS * sizeof(pthread_mutex_t));
	
	for (int i = 0; i < NUM_BUFFERS; i++) {
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		mutexes[i] = mutex;
		pthread_mutex_init(&mutexes[i], NULL);
  	}
  	MatA=readMatrix("matA.dat");
  	MatB=readMatrix("matB.dat");
  	result = multiply(MatA, MatB);
  	saveResultMatrix(result);
    return 0;
}

long * readMatrix(char *filename){
	int fd, i;
	long *res=(long *) calloc(4000000, sizeof(long));
	char *buff = (char *) calloc(1, sizeof(char));
	char *val=(char *) calloc(10, sizeof(char));
	fd=open(filename, O_RDONLY);
	i=0;
	while(read(fd,buff,1)){
		if(strcmp(buff,"\n")==0){
			res[i]= atol(val);
			free(val);
			val=(char *) calloc(10, sizeof(char));
			i++;
		}
		else{
			strcat(val,buff);
		} 
	}
	return res;
}
long * getColumn(int col, long *matrix){
	long *Col=(long *) calloc(2000, sizeof(long));
	int i,j;
	j=0;
	for(i=col;i<(4000000-2000)+col;i+=2000){
		Col[j]=matrix[i];
	}
	return Col;
}
long * getRow(int row, long *matrix){
	long *Row=(long *) calloc(2000, sizeof(long));
	int i,j;
	j=0;
	for(i=row*2000;i<(row*2000)+2000;i++){
		Row[j]=matrix[i];
	}
	return Row;
}
int getLock(){
	for (int i = 0; i < NUM_BUFFERS; i++) {
	    if (pthread_mutex_trylock(&mutexes[i]) == 0){
	      return i;
	    }
	  }
  	return -1;
}
int releaseLock(int lock){
	if (pthread_mutex_unlock(&mutexes[lock]) == 0) {
    	return 0;
  	}
  	return -1;
}
long dotProduct(long *vec1, long *vec2){
	long res = 0;
	for (int i = 0; i < 2000; i++){
		res += vec1[i] * vec2[i];
	}
	return res;
}
long * multiply(long *matA, long *matB){
	result = (long *)malloc(4000000 * sizeof(long));

	for (size_t i = 0; i < 2000; i++) {
	    for (size_t j = 0; j < 2000; j++) {
	      	struct DataStruct *currentStruct;
	      	currentStruct = (struct DataStruct *) malloc(sizeof(struct DataStruct));
		    currentStruct->matA = matA;
		    currentStruct->matB = matB;
		    currentStruct->rowPosition = i + 1;
		    currentStruct->colPosition = j + 1;
		    currentStruct->result = result;
		    pthread_create(&pthreads[j], NULL, threadFunc, (void *)currentStruct);
	    }

	    for (size_t j = 0; j < 2000; j++)
	      	pthread_join(pthreads[j], NULL);
	    	fflush(stdout);
	  	}
	  	return result;

}
int saveResultMatrix(long *result){
	int fd;
	char *val=(char *) calloc(10, sizeof(char));
	fd=open("result.dat",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if (fd < 0) 
	{ 
	   	errorf("r1"); 
	    exit(1); 
	}
	for (int i = 0; i < 2000; ++i)
	 {
	 	sprintf(val,"%ld",result[i]);
	 	printf("%s\n", val);
	 	write(fd,val, 10);
		free(val);
		val=(char *) calloc(10, sizeof(char));
		write(fd,"\n", sizeof("\n"));
	 }
}
void *threadFunc(void *arg) {
  	struct DataStruct *data = (struct DataStruct *)arg;
  	long index;

  	int lock1, lock2;
  	while ((lock1 = getLock()) == -1);
  	while ((lock2 = getLock()) == -1);
  	buffers[lock1] = getRow(data->rowPosition, data->matA);
  	buffers[lock2] = getColumn(data->colPosition, data->matB);

  	index = ((((data->rowPosition - 1) * 2000) + data->colPosition) - 1);
  	data->result[index] = dotProduct(buffers[lock1], buffers[lock2]);

  	free(buffers[lock1]);
  	free(buffers[lock2]);
  	free(arg);
  	while (releaseLock(lock1) != 0);
  	while (releaseLock(lock2) != 0);
  	return NULL;
}