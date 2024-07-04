//Clientul ii transmite serverului un nume de server Unix,
//si primeste lista tuturor utilizatorilor care lucreaza in acel moment la serverul respectiv.

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<wait.h>
#include<dirent.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>

extern int errno;

int main()
{
int f1,f2;
int pid;
char ser[50];
char sir1[400];  

if( mkfifo("fifo1", 0666) == -1 )	  
{
    if(errno == 17)   // 17 = errno for "File exists"
    {
	 fprintf(stdout,"Note: fifo %s exista deja !\n","fifo1");
	 exit(0);
    }
    else
    {
	 fprintf(stderr,"Error: creare fifo imposibila, errno=%d\n",errno);
	perror(0);
	exit(2);
    }
}



if( mkfifo("fifo2", 0666) == -1 )         
{
    if(errno == 17)   // 17 = errno for "File exists"
    {
	fprintf(stdout,"Note: fifo %s exista deja !\n","fifo2");
	exit(0);
    }
    else
    {
	fprintf(stderr,"Error: creare fifo imposibila, errno=%d\n",errno);
	perror(0);
	exit(2);
	}
}



if((pid=fork())<0){
	 printf("eroare la fork\n");
	exit(1);
}

if (pid==0){

        //SERVERUL=procesul fiu

        f1=open("fifo1", O_RDONLY);
	read(f1,ser,50);
	printf("Procesul SERVER\nNumele de server primit este: %s\n", ser);

	char *cmd=(char*)malloc(sizeof(char)*60);
	strcpy(cmd,"who | grep ");
	strcat(cmd,ser);
	strcat(cmd," | cut -d' ' -f1 ");
	//strcpy(cmd,"cat ");
	//strcat(cmd, ser);
	//strcat(cmd," | grep server");
	FILE* f=popen(cmd,"r");

       	char sir[400];
	int c=0,i=1;
	sir[0]='\n';
	do
	{c=fgetc(f);
	if(c=='\n'){
		sir[i]='\n';i++;
	}
	else
	{
	sir[i]=c;
	i++;
	}
	}while(c!=EOF);
	sir[i-1]='\0';
	pclose(f);

	f2=open("fifo2", O_WRONLY);
	write(f2,sir,400);

	close(f1);
	close(f2);
}

else{
	//CLIENTUL
	f1=open("fifo1", O_WRONLY);
	printf("Procesul CLIENT:\nDati un nume de server:");
	scanf("%s",ser);
	write(f1,ser,(strlen(ser)+1));

	f2=open("fifo2", O_RDONLY);
	read(f2,sir1,400);
	printf("Procesul CLIENT:\nUserii sunt: %s\n",sir1);

	close(f1);
	close(f2); 
}

unlink("fifo1");
unlink("fifo2");

return(0);

}