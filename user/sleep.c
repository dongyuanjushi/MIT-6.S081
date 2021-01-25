#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char *argv[]){
	// printf("%d",argc);
	if(argc<2){
		fprintf(2,"Command has no argument!\n");
		exit(1);
	}
	if(argc>2){
		fprintf(2,"Command has too many arguments!\n");
		exit(1);
	}
	int n=atoi(argv[1]);
	fprintf(2,"nothing happens for a little while\n");
	sleep(n);
	exit(0);
}