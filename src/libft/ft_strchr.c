/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:46:31 by acristin          #+#    #+#             */
/*   Updated: 2021/10/14 11:55:21 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				flag;
	unsigned char	ch;

	flag = 1;
	ch = (unsigned char)c;
	while (*s != '\0' && flag)
	{
		if (*s == ch)
			flag = 0;
		s++;
	}
	if (flag && ch != '\0')
		return (0);
	if (ch == '\0')
		return ((char *)s);
	s--;
	return ((char *)s);
}
