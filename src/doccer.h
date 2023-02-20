/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:28:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 14:34:01 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOCCER_H
# define DOCCER_H

# include "lexer.h" // t_stack
# include "minishell.h" // t_status

char	*doccer_interpret_docs(t_stack *tokstack, char *input);

#endif
