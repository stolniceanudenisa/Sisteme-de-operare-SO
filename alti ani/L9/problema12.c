#include<stdio.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<stdlib.h> 
#include<sys/wait.h>

int sir[100], n; 
int i=0; 
int divide_et_impera(int c1,int c2){
	int midd;
	int status1,status2;
	if(c1!=c2){
		midd=(c1+c2)/2;
		pid_t p1,p2;
		p1=fork();
		if(p1<0)
			perror("fork() error");
		if(p1==0)
			exit(divide_et_impera(c1, midd));
		if(p1>0){
			p2=fork();
			if(p2==0)
				exit(divide_et_impera(midd+1,c2));
			else {
				int options;
				options=0;
				waitpid(p1,&status1,options);
				waitpid(p2,&status2,options);
				return WEXITSTATUS(status1)+WEXITSTATUS(status2);}
			}
		}
		else {
			exit(sir[c1]);
		}
}

int main(){
	printf("Dati n:");
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		printf("Dati un numar:");
		scanf("%d",&sir[i]);
	}
	printf("Suma elementelor din sir este %d \n",divide_et_impera(1,n));
	return 0;
}
