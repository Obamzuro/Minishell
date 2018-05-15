/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:05:22 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/15 05:49:37 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_pwd(char *line, char ***env)
{
	line = getcwd(0, 0);
	env = 0;
	ft_printf("%s\n", line);
	free(line);
	return (0);
}

int		change_dir(char *line, char ***env)
{
	struct stat		mystat;
	size_t			amargs;
	char			**args;
	char			*pwd;
	char			*path;
	int				yep;

	env = 0;
	amargs = ft_wcount(line, ' ');
	args = ft_strsplit(line, ' ');
	if (amargs > 2)
		ft_printf("cd: too many arguments\n");
	else if (amargs == 1)
	{
		if (lstat(args[0], &mystat) == -1)
			ft_printf("cd: no such file or directory: %s\n", args[0]);
		else if (!S_ISDIR(mystat.st_mode))
			ft_printf("cd: not a directory: %s\n", args[0]);
		else
			chdir(args[0]);
	}
	else if (amargs == 2)
	{
		pwd = getcwd(0, 0);
		if ((line = ft_strstr(pwd, args[0])))
		{
			yep = ft_strlen(pwd) + ft_strlen(args[1]) - ft_strlen(args[0]) + 1;
			path = (char *)malloc(yep);
			ft_strncat(path, pwd, line - pwd);
			ft_strcat(path, args[1]);
			ft_strcat(path, line + ft_strlen(args[0]));
			if (lstat(path, &mystat) == -1)
				ft_printf("cd: no such file or directory: %s\n", path);
			else if (!S_ISDIR(mystat.st_mode))
				ft_printf("cd: not a directory: %s\n", path);
			else
			{
				ft_printf("%s\n", path);
				chdir(path);
			}
		}
		else
			ft_printf("cd: string not in pwd: %s\n", args[0]);
		free(pwd);
	}
	return (0);
}

int		print_env(char *line, char ***env)
{
	int		i;

	i = 0;
	while ((*env)[i])
		ft_printf("%s\n", (*env)[i++]);
	line = 0;
	return (0);
}

int		ft_exec(char *line, char ***env)
{
	pid_t		process;
	char		**argv;

	argv = ft_strsplit(line, ' ');
	process = fork();
	if (process == 0)
	{
		execve(line, argv, *env);
	}
	else if (process > 0)
	{
		wait(0);
	}
	else
	{
		ft_printf("Not a right comm\n");
		return (1);
	}
	return (0);
}

int		set_env(char *line, char ***env)
{
	int		amargs;
	char	**args;
	char	**newenv;
	int		i;

	amargs = ft_wcount(line, ' ');
	args = ft_strsplit(line, ' ');
	i = 0;
	while ((*env)[i])
		++i;
	newenv = (char **)malloc(sizeof(char *) * (i + 3));
	i = 0;
	while((*env)[i])
	{
		newenv[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		++i;
	}
	newenv[i] = ft_strjoin(args[0], args[1]);
	newenv[i + 1] = 0;
	free(*env);
	*env = newenv;
	return (0);
}

int		unset_env(char *line, char ***env)
{
	int		amargs;
	char	**args;
	char	**newenv;
	int		i;
	int		flag;

	amargs = ft_wcount(line, ' ');
	args = ft_strsplit(line, ' ');
	i = 0;
	while ((*env)[i])
		++i;
	newenv = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	flag = 0;
	while((*env)[i])
	{
		if (!flag && strcmp((*env)[i], args[0])  == '=')
		{
			++i;
			flag = 1;
			continue ;
		}
		newenv[i - flag] = ft_strdup((*env)[i]);
		free((*env)[i]);
		++i;
	}
	newenv[i - flag] = 0;
	free(*env);
	*env = newenv;
	return (0);
}

void	fill_commands(t_comm_corr *commands)
{
	commands[0].comm = "pwd";
	commands[0].func = print_pwd;
	commands[1].comm = "cd";
	commands[1].func = change_dir;
	commands[2].comm = "env";
	commands[2].func = print_env;
	commands[3].comm = "setenv";
	commands[3].func = set_env;
	commands[4].comm = "unsetenv";
	commands[4].func = unset_env;
}

char	**fill_env(void)
{
	extern char		**environ;
	char			**env;
	int				count;
	int				i;

	count = 0;
	while (environ[count])
		++count;
	env = (char **)malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
		env[i] = ft_strdup(environ[i]);
	env[i] = 0;
	return (env);
}

int		main(void)
{
	extern char		**environ;
	char	*line;
	int		i;
	char	*temp;
	char	**env;
	t_comm_corr commands[AM_COMMANDS];

	fill_commands(commands);
	env = fill_env();
	while (1)
	{
		ft_printf("$> ");
		get_next_line(0, &line);
		i = -1;
		while (++i < AM_COMMANDS)
		{
			if (!(temp = ft_strchr(line, ' ')))
				temp = ft_strchr(line, 0);
			if (!ft_strncmp(commands[i].comm, line, temp - line))
			{
				commands[i].func(temp + 1, &env);
				break;
			}
		}
		if (i == AM_COMMANDS)
		{
			ft_exec(line, &env);
		}
	}
	return (0);
}
