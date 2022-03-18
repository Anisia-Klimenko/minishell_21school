/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: botilia <botilia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:24:03 by botilia           #+#    #+#             */
/*   Updated: 2022/03/16 13:19:35 by botilia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr_for_mini(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' || s[i] == c)
	{
		if (s[i] == c)
			return ((char *)s + (i + 1));
		i++;
	}
	return (NULL);
}

char	**cd_pwd_oldpwd(char *old_path)
{
	char	*pwd;
	char	cwd[4096];
	char	*new_old_path;

	new_old_path = ft_strjoin("OLDPWD=", old_path);
	free(old_path);
	pwd = ft_strjoin("PWD=", getcwd(cwd, 4096));
	g_line.envp = replace_envp_el(g_line.envp, pwd, "PWD=");
	if (check_unset("OLDPWD=", g_line.envp))
		g_line.envp = replace_envp_el(g_line.envp, new_old_path, "OLDPWD=");
	else
		g_line.envp = export_envp(g_line.envp, new_old_path, 1);
	free(new_old_path);
	free(pwd);
	return (g_line.envp);
}

char	**ft_todir(char **args, int ifcd)
{
	char	*path;
	char	*old_path;
	char	cwd[4096];

	old_path = ft_strdup(getcwd(cwd, 4097));
	if (ifcd && (!args[1] || !ft_strncmp(args[1], "~", ft_strlen(args[1]))))
		chdir(getenv("HOME"));
	else if (args[1])
	{
		if (ft_strncmp(args[1], "~/", 2) == 0)
		{
			chdir(getenv("HOME"));
			path = ft_strdup(ft_strchr_for_mini(args[1], '/'));
			validpath(path, old_path, ifcd);
			free(path);
		}
		else
			validpath(args[1], old_path, ifcd);
	}
	else if (ifcd && !ft_strncmp(args[1], "..", ft_strlen("..")))
		chdir("..");
	if (ifcd)
		g_line.envp = cd_pwd_oldpwd(old_path);
	return (g_line.envp);
}
