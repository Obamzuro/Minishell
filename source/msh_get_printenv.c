/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_get_printenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:52:51 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/19 13:52:51 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env(char *key, char **env)
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

int			print_env(char **args, char ***env)
{
	int		i;

	i = 0;
	while ((*env)[i])
		ft_printf("%s\n", (*env)[i++]);
	i = args + 1 - args;
	return (0);
}
