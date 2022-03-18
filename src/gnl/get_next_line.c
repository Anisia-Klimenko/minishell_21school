/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:45:38 by acristin          #+#    #+#             */
/*   Updated: 2021/11/28 12:32:49 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_check_save(char *str, char **save, char *p, char *tmp)
{
	char	*new;

	new = NULL;
	if (p == tmp)
		str = ft_strjoin_gnl(str, "\n", 0);
	else
	{
		*p = '\0';
		str = ft_strjoin_gnl(str, tmp, 1);
	}
	p++;
	new = ft_strdup_gnl(p, 0);
	if (*save)
		free(*save);
	*save = new;
	return (str);
}

char	*ft_save(char **save, char *str)
{
	char	*tmp;
	char	*p;
	int		len;
	int		endl;

	tmp = *save;
	endl = 0;
	len = ft_strlen(tmp);
	p = ft_strnchr(tmp, '\n', len);
	if (p)
		str = ft_check_save(str, save, p, tmp);
	else
	{
		str = ft_strjoin_gnl(str, tmp, endl);
		free(*save);
		*save = NULL;
	}
	return (str);
}

char	*ft_no_save(int fd, char **save, char *str)
{
	int		rt;
	char	buf[BUFFER_SIZE + 1];
	char	*p;
	int		endl;

	p = NULL;
	rt = read(fd, buf, BUFFER_SIZE);
	if (rt < 0)
		return (0);
	endl = 0;
	while (rt && !p)
	{
		buf[rt] = '\0';
		p = ft_strnchr(buf, '\n', rt);
		if (p)
			str = ft_check_save(str, save, p, buf);
		else
			str = ft_strjoin_gnl(str, buf, endl);
		if (!p)
			rt = read(fd, buf, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*str;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save)
		str = ft_save(&save, str);
	if (!save && !str)
		str = ft_no_save(fd, &save, str);
	if (!save && str && str[ft_strlen(str) - 1] != '\n')
		str = ft_no_save(fd, &save, str);
	if (!str && !save)
	{
		free(save);
		free(str);
		return (0);
	}
	return (str);
}
