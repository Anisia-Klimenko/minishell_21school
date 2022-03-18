/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 08:17:14 by acristin          #+#    #+#             */
/*   Updated: 2022/03/17 10:22:51 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	r_out(t_cmd *cmd)
{
	t_dict	*tmp;
	int		fd;

	tmp = cmd->outfd;
	fd = 0;
	while (tmp)
	{
		if (fd)
			close(fd);
		if (!ft_strncmp(">", tmp->key, ft_strlen(tmp->key)))
			fd = open(tmp->value, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else if (!ft_strncmp(">>", tmp->key, ft_strlen(tmp->key)))
			fd = open(tmp->value, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (fd < 0)
			warning(tmp->value, errno, 1);
		tmp = tmp->next;
	}
	if (fd && dup2(fd, STDOUT_FILENO) < 0)
		warning("file: ", errno, 1);
	if (fd)
		close(fd);
}

char	*heredoc(char *delim)
{
	char	*tmpline1;
	char	*tmpline2;
	char	*tmpline3;
	char	*line;

	tmpline1 = readline("heredoc > ");
	line = NULL;
	while (ft_strncmp(tmpline1, delim, ft_strlen(tmpline1)))
	{
		tmpline2 = ft_strjoin(tmpline1, "\n");
		if (line)
		{
			tmpline3 = ft_strdup(line);
			free(line);
			line = ft_strjoin(tmpline3, tmpline2);
			free(tmpline3);
		}
		else
			line = ft_strdup(tmpline2);
		free(tmpline1);
		free(tmpline2);
		tmpline1 = readline("heredoc > ");
	}
	free(tmpline1);
	return (line);
}

void	tmp_file(char *delim, t_cmd *cmd)
{
	int		fd;
	char	*line;

	line = heredoc(delim);
	cmd->name = ft_strjoin(".tmpfile", cmd->i);
	fd = open(cmd->name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
		warning(cmd->name, errno, 1);
	write(fd, line, ft_strlen(line));
	close(fd);
	free(line);
	cmd->tmpfile = 1;
}

void	r_in(t_cmd *cmd)
{
	t_dict	*tmp;
	int		fd;

	tmp = cmd->infd;
	fd = 0;
	while (tmp)
	{
		if (fd)
			close(fd);
		if (!ft_strncmp("<", tmp->key, ft_strlen(tmp->key)))
			fd = open(tmp->value, O_RDONLY, 0777);
		else if (!ft_strncmp("<<", tmp->key, ft_strlen(tmp->key)))
			fd = open(cmd->name, O_RDONLY);
		if (fd < 0)
			warning(tmp->value, errno, 1);
		tmp = tmp->next;
	}
	if (fd && dup2(fd, STDIN_FILENO) < 0)
		warning("file: ", errno, 1);
	if (fd)
		close(fd);
	if (cmd->tmpfile && unlink(cmd->name) < 0)
		warning("unlink: ", errno, 1);
}
