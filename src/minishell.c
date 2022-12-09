/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/09 20:33:42 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define PROMPT "minishell> "

/* Free this 
	free(line);
	rl_clear_history();
*/

/* Read-Eval-Print-Loop */
void	ms_rep_loop(void)
{
	char	*line;

	line = ft_calloc(LINE_MAX, sizeof(char));
	while (1)
	{
		line = readline(PROMPT);
		if (*line)
			add_history(line);
	}
}

int	main(void)
{
	ms_rep_loop();
	return (0);
}
