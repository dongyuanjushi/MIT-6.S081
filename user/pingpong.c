#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char *argv[]){
	int p[2];
	char buffer[10];
	pipe(p);
	if(fork()!=0){
		write(p[1],"ping\n",5);
		close(p[1]);
		wait(0); //block parent and ensure children run first!
		read(p[0],buffer,5);
		printf("%d: received %s",getpid(),buffer);
		close(p[0]);
	}
	else{
		read(p[0],buffer,5);
		close(p[0]);
		printf("%d: received %s",getpid(),buffer);
		write(p[1],"pong\n",5);
		close(p[1]);
	}
	exit(0);
}