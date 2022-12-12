/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/12 19:10:55 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/libft/includes/libft.h"

char	*find_delim(const char *s, const char *delim)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (delim[j])
		{
			if (s[i] == delim[j])
				return (&((char *)s)[i]);
			j++;
		}
		i++;
	}
	// if (!delim[j])
	// 	return (&((char *)s)[i]);
	return (NULL);
}

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*start;
	char	*end;

	end = strchr(*stringp, *delim);
	return (end);
}

int	main(void)
{
     char *sep = "\\/:;=-";
	 char **test;

	 test = malloc(2 * sizeof(char *));
	 test[0] = malloc(100);
	 test[1] = malloc(100);
     strcpy(*test, "This;is.a:test:of=the/string\\tokenizer-function.");

	printf("%s\n", find_delim(*test, sep));

    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", test[1]);

  return 0;
}
