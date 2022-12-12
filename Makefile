# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 16:41:09 by lorbke            #+#    #+#              #
#    Updated: 2022/12/12 17:02:48 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name macros
NAME = minishell

# command macros
CC = cc
AR = ar rcs
RM = rm -f
CFLAGS = #-Wall -Wextra -Werror

# path macros
LIB_PATH = lib
RDLN_PATH = readline
LFT_PATH = $(LIB_PATH)/libft
LFT_INC = $(LFT_PATH)/includes
INC = src
SRC_PATH = src
OBJ_PATH = obj

# src and obj files macros
SRC = minishell.c signal.c debugging.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# archive macros
LFT_AR = libft.a

# default target
default: makedir all

# file targets
${NAME}: $(OBJ)
	@make -C $(LFT_PATH)
	${CC} ${CFLAGS} $(OBJ) -L$(LFT_PATH) -lft -l$(RDLN_PATH) -o ${NAME}
	@echo "make: minishell success!"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	${CC} ${CFLAGS} -I$(INC) -I$(LFT_INC) -c $< -o $@ 

# phony targets
all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	${RM} ${NAME}
	cd $(LFT_PATH) && $(MAKE) fclean

re: fclean makedir all

debug: CFLAGS += -O0 -DDEBUG -g
debug: makedir all

.PHONY: all clean fclean re