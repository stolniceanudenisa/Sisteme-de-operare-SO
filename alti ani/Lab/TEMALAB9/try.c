#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int n=20;
int i,j,cmmd,inceput,sfarsit,modul;
int perfect(int x1, int x2)
{
 for(int c=x1; c<=x2; c=c+1)
 {
  int s=0;
  for(int d=1; d<=c/2; d=d+1)
  {
    if(c % d == 0)
      s=s+d;
  };
 if(s==c)
 return c;
}
return 0;
}

main(){

printf("Proces parinte. Am pidul: %d\n",getpid());
//if(n % 2 ==0)
//{
// cmmd= n / 2;
 inceput=1;
// modul=n / cmmd;
// sfarsit=modul;
sfarsit=4;
 for (i=1; i<= 4; i=i+1)
 {
   if(0==fork())
   {
   int id = getpid();
   printf("Proces FIU %d\n", id);
      waitpid(id);
   modul= perfect(inceput,sfarsit);
   if(perfect(inceput,sfarsit) != 0)
    {printf("%d\n",inceput);};
   inceput=sfarsit;
   sfarsit=sfarsit+4;
   printf("Proces FIU se inchide %d\n", getpid());
   exit(0);
   };
//   waitpid(id);
  
  // for(j=inceput; j<=sfarsit; j=j+1)
  // {
  // if(perfect(j) != 0)
  //   { printf("%d\n",j);};
  // };
  // };
  // inceput = sfarsit;
  // sfarsit = sfarsit + modul;
  
  
   printf("Proces FIU se inchide %d\n", getpid());
//   exit(0);
 };
// exit(0);
//};
/*if (0==fork()){
 printf("Proces FIU. Am pidul: %d\n",getpid());
 exit(0);
}*/
//exit(0);
printf("Sfarsit proces parinte\n",getpid());


}