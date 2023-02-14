/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mssignal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:17:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/14 15:19:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSSIGNAL_H
# define MSSIGNAL_H

# define MSSIG_INTER 0
# define MSSIG_NINTER 1
# define MSSIG_HDOC 2
# define MSSIG_EXEC 3

void	mssignal_change_mode(char mode);

#endif
