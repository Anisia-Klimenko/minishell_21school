/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:14:21 by acristin          #+#    #+#             */
/*   Updated: 2022/03/17 11:05:52 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quots_pipe(void)
{
	if (!check_quotes())
	{
		errmsg("minishell: ", g_line.line, ": unclosed quotes", -21);
		add_history(g_line.line);
		free(g_line.line);
		return (1);
	}
	if (!check_first_pipe())
	{
		errmsg("minishell: syntax error near unexpected token `|'",
			NULL, NULL, -258);
		free(g_line.line);
		return (1);
	}
	return (0);
}

void	prompt_pipe(void)
{
	char	*tmpline;
	char	*tmpread;

	while (check_last_pipe(g_line.line))
	{
		tmpline = ft_strdup(g_line.line);
		free(g_line.line);
		tmpread = readline(" > ");
		g_line.line = ft_strjoin(tmpline, tmpread);
		free(tmpread);
		free(tmpline);
	}
}

void	handler_inside(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

void	prepare(void)
{	
	t_list	*tmp;

	add_history(g_line.line);
	dollar();
	parser();
	tmp = g_line.list;
	while (tmp)
	{
		tmp->content = (void *)rm_quotes(tmp->content);
		tmp = tmp->next;
	}
	get_cmd();
}

void	minishell(void)
{
	while (1)
	{
		init_g_line();
		g_line.line = readline("minishell > ");
		if (!g_line.line)
		{
			printf("\033[Aminishell > exit\n");
			exit(0);
		}
		else if (*g_line.line && ft_strlen(g_line.line))
		{
			if (check_quots_pipe())
				continue ;
			prompt_pipe();
			prepare();
			signal(SIGINT, handler_inside);
			signal(SIGQUIT, handler_inside);
			pipex(g_line.cmd);
			free(g_line.line);
			ft_free_cmd(g_line.cmd);
			ft_free_list(g_line.list);
		}
	}
}
