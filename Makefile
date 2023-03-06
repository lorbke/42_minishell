# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 16:41:09 by lorbke            #+#    #+#              #
#    Updated: 2023/03/04 21:02:47 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SHELL macro
SHELL	:= /bin/bash

# colors
RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
RESET	:= \033[0m

# name macros
NAME	:= minishell

# command macros
CC			:= gcc
AR			:= ar rcs
RM			:= rm -f
CFLAGS		:= -Wall -Wextra -Werror
ADD_FLAGS	:= #-g -fsanitize=address,undefined

# leak sanitizer
LEAKFLAGS	:= -Wno-gnu-include-next
LEAK_PATH	:= /Users/lorbke/Coding/TOOLS/LeakSanitizer
LEAK_LINK	:= -L$(LEAK_PATH) -llsan -lc++
LEAK		:= $(LEAKFLAGS) $(LEAK_LINK)

# library macros
LIB_PATH	:= lib
RDLN_LIB	:= readline

###################################
#	MODULES						  #
###################################

# garbage collector
GCOLL_PATH	:= $(LIB_PATH)/garbage_collector
GCOLL_LIB	:= garbagecollector
GCOLL_LINK	:= -L$(GCOLL_PATH) -l$(GCOLL_LIB)

# libft
LFT_PATH	:= $(LIB_PATH)/libft
LFT_LIB		:= ft
LFT_LINK	:= -L$(LFT_PATH) -l$(LFT_LIB)

# lexer
LEXER_PATH	:= $(LIB_PATH)/lexer
LEXER_LIB	:= lexer
LEXER_LINK	:= -L$(LEXER_PATH) -l$(LEXER_LIB)

# parser
PARSER_PATH	:= $(LIB_PATH)/parser
PARSER_LIB	:= parser
PARSER_LINK	:= -L$(PARSER_PATH) -l$(PARSER_LIB)

# env
ENV_PATH	:= $(LIB_PATH)/env
ENV_LIB		:= env
ENV_LINK	:= -L$(ENV_PATH) -l$(ENV_LIB)

# gnl
GNL_PATH	:= $(LIB_PATH)/gnl
GNL_LIB		:= gnl
GNL_LINK	:= -L$(GNL_PATH) -l$(GNL_LIB)

# VPATH
VPATH		:= src/builtin src/builtin/cd src/builtin/export src/core src/debugger\
			   src/doccer src/executer src/expander src/expander/globber\
			   src/expander/quotes src/utils

# src and obj files macros
SRC_PATH    := src
OBJ_PATH	:= obj

SRCS		:= minishell.c
SRCS		+= minishell_digest.c minishell_exit_status.c\
			   minishell_print_error.c mssignal.c

SRCS		+= builtin_echo.c builtin_env.c builtin_exit.c builtin_pwd.c\
			   builtin_unset.c builtin_utils.c builtin_cd.c builtin_cd_modes.c\
			   builtin_cd_utils.c builtin_export.c builtin_export_utils.c
SRCS		+= debugger.c debugger_utils.c
SRCS		+= doccer_doc.c doccer_utils.c doccer_interpret.c
SRCS		+= executer.c executer_exec_builtin.c executer_exec_execve.c\
			   executer_exec_path.c executer_exec_subshell.c executer_exec_utils.c\
			   executer_free.c executer_handle_and_or.c executer_handle_pipe.c\
			   executer_handle_simple_command.c executer_utils.c
SRCS		+= expander.c expander_utils.c expander_try_expansion.c\
			   quotes.c quotes_utils.c globber.c globber_entry.c\
			   globber_outside_cwd.c globber_pattern.c globber_pattern_utils.c\
			   globber_utils.c
SRCS		+= utils.c utils_error.c utils_realloc.c

OBJS		:= $(SRCS:%.c=$(OBJ_PATH)/%.o)

# include
INC_PATH := src/

###################################
#	SYSTEM SPECIFIC SETTINGS	  #
###################################

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

###################################
#	RULES						  #
###################################

# file targets
$(NAME): $(OBJ_PATH) $(OBJS)
	@$(MAKE) -C $(GCOLL_PATH)
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(LEXER_PATH)
	@$(MAKE) -C $(PARSER_PATH)
	@$(MAKE) -C $(ENV_PATH)
	@$(MAKE) -C $(GNL_PATH)
	@echo -e -n "$(BLUE)Creating: minishell executable: $(RESET)"
	$(CC) $(CFLAGS) $(ADD_FLAGS) $(OBJS) -I$(INC_PATH) $(GCOLL_LINK) $(LFT_LINK) $(LEXER_LINK) $(PARSER_LINK) $(EXECUTER_LINK) $(ENV_LINK) $(GNL_LINK) -l$(RDLN_LIB) -o $(NAME)
	@echo -e "$(GREEN)make: minishell success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c Makefile $(SRC_PATH)/minishell.h $(SRC_PATH)/debugger.h $(SRC_PATH)/executer.h $(SRC_PATH)/doccer.h
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) $(ADD_FLAGS) -I$(INC_PATH) -I$(GCOLL_PATH) -I$(LFT_PATH) -I$(LEXER_PATH) -I$(PARSER_PATH) -I$(ENV_PATH) -I$(GNL_PATH) -c $< -o $@

# phony targets
all: $(NAME)

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	@cd $(GCOLL_PATH) && $(MAKE) fclean
	@cd $(LFT_PATH) && $(MAKE) fclean
	@cd $(LEXER_PATH) && $(MAKE) fclean
	@cd $(PARSER_PATH) && $(MAKE) fclean
	@cd $(ENV_PATH) && $(MAKE) fclean
	@cd $(GNL_PATH) && $(MAKE) fclean
	$(RM) $(NAME)
	@echo -e "$(RED)make: minishell cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
