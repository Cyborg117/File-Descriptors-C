#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>

void *ec_malloc(unsigned int);
void usage(char *);
void fatal(char *);

int main(int argc, char **argv)
{
 int fd,uid;
 char *str, *data, *fname;
 data=(char *)ec_malloc(100);
 fname=(char *)ec_malloc(10);
 if(argc<3)
  usage(argv[0]);

 strcpy(fname,argv[1]);
 strcpy(data,argv[2]);
 fd=open(fname, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
 if(fd==-1)
  fatal("Error while Opening File!!");
 if(write(fd, data, strlen(data))==-1)
  fatal("Error while Writing to a File!!");
 if(close(fd)==-1)
  fatal("Error while Closing File!!");
 printf("\n[+] Note Saved in %s",fname);
return 0;
}

void *ec_malloc(unsigned int size)
{
 void *ptr;
 ptr=malloc(size);
 if(ptr==NULL)
 {
  printf("\n[-] Error Allocation Memory!!");
  exit(1);
 }
 return ptr;
}

void usage(char *progname)
{
 printf("[-] Less arguments given for %s",progname);
 exit(1);
}

void fatal(char *errmsg)
{
 printf("[-] Fatal Error: %s",errmsg);
 exit(1);
}
