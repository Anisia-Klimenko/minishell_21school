/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:22:45 by acristin          #+#    #+#             */
/*   Updated: 2022/03/16 16:32:52 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**mass_quots_before(char **tmpmass)
{
	int		i;
	int		j;
	char	**before;

	before = malloc(sizeof(char *) * (size_mass(tmpmass) + 1));
	if (!before)
		return (NULL);
	i = -1;
	while (tmpmass[++i])
	{
		j = -1;
		before[i] = malloc(sizeof(char) * (ft_sym_export(tmpmass[i]) + 1));
		if (!before[i])
			return (NULL);
		if (!ft_strchr(tmpmass[i], '='))
			before[i] = ft_strdup(tmpmass[i]);
		else
		{
			while (tmpmass[i][++j] != '=')
				before[i][j] = tmpmass[i][j];
			before[i][j] = '\0';
		}
	}
	before[i] = NULL;
	return (before);
}

void	exp_withot_args(char **envp)
{
	int		i;
	char	**tmpmass;
	char	**before;
	char	**after;

	i = 0;
	tmpmass = new_envp(envp);
	tmpmass = sort_mass_bubble(tmpmass);
	before = mass_quots_before(tmpmass);
	after = mass_quots_after(tmpmass);
	while (tmpmass[i])
	{
		if (!ft_strchr(tmpmass[i], '='))
			printf("declare -x %s\n", before[i]);
		else
			printf("declare -x %s=\"%s\"\n", before[i], after[i]);
		i++;
	}
	ft_free(tmpmass);
	ft_free(before);
	ft_free(after);
}

void	change_envp(char *new, char **args, int i)
{
	if (new && ft_strrchr(args[i], '='))
		g_line.envp = replace_envp_el(g_line.envp, args[i], new);
	else if (!new)
		g_line.envp = export_envp(g_line.envp, args[i], 1);
}

char	**ft_export(char **args)
{
	int		i;
	int		j;
	char	*new;

	if (!args[1])
		exp_withot_args(g_line.envp);
	i = 0;
	while (args[++i])
	{
		j = -1;
		new = check_double(args[i], g_line.envp);
		while (args[i][++j])
		{
			if (!ft_isalpha(args[i][0]) || args[i][0] == '=')
				errmsg("minishell: export: `", args[i],
					"': not a valid identifier", -1);
			else
				change_envp(new, args, i);
			break ;
		}
		if (new)
			free(new);
	}
	return (g_line.envp);
}
