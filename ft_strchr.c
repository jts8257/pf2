/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeong <tjeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:50:58 by tjeong            #+#    #+#             */
/*   Updated: 2021/07/03 13:48:31 by tjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char data;
	unsigned char *str;

	str = (unsigned char *)s;
	data = (unsigned char)c;
	while (*str)
	{
		if (*str == data)
			return ((char *)str);
		str++;
	}
	if (data == '\0')
		return ((char *)str);
	return (NULL);
}
