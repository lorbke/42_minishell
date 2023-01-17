/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:34:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 18:34:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

void	debug_parser(char *input, char *seps, char *esc);
void	debug_tokenizer(char *input, char *seps, char *esc);

#endif
