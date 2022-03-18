/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:14:46 by anisiaklime       #+#    #+#             */
/*   Updated: 2022/03/17 11:30:47 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(void)
{
	int		pipes;
	t_list	*tmp;

	pipes = 0;
	tmp = g_line.list;
	while (tmp)
	{
		if (!ft_strncmp("|", tmp->content, 1))
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}

void	fill_redirect(char *red, char *path)
{
	if (!ft_strncmp(">>", red, 2))
		ft_dictadd_back(&ft_cmdlast(g_line.cmd)->outfd, ft_dictnew(">>", path));
	else if (!ft_strncmp("<<", red, 2))
		ft_dictadd_back(&ft_cmdlast(g_line.cmd)->infd, ft_dictnew("<<", path));
	else if (!ft_strncmp(">", red, 1))
		ft_dictadd_back(&ft_cmdlast(g_line.cmd)->outfd, ft_dictnew(">", path));
	else if (!ft_strncmp("<", red, 1))
		ft_dictadd_back(&ft_cmdlast(g_line.cmd)->infd, ft_dictnew("<", path));
}

void	fill_args(void *content)
{
	t_cmd	*tmp;

	tmp = ft_cmdlast(g_line.cmd);
	if (tmp->args[0])
		tmp->args = export_envp(tmp->args, content, 0);
	else
	{
		tmp->args[0] = ft_strdup(content);
		tmp->args[1] = NULL;
	}
}

void	count_cmd(t_list *list)
{
	t_list	*tmp;
	t_cmd	*tmpcmd;

	tmp = list;
	while (tmp && ft_strncmp("|", tmp->content, 1))
	{
		if (!ft_strncmp(">", tmp->content, 1) || !ft_strncmp("<",
				tmp->content, 1))
			tmp = tmp->next;
		else
			ft_cmdlast(g_line.cmd)->count++;
		tmp = tmp->next;
	}
	tmpcmd = ft_cmdlast(g_line.cmd);
	tmpcmd->args = ft_calloc(tmpcmd->count, sizeof(char *));
	if (!tmpcmd->args)
		return ;
}

void	get_cmd(void)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = g_line.list;
	cmd = g_line.cmd;
	while (tmp)
	{
		ififis(tmp);
		while (tmp && ft_strncmp("|", tmp->content, 1))
		{
			if (!ft_strncmp(">", tmp->content, 1) || !ft_strncmp("<",
					tmp->content, 1))
			{
				fill_redirect(tmp->content, tmp->next->content);
				tmp = tmp->next;
			}
			else
				fill_args(tmp->content);
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	id_cmd();
}
