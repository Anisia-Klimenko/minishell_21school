/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:47:15 by acristin          #+#    #+#             */
/*   Updated: 2021/10/14 11:56:22 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (set[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_find_end(char const *s1, char const *set, int start)
{
	int	i;
	int	j;
	int	end;

	i = start;
	end = start;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (set[j] == '\0')
			end = i;
		i++;
	}
	return (end);
}

static char	*ft_copy_str(char const *s1, char *s2, int start, int end)
{
	int	i;

	i = 0;
	while (i < end - start + 1)
	{
		s2[i] = s1[i + start];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		start;
	int		end;

	start = ft_find_start(s1, set);
	if (start < 0)
	{
		s2 = malloc(sizeof(*s1));
		*s2 = '\0';
		return (s2);
	}
	end = ft_find_end(s1, set, start);
	s2 = malloc(sizeof(char) * (end - start + 2));
	if (s2)
	{
		s2 = ft_copy_str(s1, s2, start, end);
		return (s2);
	}
	return (0);
}
