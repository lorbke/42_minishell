/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:12:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/07 18:22:14 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_temp(const char c, int base)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (base > 10 && c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	else if (base > 10 && c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (0);
}

static int	
	strtoi_base(const char *str, const char **endptr, int base, int sign)
{
	int	n;
	int	temp;
	int	i;

	i = 0;
	n = 0;
	while (str[i])
	{
		temp = get_temp(str[i], base);
		if (temp >= base)
			break ;
		n = ft_safemult(n, base);
		n = ft_safeadd(n * sign, temp * sign);
		if ((n == INT_MAX || n == INT_MIN) && errno == ERANGE)
			return (n);
		else
			n *= sign;
		i++;
		if ((base > 10 && !ft_isalnum(str[i]))
			|| (base <= 10 && !ft_isdigit(str[i])))
			break ;
	}
	if (endptr && errno != ERANGE && i > 0)
		*endptr = &str[i];
	return (n);
}

static int	get_i(const char *str, int base, int i)
{
	if (base == 16 && str[i] == '0' && str[i + 1] == 'x')
		return (i + 2);
	return (i);
}

static int	get_base(const char *str, int base, int i)
{
	if (base == 0 && str[i] == '0' && str[i + 1] == 'x')
		base = 16;
	if (base == 0 && str[i] == '0')
		base = 8;
	if (base == 0)
		base = 10;
	if (base < 2 || base > 36 || (!ft_isalnum(str[i])))
	{
		errno = EINVAL;
		return (-1);
	}
	if (base <= 10 && !ft_isdigit(str[i]))
	{
		errno = EINVAL;
		return (-1);
	}
	return (base);
}

/* Alternative to ft_atoi, which provides no proper error handling. This 
function will handle overflows and underflows as well as 
invalid input through errno. 
The variable endptr allows to easily index multiple numbers 
in the same string.*/
int	ft_strtoi(const char *str, const char **endptr, int base)
{
	int	i;
	int	sign;

	if (endptr)
		*endptr = str;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	base = get_base(str, base, i);
	if (base == -1)
		return (0);
	i = get_i(str, base, i);
	i = strtoi_base(&str[i], endptr, base, sign);
	if ((i == INT_MIN || i == INT_MAX) && errno == ERANGE)
		return (i);
	return (i * sign);
}
