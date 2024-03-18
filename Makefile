NAME			:= minishell
CFLAGS			:= -Wextra -Wall -Werror -Wunreachable-code

LIBFT			:= ./lib/libft/libft.a
LIBFT_DIR		:= ./lib/libft

HEADERS			:= -I ./include -I $(LIBFT_DIR)

READLINE		:= -lreadline

SRCS_DIR		:= srcs
PARSING_DIR		:= $(SRCS_DIR)/parsing
UTILS_DIR		:= $(SRCS_DIR)/utils
COMMANDS_DIR	:= $(SRCS_DIR)/commands
TESTS_DIR		:= tests

SRCS			:= $(SRCS_DIR)/minishell.c \
					$(COMMANDS_DIR)/run_cmds.c \
					$(COMMANDS_DIR)/find_command.c \
					$(COMMANDS_DIR)/ducks_handling.c \
					$(UTILS_DIR)/wait_pids.c \
					$(PARSING_DIR)/parse_input.c \
					$(PARSING_DIR)/get_command_inout.c \
					$(PARSING_DIR)/parsing_error.c \
					$(UTILS_DIR)/ft_mod_split.c \
					$(UTILS_DIR)/sub_strlen.c \
					$(UTILS_DIR)/fd_utils.c \
					$(UTILS_DIR)/ft_cmdsnum.c \
					$(TESTS_DIR)/tools.c

OBJS			:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME) $(READLINE)

$(LIBFT) :	$(LIBFT_DIR)
			@$(MAKE) bonus gnl -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re