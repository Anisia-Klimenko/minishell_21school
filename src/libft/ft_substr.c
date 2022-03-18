/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:47:18 by acristin          #+#    #+#             */
/*   Updated: 2021/10/16 18:58:59 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_s;
	unsigned int	i;

	if (start > ft_strlen(s))
	{
		new_s = malloc(sizeof(*s));
		*new_s = '\0';
		return (new_s);
	}
	if (start + len > ft_strlen(s))
		new_s = malloc(sizeof(*s) * (ft_strlen(s) - start + 1));
	else
		new_s = malloc(sizeof(*s) * (len + 1));
	if (new_s)
	{
		i = start;
		while (i < start + len && i < ft_strlen(s))
		{
			new_s[i - start] = s[i];
			i++;
		}
		new_s[i - start] = '\0';
		return (new_s);
	}
	return (0);
}
