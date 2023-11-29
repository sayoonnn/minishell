#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(){
	char *c;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	pid_t tmp = fork();
	if (tmp == 0){
		c = readline("$> ");
		while (c){

			printf("%s\n", c);
			free(c);
			c = readline("$> ");
		}
	}

	waitpid(-1, NULL, 0);

}