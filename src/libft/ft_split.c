/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anisia <anisia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:46:18 by acristin          #+#    #+#             */
/*   Updated: 2021/10/15 12:05:56 by anisia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_len_split(char const *s, char c, int skip)
{
	int	i;
	int	n;
	int	start;

	i = 0;
	n = 0;
	while (n < skip)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
			i++;
		n++;
	}
	while (s[i] != '\0' && s[i] == c)
		i++;
	start = i;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i - start);
}

static int	ft_fill_word(char const *src, char *dest, int j, char c)
{
	int	i;

	i = 0;
	while (src[j + i] != '\0' && src[j + i] == c)
		j++;
	while (src[j + i] != '\0' && src[j + i] != c)
	{
		dest[i] = src[j + i];
		i++;
	}
	dest[i] = '\0';
	return (j + i);
}

static void	ft_free(char **s, int i)
{
	while (i > 0)
	{
		free(s[i - 1]);
		i--;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		words;
	char	**split;

	i = 0;
	j = 0;
	words = ft_count_words(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (0);
	while (i < words)
	{
		split[i] = malloc(sizeof(char) * (ft_len_split(s, c, i) + 1));
		if (!split[i])
		{
			ft_free(split, i);
			return (0);
		}
		j = ft_fill_word(s, split[i], j, c);
		i++;
		j++;
	}
	split[i] = 0;
	return (split);
}
