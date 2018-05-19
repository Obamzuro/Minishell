/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:53:02 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/19 14:15:33 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			set_env_check_existing(char *key, char *value, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], key) == '=')
		{
			free(env[i]);
			env[i] = msh_strjoin_char(key, value, '=');
			return (1);
		}
		++i;
	}
	return (0);
}

int					set_env(char *key, char *value, char ***env)
{
	int		i;
	char	**newenv;

	if (set_env_check_existing(key, value, *env))
		return (0);
	i = 0;
	while ((*env)[i])
		++i;
	newenv = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
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

int					set_env_comm(char **args, char ***env)
{
	if (args[1] == 0 || args[2] == 0)
	{
		ft_printf("setenv: not enough arguments\n");
		return (1);
	}
	else if (args[3] != 0)
	{
		ft_printf("setenv: too many arguments\n");
		return (1);
	}
	set_env(args[1], args[2], env);
	return (0);
}
