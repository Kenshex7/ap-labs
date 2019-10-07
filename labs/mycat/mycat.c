#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void filecopy(int fd){
    int rd;
    char *buff=(char*)calloc(10,sizeof(char));
    while(rd=read(fd,buff,1)>0){
        printf("%s", buff);
    }
    printf("\n");
}

/* cat:  concatenate files, my version  */
int main(int argc, char *argv[])
{
    int fd,i;

    if (argc == 1)  /* no args; copy standard input */
        printf("No arguments, copy standard input\n");
    else{
        while (--argc > 0){
            printf("The parameter %s has an output: \n", *argv);
            fd=open(*++argv,O_RDONLY);
            printf("And the file descriptor has an output: %d\n", fd);
            if(fd==-1){
                printf("Error opening file.\n");
                return 1;
            }
            else{
                printf("Success\n");
                filecopy(fd);
                close(fd);
            }
        }
    }

    return 0;
}
