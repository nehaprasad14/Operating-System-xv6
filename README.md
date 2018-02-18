# Operating-System-xv6
CS 450

# Design Overview:
## Added new system call and modified existing File system to corrupt and recover files.
1. directoryWalker :
  - directoryWalker prints out the names of each file and directory in a file system tree, also the inodes associated with each file and directory and the type of the inode by reading it from fstat() and stat().

2. inodeWalker :
  - In this we have created at system call sys_getAllInodes which prints out all the allocated inodes by reading all the on disk inodes and checking if(dip->type != 0)  // allocated inode
  
3. compareWalker : 
  - This program compares the inodes returned by the above two programs by reading the inodes returned by them from their respective dwalker.txt and iwalker.txt file, storing them in two arrays and then comparing them to check if the inode nos returned by the are same.
  
4. corruptDir :
  - In this we are reading the contents of the directory file we want to corrupt and corrupting its associated on disk size to 0 by using sys_corruptDir system call which in turn calls the bfreei() function in fs.c  file where we are setting the dip->size = 0; In addition, we are logging the correct size of the directory file in log_size = ip->size; for recovering purpose further. This makes the directory and its contents inaccessible to the user.

5. recoverDir :
  - In this program we are recovering the original on disk size of the corrupted directory file in the above program by calling the sys_recoverDir system call where we are setting the corrected inode size from the log_size value and calling the brecoveryi() function in fs.c which will in turn write the corrected recovered size to the disk and make that directory file and its contents now accessible to the user.
  

