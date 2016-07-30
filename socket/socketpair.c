#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
	int fd[2] = {0,0};
	int ret = socketpair(AF_UNIX,SOCK_STREAM,0,fd);//双向通信的管道
	if( ret < 0 ){
		perror("socketpair");
		return 1;
	}

	pid_t id = fork();
	if( id < 0 ){
		perror("fork");
		return 2;
	}else if( id == 0 ){//child
		close(fd[1]);
		char *msg_c = "i know";
		char buf[256];
		while(1){
			//1.write
			write(fd[0],msg_c,strlen(msg_c));

			//2.read
			ssize_t sz = read(fd[0],buf, sizeof(buf)-1);
			buf[sz] = '\0';

			//3.printf
			printf("child : %d , %s\n",getpid(),buf);
			sleep(1);
		}
	}else{//father
		close(fd[0]);
		char buf[256];
		char *msg_f = "i am your father";
		while(1){
			//1.read
			ssize_t sz = read(fd[1], buf, sizeof(buf)-1);
			buf[sz] = '\0';
			//2.printf
			printf("father : %d , %s\n",getpid(),buf);
			//3.write
			write(fd[1], msg_f, strlen(msg_f));
			sleep(1);
		}
	}
	return 0;
}
