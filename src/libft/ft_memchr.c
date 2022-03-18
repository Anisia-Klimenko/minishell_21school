/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:45:37 by acristin          #+#    #+#             */
/*   Updated: 2021/10/14 11:54:35 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	void			*p;
	unsigned char	ch;

	i = 0;
	p = (void *)s;
	ch = (unsigned char) c;
	while (i < n)
	{
		if (*(unsigned char *)(p + i) == ch)
			return (p + i);
		i++;
	}
	return (0);
}
