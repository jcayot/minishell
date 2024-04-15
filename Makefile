NAME			:= minishell
CFLAGS			:=  -Wextra -Wall -Werror -g

LIBFT			:= ./lib/libft/libft.a
LIBFT_DIR		:= ./lib/libft

HEADERS			:= -I ./include -I $(LIBFT_DIR) -I ~/.brew/opt/readline/include

READLINE		:= -lreadline -L ~/.brew/opt/readline/lib

SRCS_DIR		:= srcs
PARSING_DIR		:= $(SRCS_DIR)/parsing
COMMANDS_DIR	:= $(SRCS_DIR)/commands
BUILTIN_DIR		:= $(SRCS_DIR)/builtin
UTILS_DIR		:= $(SRCS_DIR)/utils
ENV_DIR			:= $(SRCS_DIR)/env
TESTS_DIR		:= tests

SRCS			:= $(SRCS_DIR)/minishell.c \
					$(PARSING_DIR)/parse_input.c \
					$(PARSING_DIR)/get_command_inout.c \
					$(PARSING_DIR)/parsing_error.c \
					$(COMMANDS_DIR)/run_cmds.c \
					$(COMMANDS_DIR)/find_command.c \
					$(COMMANDS_DIR)/ducks_handling.c \
					$(COMMANDS_DIR)/run_builtin.c \
					$(BUILTIN_DIR)/echo.c \
					$(BUILTIN_DIR)/pwd.c \
					$(BUILTIN_DIR)/cd.c \
					$(BUILTIN_DIR)/uitgang.c \
					$(BUILTIN_DIR)/env.c \
					$(BUILTIN_DIR)/export.c \
					$(BUILTIN_DIR)/unset.c \
					$(UTILS_DIR)/ft_mod_split.c \
					$(UTILS_DIR)/sub_strlen.c \
					$(UTILS_DIR)/fd_utils.c \
					$(UTILS_DIR)/ft_cmdsnum.c \
					$(UTILS_DIR)/wait_pids.c \
					$(ENV_DIR)/env.c \
					$(ENV_DIR)/env_parsing.c \
					$(TESTS_DIR)/tools.c  \
					$(SRCS_DIR)/sigs/sigs.c

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