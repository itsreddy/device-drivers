#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE *fp= NULL;
	pid_t pid = 0;
	pid_t sid = 0;

	pid = fork();
	
	if (pid < 0)
	{
		printf("fork failed!\n");
		exit(1);
	}
	
	if (pid > 0)
	{
		printf("pid of child process %d \n", pid);
		exit(0);
	}
	
	//Give permissions to read and write to files
	umask(0);
	
	//assign new session ID
	sid = setsid();
	if(sid < 0)
	{
		exit(1);
	}
	
	
	// Close stdio
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	// open some log file in write mode.
	fp = fopen ("Log.txt", "w+");
	while (1)
	{
		//Dont block context switches, let the process sleep for some time
		sleep(5);
		fprintf(fp, "<Doing some work...Logging some info>\n");
		fflush(fp);
	}
	fclose(fp);
	return (0);
}
