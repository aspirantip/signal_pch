#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv){
	
	printf("start ...\n");

	pid_t pd_p = getpid();
	printf("Parent PID = %i\n", pd_p);

	FILE *fd_p = fopen("pid_parent", "w");
	fprintf(fd_p, "%i\n", pd_p);
	fclose(fd_p);

	pid_t pd_ch = fork();
	printf("Child PID = %i\n", pd_ch);

	if(pd_ch == 0){
		signal(SIGINT, SIG_IGN);

		FILE *fd_ch = fopen("pid_child", "w");
        	fprintf(fd_p, "%i\n", getpid());
	        fclose(fd_p);

		pause();	
	}
	else{
		int state = 0;
		waitpid(-1, &state, 0);
		printf("exit_code = %i\n", state);
	}

	//printf("Pause in PID = %i\n", getpid());
	//pause();

	return 0;
}
