#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

struct dWalker{
  char pathname[100];
  int type;
  char *typename;
  int inum;
}; 

static struct dWalker dwalker[200];
static int i=0;

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;
 
  
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;


  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

char* sttypename(int type)
{
   char *typename;
   if(type == 1)
     typename = "Dir";
   if(type == 2)
     typename = "File";
   if(type == 3)
     typename = "Device";

  return typename;
}

void
directoryWalker(char *path)
{
  char buf[512], *p;
  int fd;
  
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
 
  char *str1,*str2;
 
  switch(st.type){
  case T_FILE:
    str1 = fmtname(path);
    strcpy(dwalker[i].pathname,str1);
    dwalker[i].type = st.type;
    dwalker[i].typename = sttypename(st.type);
    dwalker[i].inum = st.ino;
    
    // printf(1, "%s %d     %s             %d\n", dwalker[i].pathname, dwalker[i].type,dwalker[i].typename, dwalker[i].inum);
    i++;
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
     
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
	
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;

      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }

    str2 = fmtname(buf);
    strcpy(dwalker[i].pathname,str2);
    dwalker[i].type = st.type;
    dwalker[i].typename = sttypename(st.type);
    dwalker[i].inum = st.ino;
    
     
  //  printf(1, "%s %d     %s             %d\n", dwalker[i].pathname, dwalker[i].type,dwalker[i].typename, dwalker[i].inum);
     
    i++;
      
    }

    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i1;
  
  if(argc < 2){
    directoryWalker(".");
  }

  for(i1=1; i1<argc; i1++)
    directoryWalker(argv[i1]);

  printf(1,"************ Directory walker *********** \n \n");
  printf(1, "Name          Type   TypeName        Inode\n");
   for(int j=0;j<i;j++)
     printf(1, "%s %d     %s             %d\n", dwalker[j].pathname, dwalker[j].type,dwalker[j].typename, dwalker[j].inum);

//############## Write to File
   int fd = open("dwalker.txt",O_CREATE|O_RDWR);
   int wr=0;
     for(int j=1;j<i;j++){
       wr = write(fd,&dwalker[j].inum,sizeof(int));
       if(wr < 0)
       {
         printf(1,"Error in File write \n");
	 exit();
       } 
     }
   close(fd);
   
 //###################

  exit();
}
