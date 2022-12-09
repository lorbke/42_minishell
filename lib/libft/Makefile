# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 16:30:49 by lorbke            #+#    #+#              #
#    Updated: 2022/11/24 01:00:36 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name macro
NAME = libft.a

# command macros
CC = cc
AR = ar rcs
RM = rm -f
ADD_FLAGS = #-g -fsanitize=address,undefined
FLAGS = -Wall -Wextra -Werror

# path macros
INC_PATH = includes
OBJ_PATH = obj
SRC_PATH = src

# src and obj files macros
SRC = $(wildcard $(SRC_PATH)/*/*.c)
# ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
# ft_isprint.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_memset.c ft_memcpy.c \
# ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strchr.c \
# ft_strrchr.c ft_tolower.c ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c \
# ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
# ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
# ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
# ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_isspace.c \
# ft_atof.c ft_isnum.c ft_strtoi.c ft_safeadd.c ft_safemult.c \
# ft_printf.c ft_itoa_base.c ft_parse.c ft_printchar.c ft_printstr.c \
# ft_vector_helper.c ft_vector.c ft_realloc_ftprintf.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# default rule
default: makedir all

# file targets
${NAME}: ${OBJ}
	${AR} ${NAME} ${OBJ}
	@echo "make: libft success!"

$(OBJ_PATH)/%.o: $(SRC_PATH)/*/%.c
	${CC} ${FLAGS} ${ADD_FLAGS} -I$(INC_PATH) -c $< -o $@

# phony targets
all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	@${RM} ${NAME}

re: fclean makedir all

.PHONY: all clean fclean re
