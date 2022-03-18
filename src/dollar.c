/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:46:57 by acristin          #+#    #+#             */
/*   Updated: 2022/03/16 16:06:28 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char **envp, char *line, int len)
{
	char	*name;
	int		j;

	name = malloc(sizeof(char) * len);
	if (!name)
		return (0);
	ft_strlcpy(name, line, len);
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(name, envp[j], max(ft_len_eq(envp[j]),
					ft_strlen(name))))
		{
			free(name);
			name = ft_strdup(envp[j] + ft_len_eq(envp[j]) + 1);
			return (name);
		}
	}
	if (!ft_strncmp("?", name, 1))
	{
		free(name);
		return (ft_itoa(g_line.status));
	}
	free(name);
	return (NULL);
}

void	replace_var(int start, int len, char *name, int *i)
{
	int		j;
	char	*new;
	int		lenname;

	j = 0;
	lenname = 0;
	if (name)
		lenname = ft_strlen(name);
	new = malloc(sizeof(char) * (ft_strlen(g_line.line) + lenname));
	if (!new)
		return ;
	ft_strlcpy(new, g_line.line, start + 1);
	if (name)
		ft_strlcpy(new + start, name, ft_strlen(name) + 1);
	ft_strlcpy(new + start + lenname, g_line.line + start + len,
		ft_strlen(g_line.line + start + len) + 1);
	free(g_line.line);
	g_line.line = ft_strdup(new);
	(*i) = start;
	free(new);
	if (name)
		free(name);
}

void	find_name(int *i, char **envp)
{
	int		count;
	char	*name;

	count = 0;
	(*i)++;
	if (ft_isdigit(*(g_line.line + (*i))) || *(g_line.line + (*i)) == '?')
	{
		count = 1;
		(*i)++;
	}
	else
	{
		while (*(g_line.line + (*i)) != '\0' && (*(g_line.line + (*i)) == '_'
				|| ft_isdigit(*(g_line.line + (*i)))
				|| ft_isalpha(*(g_line.line + (*i)))))
		{
			(*i)++;
			count++;
		}
	}
	name = find_var(envp, g_line.line + ((*i) - count), count + 1);
	replace_var((*i) - count - 1, count + 1, name, i);
}

void	dollar(void)
{
	int		i;
	int		q;
	int		q21;

	i = 0;
	q = 0;
	q21 = 0;
	while (g_line.line[i] != '\0')
	{
		if (g_line.line[i] == '"' && q % 2 == 0)
			q21++;
		if (g_line.line[i] == '\'')
			q++;
		if ((q % 2 == 0 || q21 % 2 == 1) && g_line.line[i] == '$')
			find_name(&i, g_line.envp);
		else
			i++;
	}
}
