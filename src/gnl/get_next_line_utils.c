/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:45:35 by acristin          #+#    #+#             */
/*   Updated: 2021/11/28 12:32:18 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

char	*ft_strnchr(const char *s, int c, int size)
{
	int				flag;
	int				i;
	unsigned char	ch;

	flag = 1;
	ch = (unsigned char)c;
	i = 0;
	while (*s != '\0' && flag)
	{
		if (*s == ch)
			flag = 0;
		s++;
		i++;
	}
	if (flag && ch != '\0')
		return (0);
	if (ch == '\0' && i < size)
		return ((char *)s);
	if (ch == '\0' && i == size)
		return (0);
	s--;
	return ((char *)s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0 && (src || dest))
	{
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dest);
}

char	*ft_strdup_gnl(const char *s, int endl)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	if (!len)
		return (NULL);
	dest = malloc(sizeof(*dest) * (len + 1 + endl));
	if (!dest)
		return (0);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\n';
	dest[i + endl] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *str, char const *buf, int endl)
{
	char	*dup;
	int		lenstr;
	int		lenbuf;

	if (str != NULL && buf != NULL)
	{
		lenstr = ft_strlen(str);
		lenbuf = ft_strlen(buf);
		dup = ft_strdup_gnl(str, 0);
		free(str);
		str = malloc(sizeof(char) * (lenstr + lenbuf + 1 + endl));
		if (str)
		{
			ft_memcpy(str, dup, lenstr);
			ft_memcpy(str + lenstr, buf, lenbuf);
			str[lenstr + lenbuf] = '\n';
			str[lenstr + lenbuf + endl] = '\0';
		}
		free(dup);
	}
	else if (!str)
		str = ft_strdup_gnl(buf, endl);
	return (str);
}
