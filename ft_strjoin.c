/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeong <tjeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:32:26 by tjeong            #+#    #+#             */
/*   Updated: 2021/07/03 16:19:48 by tjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(concat = (char *)malloc((s1_len + s2_len) * sizeof(char) + 1)))
		return (NULL);
	ft_bzero(concat, (s1_len + s2_len + 1));
	ft_strlcpy(concat, (char *)s1, s1_len + 1);
	ft_strlcpy(&concat[s1_len], (char *)s2, s2_len + 1);
	free(s1);
	free(s2);
	return (concat);
}
