/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:10:39 by acristin          #+#    #+#             */
/*   Updated: 2022/03/16 10:25:13 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*redirect(int *i, char *redir)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 3);
	if (!tmp)
		return (0);
	tmp[0] = redir[0];
	tmp[1] = redir[1];
	tmp[2] = '\0';
	(*i)++;
	return (tmp);
}

char	*separator(int *i, char c)
{
	char	*tmp;

	(void) i;
	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
		return (0);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}

int	open_quotes(int *i)
{
	int	j;

	j = 0;
	while (j < *i)
	{
		if (g_line.line[j] == '\'')
		{
			j++;
			while (j < *i && g_line.line[j] != '\'')
				j++;
			if (j == *i)
				return (1);
		}
		if (g_line.line[j] == '"')
		{
			j++;
			while (j < *i && g_line.line[j] != '"')
				j++;
			if (j == *i)
				return (1);
		}
		j++;
	}
	return (0);
}

char	*string(int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	if (!ft_strlen(g_line.line + (*i)))
		return (0);
	tmp = malloc(sizeof(char) * (ft_strlen(g_line.line + (*i)) + 1));
	if (!tmp)
		return (0);
	while (!ft_strchr(" |<>\0", g_line.line[(*i)]) || open_quotes(i))
	{
		tmp[j] = g_line.line[(*i)];
		j++;
		(*i)++;
	}
	tmp[j] = '\0';
	(*i)--;
	return (tmp);
}

void	parser(void)
{
	int		i;

	i = 0;
	while (g_line.line[i] != '\0')
	{
		while (g_line.line[i] != '\0' && g_line.line[i] == ' ')
			i++;
		if (!ft_strncmp(g_line.line + i, ">>", 2))
			ft_lstadd_back(&g_line.list, ft_lstnew((void *)redirect(&i, ">>")));
		else if (!ft_strncmp(g_line.line + i, "<<", 2))
			ft_lstadd_back(&g_line.list, ft_lstnew((void *)redirect(&i, "<<")));
		else if (g_line.line[i] == '|')
			ft_lstadd_back(&g_line.list, ft_lstnew((void *)separator(&i, '|')));
		else if (g_line.line[i] == '>')
			ft_lstadd_back(&g_line.list, ft_lstnew((void *)separator(&i, '>')));
		else if (g_line.line[i] == '<')
			ft_lstadd_back(&g_line.list, ft_lstnew((void *)separator(&i, '<')));
		else if (g_line.line + i)
			ft_lstadd_back(&g_line.list, ft_lstnew((void *)string(&i)));
		i++;
	}
}
