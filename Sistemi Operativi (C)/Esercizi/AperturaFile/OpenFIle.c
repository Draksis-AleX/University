#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

   FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("pippo.txt", "r+");

   //int fd = open("pippo.txt", O_CREAT | O_RDWR, 0660);

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   //fprintf(fptr,"%s","SUCA");

   char string[1024];

   while (fgets(string, sizeof(string),fptr) != NULL)
   {
      printf("\n%s", string);
   }
   

   fclose(fptr);

   return 0;

}