/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:36:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 17:53:58 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strjoin, ft_substr, ft_isalpha, ft_isalnum, ft_strlen
#include "../../utils.h" // check_naming_convention
#include <stdio.h> // printf

int	check_if_var_exists(t_sym_tab *temp, char *var_name)
{
	int	i;

	i = 0;
	while (temp->var[i] != '\0' && temp->var[i] != '=')
		i++;
	if (ft_strncmp(temp->var, var_name, i) == 0)
		return (1);
	return (0);
}

void	update_var(t_sym_tab *temp, char *var_name, char *var_value)
{
	int	i;

	i = 0;
	while (temp->var[i] != '\0' && temp->var[i] != '=')
		i++;
	if (var_value != NULL)
	{
		free(temp->var);
		temp->var = ft_strjoin(var_name, var_value);
	}
}

char	*init_var_name(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	var_name = ft_substr(var, 0, i);
	if (check_naming_convention(var_name) == 0)
	{
		// @note needs to be printed to stderr
		printf("minishell: export: `%s': not a valid identifier\n", var_name);
		return (NULL);
	}
	return (var_name);
}

char	*init_var_value(char *var, char *var_name)
{
	int		i;
	char	*var_value;

	i = ft_strlen(var_name);
	if (var[i] == '=')
	{
		var_value = ft_substr(var, i, ft_strlen(var) - i);
		return (var_value);
	}
	return (NULL);
}
