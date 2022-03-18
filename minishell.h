/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acristin <acristin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:13:54 by acristin          #+#    #+#             */
/*   Updated: 2022/03/17 11:34:50 by acristin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# include "src/libft/libft.h"
# include "src/gnl/get_next_line.h"

typedef struct s_child
{
	int		current;
	pid_t	pid;
	int		pipe[2][2];
	int		i;
	int		len;
}	t_child;

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

typedef struct s_cmd
{
	char			*i;
	int				count;
	char			**args;
	t_dict			*infd;
	t_dict			*outfd;
	int				tmpfile;
	char			*name;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_line
{
	char	*line;
	char	**envp;
	int		fd[3][2];
	t_list	*list;
	t_cmd	*cmd;
	int		status;
}	t_line;

t_line	g_line;

// builtins
void	ft_echo(t_cmd *cmdx);
void	ft_pwd(void);
void	ft_env(void);
void	ft_exit(t_cmd *cmd, int ifexit);
char	**ft_export(char **args);
char	**ft_unset(char **args, char **envp);
char	**ft_todir(char **args, int ifcd);

// free
void	ft_free(char **mass);
void	ft_free_list(t_list *a);
void	ft_free_cmd(t_cmd *cmd);

// cmd functions
t_cmd	*ft_cmdnew(void);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmdlast(t_cmd *lst);
int		ft_cmdlen(t_cmd *cmd);

// dict functions
t_dict	*ft_dictnew(char *key, char *value);
void	ft_dictadd_back(t_dict **lst, t_dict *new);
void	ft_free_dict(t_dict *dict);

// list functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

// error management
void	warning(char *msg, int code, int errstd);
void	errmsg(char *s1, char *s2, char *s3, int code);

// for export
char	**new_envp(char **envp);
char	**sort_mass_bubble(char **tmpmass);
char	**mass_quots_after(char **tmpmass);
char	**export_envp(char **envp, char *str, int free);
char	*check_double(char *args, char **envp);
char	**replace_envp_el(char **envp, char *args, char *new);
int		ft_sym_export(char *str);

// for cd
void	validpath(char *args, char *old_path, int ifcd);
int		check_unset(char *args, char **envp);

// minishell
void	minishell(void);

// prepare for execution
void	dollar(void);
void	parser(void);
char	*rm_quotes(void *content);
void	get_cmd(void);
void	execute(t_cmd *cmd);

// utils
int		max(int a, int b);
int		ft_len_eq(char *str);
int		size_mass(char **envp);
void	id_cmd(void);
int		check_first_pipe(void);
int		check_last_pipe(char *str);
int		check_quotes(void);
void	handler(int signum);
void	handler_inside(int sig); // внутри 2
void	init_g_line(void);
void	ififis(t_list	*tmp);
void	count_cmd(t_list *list);

// redirects
void	r_out(t_cmd *cmd);
void	r_in(t_cmd *cmd);

// pipes
void	pipex(t_cmd *cmd);
void	tmp_file(char *delim, t_cmd *cmd);
void	init_child(t_child *child, t_cmd *cmd);
void	wait_child(int n);
void	instd(t_cmd *cmd);
void	collect_variables(void);
void	get_variables(void);

#endif
