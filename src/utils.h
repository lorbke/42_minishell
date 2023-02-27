/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:10:26 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 16:52:37 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lib/env/env.h" // t_sym_tab

// realloc
char	*ft_realloc(char *ptr, int len);
char	**realloc_string_array(char **ptr, int size);

// utils
void	free_split(char **split);
void	env_free_sym_tab(t_sym_tab **head);
int		get_string_array_len(char **array);
int		check_naming_convention(char *var);
int		ft_strcmp(const char *s1, const char *s2);

// error
void	ft_perror(char *cmd, char *str);
void	exit_print_to_stderr(char *str, char *arg);

#endif
