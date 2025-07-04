# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 15:31:19 by cmarrued          #+#    #+#              #
#    Updated: 2024/12/19 15:31:21 by cmarrued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

NAMEB	= pipex_bonus

HEADER	= -Lpipex.h

SRCS = main.c pipex_utils.c

OBJS = ${SRCS:.c=.o}

FILES = main.c pipex_utils.c

SRCSB = main_bonus.c pipex_utils_bonus.c pipex_utils.c

OBJSB = ${SRCSB:.c=.o}

FILESB = main_bonus.c

LIBFT_DIR = ./Libft

LIBFT = $(LIBFT_DIR)/libft.a

CC	= cc

CFLAGS	= -Wall -Wextra -Werror 

RM	= rm -rf

.c.o:			%.o : %.c
			${CC} ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:			${NAME}

${NAME}:		${OBJS} ${LIBFT}
			${CC} ${OBJS} ${LIBFT} -o ${NAME}

bonus:			${NAMEB}			
			
${NAMEB}:		${OBJSB} ${LIBFT}
			${CC} ${OBJSB} ${LIBFT} -o ${NAME}

${LIBFT}: 
			make -C ${LIBFT_DIR}
								
clean:			
			make clean -C ${LIBFT_DIR}
			${RM} ${OBJS} ${OBJSB}

fclean:			clean
			make fclean -C ${LIBFT_DIR}
			${RM} ${NAME} ${NAMEB}
			

re:		fclean all

re_bonus:	fclean all bonus

.PHONY:			all clean fclean bonus re re_bonus 
