/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:01:33 by acristin          #+#    #+#             */
/*   Updated: 2022/03/17 11:09:00 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	work_child(t_child *child, t_cmd *cmd, int len)
{
	if (!cmd->infd && child->i > 0)
	{
		dup2(child->pipe[1 - child->current][0], STDIN_FILENO);
		close (child->pipe[1 - child->current][0]);
	}
	if (!cmd->outfd && child->i < len - 1)
	{
		dup2(child->pipe[child->current][1], STDOUT_FILENO);
		close (child->pipe[child->current][0]);
		close (child->pipe[child->current][1]);
	}
	r_in(cmd);
	r_out(cmd);
	if (cmd->args[0])
		execute(cmd);
	collect_variables();
	if (cmd->tmpfile)
		unlink(cmd->name);
}

void	check_cd_exit(t_cmd *cmd, int n)
{
	int	docmd;

	if (ft_cmdlen(cmd) == 1 && !n)
		docmd = 1;
	else
		docmd = 0;
	if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
		ft_exit(cmd, docmd);
	if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
		g_line.envp = ft_todir(cmd->args, docmd);
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	pipex(t_cmd *cmd)
{
	t_child	child;

	init_child(&child, cmd);
	while (++child.i < child.len)
	{
		check_cd_exit(cmd, child.i);
		if (pipe(child.pipe[child.current]) == -1)
			warning("minishell: pipe: ", errno, 1);
		child.pid = fork();
		if (child.pid)
			sig_sig_signal();
		if (child.pid < 0)
			warning("minishell: fork: ", errno, 1);
		if (!child.pid)
			work_child(&child, cmd, child.len);
		close(child.pipe[1 - child.current][0]);
		close(child.pipe[child.current][1]);
		if (!child.pid)
			exit(0);
		child.current = 1 - child.current;
		cmd = cmd->next;
		get_variables();
	}
	close(child.pipe[1 - child.current][0]);
	wait_child(child.len);
}
