/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:05:22 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/16 14:01:13 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_pwd(char **args, char ***env)
{
	char	*line;

	if (args[1])
	{
		ft_printf("pwd: too many arguments");
		return (1);
	}
	line = getcwd(0, 0);
	env = 0;
	ft_printf("%s\n", line);
	free(line);
	return (0);
}

char	*get_env(char *key, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], key) == '=')
			return (env[i] + ft_strlen(key) + 1);
		++i;
	}
	return (0);
}

int		set_env_inner(char *key, char *value, char ***env)
{
	int i;
	char	**newenv;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strcmp((*env)[i], key) == '=')
		{
			free((*env)[i]);
			(*env)[i] = (char *)malloc(ft_strlen(key) + ft_strlen(value) + 2);
			(*env)[i] = msh_strjoin_char(key, value, '=');
			return (0);
		}
		++i;
	}
	i = 0;
	while ((*env)[i])
		++i;
	newenv = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while((*env)[i])
	{
		newenv[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		++i;
	}
	newenv[i] = msh_strjoin_char(key, value, '=');
	newenv[i + 1] = 0;
	free(*env);
	*env = newenv;
	return (0);
}

int		set_env(char **args, char ***env)
{
	//amargs = ft_wcount(line, ' ');
	//args = ft_strsplit(line, ' ');
	if (args[1] == 0 || args[2] == 0)
	{
		ft_printf("setenv: not enough arguments");
		return (1);
	}
	else if (args[3] != 0)
	{
		ft_printf("setenv: too many arguments");
		return (1);
	}
	set_env_inner(args[1], args[2], env);
	return (0);
}

int		unset_env(char **args, char ***env)
{
//	char	**args;
	char	**newenv;
	int		i;
	int		flag;

//	amargs = ft_wcount(line, ' ');
//	args = ft_strsplit(line, ' ');
	if (!get_env(args[1], *env))
		return (1);
	i = 0;
	while ((*env)[i])
		++i;
	newenv = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	flag = 0;
	while((*env)[i])
	{
		if (!flag && strcmp((*env)[i], args[1])  == '=')
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


int		change_dir_back(char ***env)
{
	char	*value;

	value = get_env("OLDPWD", *env);
	if (!value)
		return (1);
	//FIXME
	//chdir == 0
	chdir(value);
	return (0);
}

int		change_dir(char **args, char ***env)
{
	struct stat		mystat;
//	size_t			amargs;
//	char			**args;
	char			*pwd;
	char			*path;
	int				yep;
	char			*line;

//	amargs = ft_wcount(line, ' ');
//	args = ft_strsplit(line, ' ');
	pwd = getcwd(0, 0);
	if (args[1] && args[2] && args[3])
		ft_printf("cd: too many arguments\n");
	else if (!args[1])
		chdir(get_env("HOME", *env));
	else if (!args[2])
	{
		if (args[1][0] == '-' && !args[1][1])
			change_dir_back(env);
		else if (lstat(args[1], &mystat) == -1)
			ft_printf("cd: no such file or directory: %s\n", args[1]);
		else if (!S_ISDIR(mystat.st_mode))
			ft_printf("cd: not a directory: %s\n", args[1]);
		else
			chdir(args[1]);
	}
	else if (!args[3])
	{
		if ((line = ft_strstr(pwd, args[1])))
		{
			yep = ft_strlen(pwd) + ft_strlen(args[2]) - ft_strlen(args[1]) + 1;
			path = (char *)malloc(yep);
			ft_strncat(path, pwd, line - pwd);
			ft_strcat(path, args[2]);
			ft_strcat(path, line + ft_strlen(args[1]));
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
			ft_printf("cd: string not in pwd: %s\n", args[1]);
	}
	set_env_inner("OLDPWD", pwd, env);
	free(pwd);
	return (0);
}

int		print_env(char **args, char ***env)
{
	int		i;

	i = 0;
	while ((*env)[i])
		ft_printf("%s\n", (*env)[i++]);
	i = args + 1 - args;
	return (0);
}

char	*ft_exec_path(char **args, char ***env)
{
	char	**paths;
	int		i;
	char	*temp;

	paths = ft_strsplit(get_env("PATH", *env), ':');
	i = 0;
	while (paths[i])
	{
		temp = msh_strjoin_char(paths[i], args[0], '/');
		if (!access(temp, X_OK))
			return (temp);
		free(temp);
		++i;
	}
	return (0);
}

void	int_handler(int sig)
{
	signal(sig, SIG_IGN);
	kill(g_child, SIGINT);
	ft_printf("HERE\n");
}

int		ft_exec(char **args, char ***env)
{
	pid_t		process;
	char		*comm;

	if (!ft_strchr(args[0], '/'))
		comm = ft_exec_path(args, env);
	else
		comm = args[0];
	process = fork();
	if (process == 0)
	{
		if (execve(comm, args, *env) == -1)
			ft_printf("Not a right comm\n");
	}
	else if (process > 0)
	{
		wait(0);
	}
	else
	{
		ft_printf("Can't create a child thread\n");
		return (1);
	}
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
	char	**args;
	char	*line;
	int		i;
	char	**env;
	int		a;
	t_comm_corr commands[AM_COMMANDS];
	extern char		**environ;

	signal(SIGINT, int_handler);
	signal(SIGSTOP, int_handler);
	fill_commands(commands);
	env = fill_env();
	while (1)
	{
		ft_printf("$> ");
		if ((a = get_next_line(0, &line)) == -1)
		{
			ft_printf("123\n");
			continue;
		}
		args = ft_strsplit(line, ' ');
		i = -1;
		while (++i < AM_COMMANDS)
		{
//			if (!(temp = ft_strchr(line, ' ')))
//				temp = ft_strchr(line, 0);
			if (!ft_strncmp(commands[i].comm, args[0], ft_strlen(commands[i].comm)))
			{
				commands[i].func(args, &env);
				break;
			}
		}
		if (i == AM_COMMANDS)
		{
			ft_exec(args, &env);
		}
	}
	return (0);
}
