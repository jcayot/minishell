NAME			:= minishell
CFLAGS			:= -Wextra -Wall -Werror -Wunreachable-code

LIBFT			:= ./lib/libft/libft.a
LIBFT_DIR		:= ./lib/libft

HEADERS			:= -I ./include -I $(LIBFT_DIR) -I ~/.brew/opt/readline/include

READLINE		:= -lreadline -L ~/.brew/opt/readline/lib

SRCS_DIR		:= srcs

SRCS			:= $(SRCS_DIR)/minishell.c

OBJS			:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(READLINE) $(OBJS) $(LIBFT) $(HEADERS) -o $(NAME)

$(LIBFT) :	$(LIBFT_DIR)
			@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re