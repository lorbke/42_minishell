/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:10:26 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/16 16:38:33 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lib/env/env.h"

void	free_split(char **split);
void	free_list(t_sym_tab **head);
int		ft_strcmp(const char *s1, const char *s2);
int		check_naming_convention(char *var_name);

#endif
