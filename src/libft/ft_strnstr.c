/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:47:07 by acristin          #+#    #+#             */
/*   Updated: 2021/10/16 19:37:37 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dst, const char *src, size_t n)
{
	size_t	len_src;

	if (*src == '\0')
		return ((char *)dst);
	len_src = ft_strlen(src);
	while (*dst && n >= len_src)
	{
		if (*dst == *src && ft_memcmp(dst, src, len_src) == 0)
			return ((char *)dst);
		dst++;
		n--;
	}
	return (NULL);
}
