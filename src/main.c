/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:13:35 by acristin          #+#    #+#             */
/*   Updated: 2022/03/16 15:57:07 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	if (argc != 1)
	{
		errno = 7;
		warning(argv[0], errno, 1);
	}
	g_line.envp = new_envp(envp);
	g_line.status = 0;
	minishell();
	ft_free(g_line.envp);
	return (0);
}
