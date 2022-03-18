/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:25:35 by acristin          #+#    #+#             */
/*   Updated: 2022/03/16 15:31:54 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_child(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(-1, 0, 0);
		i++;
	}
}

void	instd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_dict	*dict;

	tmp = cmd;
	while (tmp)
	{
		dict = tmp->infd;
		while (dict)
		{
			if (!ft_strncmp("<<", dict->key, 2))
				tmp_file(dict->value, tmp);
			dict = dict->next;
		}
		tmp = tmp->next;
	}
}

void	init_child(t_child *child, t_cmd *cmd)
{
	child->i = -1;
	child->len = ft_cmdlen(cmd);
	child->current = 0;
	child->pipe[0][0] = -1;
	child->pipe[0][1] = -1;
	child->pipe[1][0] = -1;
	child->pipe[1][1] = -1;
	instd(cmd);
}

void	collect_variables(void)
{
	int	i;

	i = 0;
	while (g_line.envp[i])
	{
		write(g_line.fd[0][1], g_line.envp[i], ft_strlen(g_line.envp[i]));
		write(g_line.fd[0][1], "\n", 1);
		i++;
	}
	close (g_line.fd[0][1]);
	write(g_line.fd[1][1], &i, sizeof(int));
	close (g_line.fd[1][1]);
	write(g_line.fd[2][1], &g_line.status, sizeof(int));
	close (g_line.fd[2][1]);
}

void	get_variables(void)
{
	int	i;
	int	j;

	read(g_line.fd[1][0], &i, sizeof(int));
	ft_free(g_line.envp);
	g_line.envp = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		g_line.envp[j] = get_next_line(g_line.fd[0][0]);
		g_line.envp[j][ft_strlen(g_line.envp[j]) - 1] = '\0';
		j++;
	}
	g_line.envp[j] = NULL;
	read(g_line.fd[2][0], &g_line.status, sizeof(int));
}
