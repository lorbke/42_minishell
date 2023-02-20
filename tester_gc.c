/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:15:32 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 22:55:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"
#include "executer.h"
#include "src/executer/private_executer.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "src/minishell.h"
#include "src/mssignal.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h>
#include <stdbool.h>

typedef struct	s_garbage
{
	void				*alloc;
	void				(*func_free)(void *);
	struct s_garbage	*next;
}				t_garbage;

t_garbage	*create_garbage(void *alloc, void (*func_free)(void *))
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (new == NULL)
		return (NULL);
	new->alloc = alloc;
	new->func_free = func_free;
	new->next = NULL;
	return (new);
}

t_garbage	*append_garbage(t_garbage *main, t_garbage *append)
{
	t_garbage	*tmp;

	if (main == NULL)
		return (append);
	tmp = main;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = append;
	return (main);
}

static t_garbage	**garbage_init(void)
{
	static t_garbage	*garbage = NULL;

	return (&garbage);
}

void	gc_add_garbage(void *alloc, void (*func_free)(void *))
{
	t_garbage	*new;

	new = create_garbage(alloc, func_free);
	// if (new == NULL)
		// free all garbage, exit
	*garbage_init() = append_garbage(*garbage_init(), new);
}

t_garbage	*gc_get_garbage(void)
{
	return (*garbage_init());
}

void	*gc_malloc_and_add(size_t size, size_t count)
{
	void	*alloc;

	alloc = malloc(size * count);
	// if (alloc == NULL)
		// free all garbage, exit
	gc_add_garbage(alloc, free);
	return (alloc);
}

void	gc_free_all_garbage(void)
{
	t_garbage	*garbage;
	t_garbage	*temp;

	garbage = gc_get_garbage();
	while (garbage != NULL)
	{
		temp = garbage;
		garbage = garbage->next;
		temp->func_free(temp->alloc);
		free(temp);
	}
	*garbage_init() = NULL;
}

int	main(void)
{
	t_garbage	*garbage;
	char		*test;
	t_stack		*tokstack;
	t_ast		*ast;
	char		*input = "echo |";

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	gc_add_garbage(tokstack, &lexer_free_tokstack);
	ast = parser_tokstack_to_ast(&tokstack);
	gc_add_garbage(ast, &parser_free_ast);
	test = gc_malloc_and_add(sizeof(char), 100);
	test = gc_malloc_and_add(sizeof(char), 100);
	test = gc_malloc_and_add(sizeof(char), 100);
	test = gc_malloc_and_add(sizeof(char), 100);
	test = gc_malloc_and_add(sizeof(char), 100);
	gc_free_all_garbage();
	return (0);
}
