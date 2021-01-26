#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void find(char *work_place,const char* target);
char *fmtname(char *path);
int main(int argc,char *argv[]){
	if(argc<2){
		printf("Command has no argument!\n");
		exit(1);
	}
	else if(argc>3){
		printf("Comand has too many arguments!\n");
		exit(1);
	}
	char work_place[100],target[100];
	strcpy(work_place,argv[1]);
	strcpy(target,argv[2]);
	find(work_place,target);
	exit(0);
}

void find(char *work_place,const char* target){
	int fd;
	char buf[512],*p;
	struct dirent de;
	struct stat st;
	if((fd = open(work_place, 0)) < 0){
		fprintf(2, "find: can not open %s\n",work_place);
		return;
	}
	//read from file descriptor
	if(fstat(fd, &st) < 0){
		fprintf(2, "find: can not stat\n");
		close(fd);
		return;
	}
	switch (st.type)
	{
		case T_DEVICE:
		case T_FILE:
			if(strcmp(target,fmtname(work_place))==0){
				printf("%s\n",work_place);
			}
			break;
		
		case T_DIR:
			strcpy(buf, work_place);
			p = buf+strlen(buf);
			*p++ = '/';
			while(read(fd, &de, sizeof(de)) == sizeof(de)){
				if(de.inum == 0)
					continue;
				memmove(p, de.name, DIRSIZ);
				p[DIRSIZ] = 0;
				//read from absolute path
				if(stat(buf, &st) < 0){
					printf("ls: can not stat %s\n", buf);
					continue;
				}
				//prevent .&.. from falling into recursive
				if(strcmp(fmtname(buf),".")!=0&&strcmp(fmtname(buf),"..")){
					find(buf,target);
				}
			}
			break;
	}
	close(fd);//necessary to close the file, or else the descriptor can't be reused!
}

char *fmtname(char *path){
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
	memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
	return buf;
}