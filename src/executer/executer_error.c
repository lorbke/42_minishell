/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/08 18:26:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include <string.h> // NULL

static char	*exit_status_init(void)
{
	static char	exit_status = EXEC_SUCCESS;

	return (&exit_status);
}

void	exit_status_set(char exit_status)
{
	*exit_status_init() = exit_status;
}

char	exit_status_get(void)
{
	return (*exit_status_init());
}

static t_ast	**invalid_ast_init(void)
{
	static t_ast	*ast = NULL;

	return (&ast);
}

void	invalid_ast_set(t_ast *invalid_ast)
{
	*invalid_ast_init() = invalid_ast;
}

t_ast	*invalid_ast_get(void)
{
	return(*invalid_ast_init());
}
