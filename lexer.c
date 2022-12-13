/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/13 16:59:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/libft/includes/libft.h"

static char	*set_stringp(char **stringp, char *start, char *end)
{
	*start = '\0';
	start = *stringp;
	*stringp = end;
	return (start);
}

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*start;
	char	*end;
	int		j;

	if (!*stringp || !delim)
		return (NULL);
	start = *stringp;
	if (!**stringp)
	{
		*stringp = NULL;
		return (start);
	}
	while (*start)
	{
		j = 0;
		while (delim[j])
		{
			if (*start == delim[j])
				return (set_stringp(stringp, start, start + 1));
			j++;
		}
		start++;
	}
	if (start != *stringp)
		return (set_stringp(stringp, start, start + 1));
	return (start);
}

int	main(void)
{
     char *sep = "\\/:;=-";
	 char *test;
	 char *test2;

	 test = malloc(100);
	 test2 = malloc(100);
     strcpy(test, "::;This;is.a:test:of=the/string\\tokenizer-function.:;;");
     strcpy(test2, "::;This;is.a:test:of=the/string\\tokenizer-function.:;;");


     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
     printf("%s\n", strsep(&test, sep));
	 printf("stringp: %s\n", test);
	 printf("-\n-\n");
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
     printf("%s\n", ft_strsep(&test2, sep));
	 printf("stringp: %s\n", test2);
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", strsep(test, sep));
    //  printf("%s\n", test[1]);

  return 0;
}
