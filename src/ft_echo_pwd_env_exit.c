/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_pwd_env_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:05:48 by botilia           #+#    #+#             */
/*   Updated: 2022/03/17 10:39:14 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	g_line.status = 0;
	if (!cmd->args[1])
	{
		printf("\n");
		return ;
	}
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n",
			ft_strlen(cmd->args[i])))
		i++;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])))
		printf("\n");
}

void	ft_pwd(void)
{
	char	cwd[4096];

	getcwd(cwd, 4097);
	printf("%s\n", cwd);
	g_line.status = 0;
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_line.envp[i])
	{
		if (!ft_strchr(g_line.envp[i], '='))
			i++;
		else
		{
			printf("%s\n", g_line.envp[i]);
			i++;
		}
	}
	g_line.status = 0;
}

void	ft_exit(t_cmd *cmd, int ifexit)
{
	int	i;

	i = 0;
	if (ifexit && !(cmd->args[1] && cmd->args[2]))
		printf("exit\n");
	if (cmd->args[1] && cmd->args[2])
		errmsg("", "", "minishell: exit: too many arguments", -1);
	if (cmd->args[1])
	{
		while (ft_isdigit(cmd->args[1][i]))
			i++;
		if ((size_t)i != ft_strlen(cmd->args[1]))
			errmsg("minishell: exit: ", cmd->args[1],
				": numeric argument required", -255);
	}
	if (ifexit && !(cmd->args[1] && cmd->args[2]))
	{
		if (!cmd->args[1])
			exit(0);
		else if ((size_t)i != ft_strlen(cmd->args[1]))
			exit(255);
		else
			exit(ft_atoi(cmd->args[1]) % 256);
	}
}
