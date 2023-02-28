/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:43:00 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:37:59 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strlen, ft_strdup, ft_strjoin
#include "../../utils.h" // utils_ft_strcmp
#include <errno.h> // errno
#include <stdio.h> // perror

static char	*concat_var(char *var, char *value);

/**
 * *|MARCADOR_CURSOR|*
 * 
 * @param path The path to be checked.
 * @param i the index of the path string
 * 
 * @return The number of ".." in the path.
 */
int	check_for_dots(char *path, int *i)
{
	int	count;

	count = 0;
	while (ft_strncmp(&path[*i], "..", ft_strlen("..")) == 0)
	{
		count++;
		*i += 3;
	}
	return (count);
}

/**
 * It changes the current working directory to the previous directory
 * 
 * @return The return value is the error number.
 */
int	change_prev_dir(void)
{
	int		i;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (errno);
	i = ft_strlen(cwd) - 1;
	while (cwd[i] != '/' && i > 0)
	{
		cwd[i] = '\0';
		i--;
	}
	if (chdir(cwd) != 0)
	{
		free(cwd);
		return (errno);
	}
	free(cwd);
	return (0);
}

/**
 * It takes a variable name and a value, and if the variable is already 
 * in the symbol table, it updates
 * the value, otherwise it adds the variable to the symbol table
 * 
 * @param var The name of the variable to set.
 * @param value The value of the variable.
 * 
 * @return A pointer to a new node in the symbol table.
 */
void	set_path(char *var, char *value)
{
	t_sym_tab	*temp;
	char		*new_var;

	if (g_sym_table == NULL)
		temp = NULL;
	else
		temp = *g_sym_table;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var)) == 0)
		{
			free(temp->var);
			temp->var = concat_var(var, value);
			return ;
		}
		temp = temp->next;
	}
	if (value != NULL)
	{
		new_var = concat_var(var, value);
		env_add_to_back(g_sym_table, env_new_sym_tab_node(new_var));
		free(new_var);
	}
}

/**
 * It takes a variable name and a value, and returns a string 
 * of the form `VAR=value`
 * 
 * @param var the name of the variable
 * @param value the value of the variable
 * 
 * @return A string that is the concatenation of the variable 
 * name and its value.
 */
static char	*concat_var(char *var, char *value)
{
	char	*new_var;
	char	*var_name;

	var_name = ft_strjoin(var, "=");
	new_var = ft_strjoin(var_name, value);
	free(var_name);
	return (new_var);
}
