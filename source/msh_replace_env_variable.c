/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_replace_env_variable.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:24:29 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/23 12:26:52 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			replace_env_variable_join(int counter, char **str,
		char **strsplitted, char **env)
{
	char	*temp;

	if (counter == 0)
	{
		free(*str);
		if ((*str)[0] != '$')
		{
			*str = ft_strdup(strsplitted[0]);
			return ;
		}
		else
			*str = 0;
	}
	temp = *str;
	*str = ft_strjoin(temp, get_env(strsplitted[counter], env));
	free(temp);
	return ;
}

int					replace_env_variable(char **args, char **env)
{
	int		i;
	int		j;
	char	*temp;
	char	end;
	char	**strsplitted;

	i = 0;
	while (args[++i])
	{
		strsplitted = ft_strsplit(args[i], '$');
		end = *(ft_eol(args[i]));
		j = -1;
		while (strsplitted[++j])
			replace_env_variable_join(j, &args[i], strsplitted, env);
		if (end == '$')
		{
			temp = args[i];
			args[i] = ft_strjoin(args[i], "$");
			free(temp);
		}
		free_double_arr(strsplitted);
	}
	return (0);
}
