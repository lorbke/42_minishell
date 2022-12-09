/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:11:10 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/13 12:17:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;

	if (lst == NULL)
		return (NULL);
	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == NULL)
		return (newlst);
	newlst->content = (*f)(lst->content);
	newlst->next = ft_lstmap(lst->next, f, del);
	return (newlst);
}
