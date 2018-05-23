/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:52:21 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/23 13:13:21 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			change_dir_back(char ***env)
{
	char	*value;

	value = get_env("OLDPWD", *env);
	if (!value)
		return ;
	chdir(value);
}

static void			change_dir_home_sign(char **args, char ***env)
{
	char *line;

	if (args[1])
	{
		if (args[1][0] == '~')
		{
			line = ft_strjoin(get_env("HOME", *env), args[1] + 1);
			free(args[1]);
			args[1] = line;
		}
		if (args[2] && args[2][0] == '~')
		{
			line = ft_strjoin(get_env("HOME", *env), args[2] + 1);
			free(args[2]);
			args[2] = line;
		}
	}
}

static void			change_dir_one_arg(char **args, char ***env)
{
	struct stat		mystat;

	if (args[1][0] == '-' && !args[1][1])
		change_dir_back(env);
	else if (stat(args[1], &mystat) == -1)
		ft_fprintf(2, "cd: no such file or directory: %s\n", args[1]);
	else if (!S_ISDIR(mystat.st_mode))
		ft_fprintf(2, "cd: not a directory: %s\n", args[1]);
	else if (access(args[1], X_OK) == -1)
		ft_fprintf(2, "cd: permission denied: %s\n", args[1]);
	else
		chdir(args[1]);
}

static void			change_dir_two_args(char **args, char ***env, char *pwd)
{
	char			*line;
	char			*path;
	struct stat		mystat;
	int				len;

	if ((line = ft_strstr(pwd, args[1])))
	{
		len = ft_strlen(pwd) + ft_strlen(args[2]) - ft_strlen(args[1]) + 1;
		path = (char *)malloc(len);
		ft_strncat(path, pwd, line - pwd);
		ft_strcat(path, args[2]);
		ft_strcat(path, line + ft_strlen(args[1]));
		if (stat(path, &mystat) == -1)
			ft_fprintf(2, "cd: no such file or directory: %s\n", path);
		else if (!S_ISDIR(mystat.st_mode))
			ft_fprintf(2, "cd: not a directory: %s\n", path);
		else
		{
			ft_printf("%s\n", path);
			chdir(path);
		}
	}
	else
		ft_fprintf(2, "cd: string not in pwd: %s\n", args[1]);
	free(path);
}

void				change_dir(char **args, char ***env)
{
	struct stat		mystat;
	char			*oldpwd;
	char			*pwd;
	char			*path;
	char			*line;

	oldpwd = getcwd(0, 0);
	change_dir_home_sign(args, env);
	if (args[1] && args[2] && args[3])
		ft_fprintf(2, "cd: too many arguments\n");
	else if (!args[1])
		chdir(get_env("HOME", *env));
	else if (!args[2])
		change_dir_one_arg(args, env);
	else if (!args[3])
		change_dir_two_args(args, env, pwd);
	pwd = getcwd(0, 0);
	if (ft_strcmp(pwd, oldpwd))
		set_env("OLDPWD", pwd, env);
	set_env("PWD", pwd, env);
	free(oldpwd);
	free(pwd);
}
