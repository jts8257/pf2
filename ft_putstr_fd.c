/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeong <tjeong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:57:17 by tjeong            #+#    #+#             */
/*   Updated: 2021/07/03 13:58:42 by tjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return 0;
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}