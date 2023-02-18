/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_private.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:39:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/18 12:47:38 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_PRIVATE_H
# define CD_PRIVATE_H

// utils
void	set_path(char *var, char *value);
char	*get_path(char *var);
int		change_prev_dir(void);
int		check_for_dots(char *path, int *i);

// modes
int		handle_dots(char *path);
int		handle_dash(char *oldpwd);

#endif
