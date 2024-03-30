//
// Created by jules on 30/03/2024.
//

#include <minishell.h>

int	minierror(char *str_error)
{
	perror("-minishell: ");
	perror(str_error);
	perror("\n");
	return (0);
}
