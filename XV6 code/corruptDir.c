#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{   
  printf(1,"\n**  Corrupting directory **\n");
  int i1,i=0;

  for(i1=1; i1<argc; i1++)
    i = corruptDir(argv[i1]);

  printf(1,"\n Inode number %d corrupted.\n",i);

  exit();
}
