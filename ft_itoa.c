/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeong <tjeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 10:13:03 by tjeong            #+#    #+#             */
/*   Updated: 2021/07/03 13:55:42 by tjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int	ft_digit(int n)
{
	int digit;

	digit = 1;
	while (n /= 10)
		digit++;
	return (digit);
}

static void	ft_itoa_insert(int n, char *converted, int size)
{
	int limit;
	int sign;

	limit = 0;
	sign = 1;
	converted[size] = '\0';
	if (n < 0)
	{
		converted[0] = '-';
		limit = 1;
		sign = -1;
	}
	while (size-- > limit)
	{
		converted[size] = (((n % 10) * sign) + '0');
		n /= 10;
	}
}

char		*ft_itoa(int n)
{
	char	*converted;
	int		size;

	size = n < 0 ? ft_digit(n) + 1 : ft_digit(n);
	converted = (char *)malloc(size * sizeof(char) + 1);
	if (!converted)
		return (NULL);
	else
		ft_itoa_insert(n, converted, size);
	return (converted);
}
