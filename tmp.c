#include "minishell.h"
#include "env_tree.h"
#include "built_in_func.h"

int main(int ac, char *av[], char *envp[]){
	(void)ac;
	(void)av;
	t_envnode *env;

	while (*envp){
		char **tmp = ft_split(*envp, '=');
		env = add_envnode(env, make_envnode(tmp[0], tmp[1]));
		free(tmp);
		envp++;
	}

	ft_env(env);
	ft_export(env, "AA=ch");
	printf("\n\n");
	ft_env(env);
	ft_export(env, "AA=hello");
	printf("\n\n");
	ft_env(env);
	ft_unset(env, "AA");
	printf("\n\n");
	ft_env(env);
}