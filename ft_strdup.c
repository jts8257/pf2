/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeong <tjeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:59:19 by tjeong            #+#    #+#             */
/*   Updated: 2021/07/03 13:55:10 by tjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*new_ptr;

	len = 0;
	while (s1[len])
		len++;
	if (!(new_ptr = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_ptr[i] = s1[i];
		i++;
	}
	new_ptr[i] = '\0';
	return (new_ptr);
}
