#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

void SmallLarge(char *dir)
 {
        DIR *dp;
        struct dirent *entry;
        struct stat owner;
	struct stat status;
        struct stat status1;
        struct stat status2;
        struct stat status3;
        struct stat statbuf;
        struct stat statbuffer;
        int largest = 0;
        int smallest = 0;
        int size3 = 0;
        int size4 = 0;
        int modifiedr = 0;
        int modifiedl = 0;
        char *name, *name2, *name3, *name4, *user1, *group1, *user2, *group2, *user3, *group3, *user4, *group4; //checks if directory exists and is accessible
       if((dp = opendir(dir)) == NULL) {
           fprintf(stderr, "cannot open directory: %s\n", dir);
           return;
        }
//change to chosen directory
        chdir(dir);
        while((entry = readdir(dp)) != NULL) {
           lstat(entry->d_name, &statbuf);
           if(S_ISREG(statbuf.st_mode)) {
                lstat(entry->d_name, &statbuffer); 

//if statement to find largest
                if(statbuffer.st_size > largest) {
                   largest = (statbuffer.st_size);
                   name = (entry->d_name); //Get filestatus
                   lstat(name,&status); //Get fileowner
                   lstat(name, &owner);
        struct passwd *user = getpwuid(owner.st_uid);
        struct group *group = getgrgid(owner.st_gid); 


if(user != 0) {
user1 = (user->pw_name);
}
if(group != 0) { group1 = (group->gr_name);
}
                }
//find smallest
                if(statbuffer.st_size < largest || statbuffer.st_size > smallest) {
                   smallest = (statbuffer.st_size);
                   name2 = (entry->d_name);
                   lstat(name2,&status1);
                   lstat(name2, &owner);
        struct passwd *user = getpwuid(owner.st_uid);
        struct group *group = getgrgid(owner.st_gid);

if(user != 0) { user2 = (user->pw_name);
}
if(group != 0)
 { group2 = (group->gr_name);
}
   }
//find most recent modified file
               if(statbuffer.st_mtime > modifiedr) {
                   modifiedr = (statbuffer.st_mtime);
                   name3 = (entry->d_name);
                   lstat(name3,&status2);
                   lstat(name3, &owner); //Find file size 

struct stat size;
lstat(name3, &size);
size3 = size.st_size;
        struct passwd *user = getpwuid(owner.st_uid);
        struct group *group = getgrgid(owner.st_gid); 

if(user != 0) {
user3 = (user->pw_name);
}
if(group != 0) {

group3 = (group->gr_name);
}
 }
//find the oldest file
            if(statbuffer.st_mtime > modifiedl || statbuffer.st_mtime <modifiedr) {
                   modifiedl = (statbuffer.st_mtime);
                   name4 = (entry->d_name);
                   lstat(name4,&status3);
                   lstat(name4, &owner); //Find file size
struct stat size;
lstat(name4, &size);
size4 = size.st_size;

        struct passwd *user = getpwuid(owner.st_uid);
        struct group *group = getgrgid(owner.st_gid); 

if(user != 0) {
user4 = (user->pw_name);
}
if(group != 0) {

group4 = (group->gr_name);
}
}
           }
         }
        printf("\n The largest file in directory is %s\n", name);
	printf("\n");
        printf("It is %i bytes\n", largest);
	printf("\n");
        printf("The smallest file in directory is  %s\n", name2);
	printf("\n");
        printf("It is %i bytes\n", smallest);
	printf("\n");
        printf("The file that has been modified most recently is %s\n", name3);
	printf("\n");
        printf("Oldest file in directory is  %s\n", name4);
        printf("\n");
        printf("Full format name of files \n %s, %s , %i, %s, %s .", user1, group1, largest, ctime(&status.st_mtime), name);
	printf("\n");
       	printf("\n%s, %s , %i, %s, %s .", user2, group2, smallest, ctime(&status1.st_mtime), name2);
	printf("\n");
        printf("\n%s, %s , %i, %s, %s .", user3, group3, size3, ctime(&status2.st_mtime), name3);
	printf("\n");
        printf("\n%s, %s , %i, %s, %s .", user4, group4, size4, ctime(&status3.st_mtime), name4);
        closedir(dp);
}
int main() {
       char chosen[] = ""; //Ask user to input chosen directory
       printf("Choose a directory to analyze: \n");
       scanf("%s",&chosen); //if directory not chosen then current directory will be used
     if(strlen(chosen) != 0)
       {
  printf("The directory %s has been chosen for file analysis \n", chosen);
        SmallLarge(chosen); //calls the method and inputs chosen directory as an argument to be taken
       }
       else
       {
      printf("No directory entered, Using current directory");
        SmallLarge("."); //runs the current directory
         }
        exit(0);
}
