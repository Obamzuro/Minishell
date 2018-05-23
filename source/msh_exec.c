/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:52:33 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/23 14:44:20 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_exec_path_find_comm(char **args, char ***env, char **paths)
{
	int			i;
	struct stat	mystat;
	char		*temp;

	while (paths[i])
	{
		temp = ft_strjoin_char(paths[i], args[0], '/');
		if (lstat(temp, &mystat) != -1)
		{
			if (access(temp, X_OK) == -1)
			{
				ft_fprintf(2, "minishell: Permission denied: %s\n", args[0]);
				free(temp);
				return (0);
			}
			else
				return (temp);
		}
		free(temp);
		++i;
	}
	ft_fprintf(2, "minishell: command not found: %s\n", args[0]);
	return (0);
}

static char		*ft_exec_path(char **args, char ***env)
{
	char		**paths;
	int			i;
	struct stat	mystat;
	char		*ret;

	paths = ft_strsplit(get_env("PATH", *env), ':');
	i = 0;
	if (!paths)
	{
		ft_fprintf(2, "minishell: command not found: %s\n", args[0]);
		return (0);
	}
	ret = ft_exec_path_find_comm(args, env, paths);
	free_double_arr(paths);
	return (ret);
}

static int		ft_exec_check_err(char **args, char ***env, char *comm)
{
	struct stat	tempstat;

	if (!comm)
		return (0);
	if (lstat(comm, &tempstat) == -1)
	{
		ft_fprintf(2, "minishell: no such file or directory: %s\n", comm);
		if (comm != args[0])
			free(comm);
		return (0);
	}
	if (!S_ISREG(tempstat.st_mode) || access(comm, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: Permission denied: %s\n", comm);
		if (comm != args[0])
			free(comm);
		return (0);
	}
	return (1);
}

static int		ft_exec_fork(char **args, char ***env, char *comm)
{
	pid_t		process;
	struct stat	tempstat;

	process = fork();
	if (process == 0)
	{
		if (execve(comm, args, *env) == -1)
		{
			ft_fprintf(2, "minishell: File execution error: %s\n", comm);
			exit(EXIT_FAILURE);
		}
	}
	else if (process > 0)
	{
		wait(0);
	}
	else
	{
		ft_fprintf(2, "Can't create a child thread\n");
		return (1);
	}
	return (0);
}

void			ft_exec(char **args, char ***env)
{
	char		*comm;
	char		*temp;
	int			ret;

	if (!ft_strchr(args[0], '/'))
		comm = ft_exec_path(args, env);
	else
	{
		if (args[0] && args[0][0] == '~')
		{
			temp = ft_strjoin(get_env("HOME", *env), args[0] + 1);
			free(args[0]);
			args[0] = temp;
		}
		comm = args[0];
	}
	if (!ft_exec_check_err(args, env, comm))
		return ;
	ret = ft_exec_fork(args, env, comm);
	if (comm != args[0])
		free(comm);
	return ;
}
