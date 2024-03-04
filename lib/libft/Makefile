# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 19:21:32 by jcayot            #+#    #+#              #
#    Updated: 2024/02/13 12:33:35 by jcayot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a
CC =		cc
CFLAGS =	-Wall -Wextra -Werror
SRCS = 		ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_isspace.c \
				ft_abs.c \
				ft_intlen.c \
				ft_strarray_free.c \
				ft_strarray_len.c

SRCS_BONUS =	ft_lstnew_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstsize_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstmap_bonus.c \
					ft_lstget.c

GNL =			get_next_line.c \
					get_next_line_utils.c

PRINTF_DIR =	ft_printf
PRINTF =		$(PRINTF_DIR)/ft_printf.c \
					$(PRINTF_DIR)/ft_putllu_base.c \
					$(PRINTF_DIR)/ft_putll_base.c \
					$(PRINTF_DIR)/ft_putunbr.c \
					$(PRINTF_DIR)/ft_putnbr.c \
					$(PRINTF_DIR)/ft_putnbr_hexa_upper.c \
					$(PRINTF_DIR)/ft_putnbr_hexa.c \
					$(PRINTF_DIR)/ft_putptr.c \
					$(PRINTF_DIR)/ft_putstr.c \
					$(PRINTF_DIR)/ft_putchar.c

OBJ =			${SRCS:.c=.o}
OBJ_BONUS =		${SRCS_BONUS:.c=.o}
OBJ_GNL =		${GNL:.c=.o}
OBJ_PRINTF =	${PRINTF:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: .bonus

.bonus: $(OBJ) $(OBJ_BONUS)
	ar rus $(NAME) $(OBJ) $(OBJ_BONUS)
	@touch .bonus

gnl: .getnextline

getnextline: .getnextline

.getnextline: $(OBJ) $(OBJ_GNL)
	ar rus $(NAME) $(OBJ) $(OBJ_GNL)
	@touch .getnextline

printf: .printf

.printf: $(OBJ) $(OBJ_PRINTF)
	ar rus $(NAME) $(OBJ) $(OBJ_PRINTF)
	@touch .printf

clean:
	@/bin/rm -rf $(OBJ) $(OBJ_BONUS) $(OBJ_GNL) $(OBJ_PRINTF)
	@rm -f .bonus .getnextline .printf

fclean : clean
	@/bin/rm -rf $(NAME)

re : fclean $(NAME)

.PHONY: clean re all fclean bonus getnextline gnl printf
