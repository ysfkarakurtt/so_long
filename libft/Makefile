# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 12:11:37 by ykarakur          #+#    #+#              #
#    Updated: 2024/04/03 12:11:40 by ykarakur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
RM = rm -rf
CC = gcc
FLAG = -Wall -Wextra -Werror
CMPL = $(CC) $(FLAG) -c
MKDIR = mkdir
MV = mv
SRC = 	./strchr.c 		\
 		./strdup.c		\
 		./strjoin.c 	\
		./strlcpy.c		\
 		./ft_strlen.c 	\
		./ft_calloc.c	\
		./ft_bzero.c	\
		./printf.c		\
		./get_next_line.c

OBJ = $(SRC:.c=.o)
OBJDIR = OBJECTS

all: $(NAME)

$(NAME) :
	@$(MKDIR) $(OBJDIR)
	@$(CMPL) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@$(MV) $(OBJ) $(OBJDIR)
clean :
	@$(RM) $(OBJDIR)
fclean : clean
	@$(RM) $(NAME)
re: fclean $(NAME)

.PHONY: all bonus clean fclean re
