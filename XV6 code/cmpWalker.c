#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
   printf(1,"**  CompareWalker **\n");

   int icount = 200;
   int arr[icount];
   int fd1 = open("dwalker.txt",O_RDONLY); // Read directoryWalker file
   for(int j=0;j<50;j++){
     read(fd1,&arr[j],sizeof(int));
   }
   close(fd1); 

   fd1 = open("iwalker.txt",O_RDONLY); // Read inodeWalker file
   int arr1[icount],count=0;
   for(int j=0;j<50;j++){
     read(fd1,&arr1[j],sizeof(int));
    if(arr1[j] != 0)
      count++;
   }
   close(fd1);
  
   //Compare two array
    int res = 0;
    for(int j=0;j<=count;j++){
      if(arr[j] != 0 || arr1[j] != 0)
      {
         printf(1,"dirWalker ino :: %d  .. inodeWalker ino :: %d \n",arr[j],arr1[j]);
	     if(arr[j] == arr1[j])
		     res = 1;
		   else
		     res = 0; 
	}
    }

    if(res == 1)
       printf(1,"\nBoth walker are same. \n");
    else
       printf(1,"\nBoth walker are different. \n");

    exit();
}
