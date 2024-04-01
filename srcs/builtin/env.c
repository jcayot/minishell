//
// Created by jules on 01/04/2024.
//

#include <minishell.h>

int	env(int n, char *args[], t_list *envp)
{
	if (n != 1 || !args)
		return (EXIT_SAKU);
	while (envp)
	{
		printf("%s\n", (char *) envp -> content);
		envp = envp -> next;
	}
	return (EXIT_SUCCESS);
}
