/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:45:03 by acristin          #+#    #+#             */
/*   Updated: 2021/10/14 11:54:07 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_check_int_min_zero(char *s, int *n)
{
	if (*n == -2147483648)
	{
		s[0] = '-';
		s[1] = '2';
		*n = 147483648;
	}
	if (*n == 0)
		s[0] = '0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		len;

	len = ft_numlen(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	i = -1;
	s = ft_check_int_min_zero(s, &n);
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		s[len - (++i) - 1] = (char)(n % 10 + 48);
		n = n / 10;
	}
	s[len] = '\0';
	return (s);
}
