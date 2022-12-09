/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:55:15 by lorbke            #+#    #+#             */
/*   Updated: 2022/08/11 19:22:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*g_hex = "0123456789abcdef";
static const char	*g_hex_cap = "0123456789ABCDEF";

static void	ft_printnbr_base(t_vector *vector, t_mods *mods,
	unsigned long int n)
{
	if (n / mods->base != 0)
		ft_printnbr_base(vector, mods, n / mods->base);
	if (mods->caps == 'x')
		ft_vector_push_back(vector, g_hex[n % mods->base], 1);
	else if (mods->caps == 'X')
		ft_vector_push_back(vector, g_hex_cap[n % mods->base], 1);
}

static long int	ft_putsign(t_vector *vector, t_mods *mods, long int n)
{
	if (n < 0 && mods->ptr == 0)
	{
		n *= -1;
		ft_vector_push_back(vector, '-', 1);
	}
	else if (mods->sign == 1 && mods->ptr == 0)
		ft_vector_push_back(vector, '+', 1);
	return (n);
}

static void	ft_mods(t_vector *vector, t_mods *mods, long int n)
{
	mods->field -= mods->ptr * 2;
	if (mods->hash == 1 && n != 0)
	{
		ft_vector_push_back(vector, '0', 1);
		ft_vector_push_back(vector, mods->caps, 1);
	}
	if (mods->space == 1)
	{
		ft_vector_push_back(vector, ' ', 1 - mods->sign);
		ft_vector_push_back(vector, ' ', mods->field - 1 - mods->nbr_len);
	}
	if (mods->right == 0)
		ft_vector_push_back(vector, mods->field_char, mods->field
			- mods->nbr_len);
	if (mods->ptr == 1)
	{
		ft_vector_push_back(vector, '0', 1);
		ft_vector_push_back(vector, 'x', 1);
	}
}

static void	ft_mods_precision(t_vector *vector, t_mods *mods, long int n)
{
	if (n == 0)
	{
		if (mods->field_prec > 0)
			mods->field_prec++;
		else if (mods->field > 0 && mods->right == 0)
			mods->field++;
	}
	if (mods->field_prec > 0 && mods->right == 0
		&& mods->nbr_len < mods->field_prec)
			mods->field -= (mods->field_prec - mods->nbr_len + mods->sign);
	if (mods->right == 0)
		ft_vector_push_back(vector, mods->field_char,
			mods->field - mods->nbr_len);
	n = ft_putsign(vector, mods, n);
	ft_vector_push_back(vector, '0', mods->field_prec
		- mods->nbr_len + mods->sign);
	if (n != 0)
		ft_printnbr_base(vector, mods, n);
}

void	ft_itoa_printf(t_vector *vector, t_mods *mods, long int n)
{
	long int	temp;

	temp = n;
	if (n < 0)
		mods->sign = 1;
	while (temp / mods->base != 0)
	{
		temp /= mods->base;
		mods->nbr_len++;
	}
	mods->nbr_len += 1 + mods->sign;
	if (mods->precision == 1)
		ft_mods_precision(vector, mods, n);
	else if (mods->field_char == '0' || mods->ptr == 1)
	{
		n = ft_putsign(vector, mods, n);
		ft_mods(vector, mods, n);
		ft_printnbr_base(vector, mods, n);
	}
	else
	{
		ft_mods(vector, mods, n);
		n = ft_putsign(vector, mods, n);
		ft_printnbr_base(vector, mods, n);
	}
}
