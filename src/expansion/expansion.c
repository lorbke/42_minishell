/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/09 21:37:10 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*expand_env(char *arg);

// @note seems to break my func (I guess it is the memcpy)
char	*ft_realloc(char *ptr, int len)
{
	char	*result;

	result = malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	ft_memcpy(result, ptr, ft_strlen(ptr));
	free(ptr);
	ptr = 0;
	return (result);
}

// @note needs to be change because the var can also include numericals + underscores
char	*get_var(char *arg, int *index)
{
	int		i;
	char	*var;

	i = 0;
	while (arg[i] && ft_isalpha(arg[i]))
		i++;
	var = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (arg[i] && ft_isalpha(arg[i]))
	{
		var[i] = arg[i];
		i++;
	}
	var[i] = '\0';
	*index += i;
	return (var);
}

int	find_closing_quote(char *str, int *index)
{
	int	str_len;

	str_len = 1;
	while (str[str_len])
	{
		if (str[str_len] == '\'')
		{
			(*index)++;
			break ;
		}
		str_len++;
		(*index)++;
	}
	return (str_len);
}

// @note needs to be tested if quotes are implemented in parser
char*	handle_single_quotes(char *result, char *str, int *index, int *result_index)
{
	int		i;
	int		str_len;
	char	*arg;

	(*index)++;
	str_len = find_closing_quote(str, &(*index));
	if (!result)
		arg = malloc(sizeof(char) * str_len + 1);
	else
		arg = ft_realloc(result, ft_strlen(result) + str_len);
	i = 0;
	while (i < str_len)
	{
		arg[i] = str[i];
		i++;
		(*result_index)++;
	}
	return (arg);
}

char	*create_new_arg(char *result, char *var, int *index)
{
	int		i;
	int		len;
	char	*arg;

	i = 0;
	len = 0;
	if (!result)
		arg = malloc(sizeof(char) * (ft_strlen(var) + 1));
	else
	{
		arg = ft_realloc(result, ft_strlen(result) + ft_strlen(var));
		len = ft_strlen(arg);
	}
	while (var[i])
		arg[len++] = var[i++];
	arg[len] = '\0';
	*index = ft_strlen(var);
	return (arg);
}

char	*add_char_to_string(char *result, char c, int *index)
{
	char *arg;

	if (!result)
		arg = malloc(sizeof(char) * 2);
	else
		arg = ft_realloc(result, ft_strlen(result));
	arg[(*index)++] = c;
	arg[(*index)] = '\0';
	return (arg);
}

void	quote_removal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

char	*copy_result_to_argv(char *result)
{
	char	*arg;
	int		i;

	if (result == NULL)
		return (NULL);
	i = 0;
	arg = malloc(sizeof(char) * ft_strlen(result) + 1);
	while (result[i])
	{
		arg[i] = result[i];
		i++;
	}
	arg[i] = '\0';
	quote_removal(arg);
	free(result);
	return (arg);
}

char *check_var_validity(char *argv, int *index, int *result_index)
{
	char	*var;
	char	*result;

	(*index)++;
	argv++;
	result = NULL;
	var = get_var(argv, &(*index));
	var = expand_env(var);
	if (var != NULL)
		result = create_new_arg(result, var, &(*result_index));
	return (result);
}

void	expand(char **argv)
{
	int		i;
	int		j;
	int		result_index;
	char	*var;
	char	*result;

	i = 1;
	while (argv[i])
	{
		result = NULL;
		j = 0;
		result_index = 0;
		while (argv[i][j] && argv[i][j] != ' ')
		{
			if (argv[i][j] == '$')
				result = check_var_validity(&argv[i][j], &j, &result_index);
			else if (argv[i][j] == '\'')
				result = handle_single_quotes(result, &argv[i][j], &j, &result_index);
			else
			{
				result = add_char_to_string(result, argv[i][j], &result_index);
				j++;
			}
		}
		argv[i] = copy_result_to_argv(result);
		i++;
	}
}

int	get_var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*expand_env(char *arg)
{
	int			len;
	t_sym_tab	*temp;
	char		*value;

	temp = *g_sym_table;
	value = NULL;
	while (temp)
	{
		if (ft_strlen(arg) > get_var_len(temp->var))
			len = ft_strlen(arg);
		else
			len = get_var_len(temp->var);
		if (ft_strncmp(arg, temp->var, len) == 0)
		{
			value = ft_strchr(temp->var, '=') + 1;
			break ;
		}
		temp = temp->next;
	}
	return (value);
}
