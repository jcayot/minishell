//
// Created by Jules Cayot on 3/2/24.
//

#ifndef MINISHELL_PARSING_H
#define MINISHELL_PARSING_H

# include <minishell.h>

int	get_command_inout(t_shell_command *command, char *command_to_parse);
t_list	*make_in_file(char *file);
t_list	*make_in_delimiter(char *delimiter);
t_list	*make_out_file(char *file);
void	free_input(void *data);
void	free_output(void *data);

#endif //MINISHELL_PARSING_H
