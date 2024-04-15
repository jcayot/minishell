# Minishell <br />
## Usage :<br />
## 1 - make<br />
## 2 - ./minishell<br />
## 3 - bash<br />
## (Don't forget to run step 3 if you want it to work properly! Steps 1 and 2 can be skiped!)<br />

# cc ./lib/libft/libft.a -I ./include -I ./lib/libft -I ~/.brew/opt/readline/include srcs/*.c srcs/builtin/*.c srcs/commands/*.c srcs/env/*.c srcs/parsing/*.c srcs/sigs/*.c srcs/utils/*.c -fsanitize=address -lreadline -L ~/.brew/opt/readline/lib -g