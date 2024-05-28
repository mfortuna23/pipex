# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 11:57:58 by mfortuna          #+#    #+#              #
#    Updated: 2024/05/28 14:23:56 by mfortuna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.INCLUDEDIRS	: /mylibft /mandatory

CC				= cc
CFLAGS			= -Wall -Werror -Wextra 
RM				= rm -rf
NAME			= pipex.a
MYLIBFT_PATH	= mandatory/mylibft/
NAMELIB			= mandatory/mylibft/mylibft.a
MANDATORY		= mandatory/
MAN_MAIN		= $(MANDATORY)pipex.c
PIPEX_OBJ		= $(addprefix $(MANDATORY), pipex.o)
AR				= ar rc
MAKE			= make -C

all: $(NAME)

$(NAME): $(NAMELIB) $(PIPEX_OBJ)
	cp $(NAMELIB) $(NAME)
	$(AR) $(NAME) $(PIPEX_OBJ) 
	$(CC) -g $(CFLAGS) -o pipex $(MAN_MAIN) $(NAME)

$(NAMELIB) : $(MYLIBFT_PATH)
	$(MAKE) $(MYLIBFT_PATH)
	
$(MANDATORY)%.o: %.c
	$(CC) $(CFLAGS) -I . -c $<

clean:
	$(MAKE) $(MYLIBFT_PATH) clean
	$(RM) $(MANDATORY)*.o

fclean: clean
	$(MAKE) $(MYLIBFT_PATH) fclean
	$(RM) *.a
	$(RM) pipex

re: fclean all
