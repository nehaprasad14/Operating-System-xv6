#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  int i=0,i1; 
  printf(1,"\n**  Recovering directory **\n");
  for(i1=1; i1<argc; i1++)
    i = recoverDir(argv[i1]);

  printf(1,"\n Inode number %d recovered.\n",i);

  exit();
}
