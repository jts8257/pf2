/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeong <tjeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:04:59 by tjeong            #+#    #+#             */
/*   Updated: 2021/07/03 13:26:28 by tjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t len;
	size_t i;

	if (!src)
		return (0);
	len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (src[i] && (i + 1) < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
