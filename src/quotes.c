/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:46:18 by acristin          #+#    #+#             */
/*   Updated: 2022/03/16 16:10:51 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*manage_quotes(char q, int *i, char *line)
{
	int		start;
	char	*tmp;

	start = (*i);
	(*i)++;
	while (line[(*i)] != q && line[(*i)] != '\0')
		(*i)++;
	tmp = malloc(sizeof(char) * (ft_strlen(line) - 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, line, start + 1);
	ft_strlcpy(tmp + start, line + start + 1, (*i) - start);
	ft_strlcpy(tmp + (*i) - 1, line + (*i) + 1, ft_strlen(line)
		- (*i));
	if (line)
		free(line);
	line = ft_strdup(tmp);
	free(tmp);
	(*i)--;
	return (line);
}

char	*rm_quotes(void *content)
{
	int		i;
	char	*line;

	i = 0;
	line = (char *)content;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || line[i] == '\'')
			line = manage_quotes(line[i], &i, line);
		else
			i++;
		if (!line)
			return (0);
	}
	return (line);
}
