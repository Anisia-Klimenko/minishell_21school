/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:11:42 by botilia           #+#    #+#             */
/*   Updated: 2022/03/16 16:32:27 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export_envp(char **envp, char *str, int free)
{
	char	**new_mass;
	int		j;

	new_mass = malloc(sizeof(char *) * (size_mass(envp) + 2));
	if (!new_mass)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		new_mass[j] = ft_strdup(envp[j]);
		j++;
	}
	new_mass[j] = ft_strdup(str);
	j++;
	new_mass[j] = NULL;
	if (free)
		ft_free(envp);
	return (new_mass);
}

char	*check_double(char *args, char **envp)
{
	int		i;
	char	*str_tmp;

	i = 0;
	str_tmp = malloc(sizeof(char) * (ft_sym_export(args) + 1));
	if (!str_tmp)
		return (NULL);
	while (args[i] != '\0' && args[i] != '=')
	{
		str_tmp[i] = args[i];
		i++;
	}
	str_tmp[i] = '\0';
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str_tmp, envp[i], max(ft_strlen(str_tmp),
					ft_sym_export(envp[i]))))
			return (str_tmp);
		i++;
	}
	free(str_tmp);
	return (NULL);
}

char	**replace_envp_el(char **envp, char *args, char *new)
{
	char	**new_mass;
	int		j;

	j = 0;
	new_mass = malloc(sizeof(char *) * (size_mass(envp) + 1));
	if (!new_mass)
		return (NULL);
	while (envp[j])
	{
		if (ft_strncmp(envp[j], new, max(ft_strlen(new),
					ft_sym_export(envp[j]))))
			new_mass[j] = ft_strdup(envp[j]);
		else
			new_mass[j] = ft_strdup(args);
		j++;
	}
	new_mass[j] = NULL;
	ft_free(envp);
	return (new_mass);
}

char	**sort_mass_bubble(char **mass)
{
	int		i;
	int		k;
	int		j;
	char	*tmp;

	i = -1;
	j = size_mass(mass);
	while (++i < (j - 1))
	{
		k = -1;
		while (++k < (j - i - 1))
		{
			if (ft_strncmp(mass[k], mass[k + 1], ft_sym_export(mass[k])) > 0)
			{
				tmp = ft_strdup(mass[k]);
				free(mass[k]);
				mass[k] = ft_strdup(mass[k + 1]);
				free(mass[k + 1]);
				mass[k + 1] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	mass[i + 1] = NULL;
	return (mass);
}

char	**mass_quots_after(char **tmpmass)
{
	int		i;
	int		j;
	int		k;
	char	**after;

	after = malloc(sizeof(char *) * (size_mass(tmpmass) + 1));
	if (!after)
		return (NULL);
	i = -1;
	while (tmpmass[++i])
	{
		k = 0;
		after[i] = malloc(sizeof(char) * (ft_strlen(tmpmass[i])
					- ft_sym_export(tmpmass[i]) + 1));
		if (!after[i])
			return (NULL);
		j = ft_sym_export(tmpmass[i]);
		while (tmpmass[i][++j] != '\0')
			after[i][k++] = tmpmass[i][j];
		after[i][k] = '\0';
	}
	after[i] = NULL;
	return (after);
}
