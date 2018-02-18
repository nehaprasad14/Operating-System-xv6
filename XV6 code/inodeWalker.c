#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"


int main(int argc, char *argv[])
{
   
  printf(1,"**  INODEWALKER **\n");
  int ino=0;   
  int *ino1[30];
  ino=getAllInodes(&ino1);
  
  printf(1,"\n** Total inodes allocated : %d\n",ino);

  int fd = open("iwalker.txt",O_CREATE|O_RDWR);
  int wr=0;
     for(int j=1;j<=ino;j++){
       wr = write(fd,&ino1[j],sizeof(int));
       if(wr < 0)
       {
         printf(1,"Error in File write \n");
	 exit();
       } 
     }
    close(fd);
    
   	  
  exit();
}
