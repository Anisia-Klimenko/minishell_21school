/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: botilia <botilia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:18:40 by botilia           #+#    #+#             */
/*   Updated: 2022/03/16 13:20:40 by botilia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ifs(int j, int i, char *args, char *str)
{
	if (j == 1 && i)
		chdir(str);
	else if (j != 1)
		errmsg("minishell: cd: ", args, ": No such file or directory", -1);
	else if (j == 1 && !i)
		errmsg("minishell: cd: ", args, ": Not a directory", -1);
}

void	inside_validpath(char *str, int j, char *old_path, char *args)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		status;
	int				ifcd;
	int				i;

	ifcd = j;
	entry = NULL;
	dir = opendir("./");
	entry = readdir(dir);
	j = 0;
	while (entry != NULL)
	{
		if (ft_strncmp(str, entry->d_name, ft_strlen(entry->d_name)) == 0)
		{
			stat(str, &status);
			j = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	i = S_ISDIR(status.st_mode);
	ifs(j, i, args, str);
	if ((j != 1 || !i) || !ifcd)
		chdir(old_path);
}

void	validpath(char *args, char *old_path, int ifcd)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(args);
	while (args[j] && args[j] != '/' )
		j++;
	if (j != i)
		str = ft_split(args, '/');
	else
		str = ft_split(args, '\0');
	i = 0;
	while (str[i])
	{
		j = ifcd;
		inside_validpath(str[i], j, old_path, args);
		i++;
	}
	ft_free(str);
}
