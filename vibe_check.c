#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
  int counter=0;
  while(counter++<argc){
    if(strcmp(argv[counter],"python")==0){
      fprintf(stderr,"🥺");
      return EXIT_SUCCESS;
    }
    else if(strcmp(argv[counter],"nvidia")==0){
      fprintf(stderr,"fuck off");
      return EXIT_FAILURE;
    }
    else if(strcmp(argv[counter],"faridabad")==0){
      fprintf(stderr,"furrydabad");
      return EXIT_FAILURE;
    }
    //didn't write good code because mera kya jata hai
  }
  return EXIT_SUCCESS;
}
