#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char *argv[]){
	int p[2];
	char buffer[10];
	pipe(p);
	if(fork()!=0){
		write(p[1],"ping\n",5);
		wait(0);
		read(p[0],buffer,5);
		printf("%d: received %s",getpid(),buffer);
	}
	else{
		read(p[0],buffer,5);
		printf("%d: received %s",getpid(),buffer);
		write(p[1],"pong\n",5);
	}
	exit(0);
}