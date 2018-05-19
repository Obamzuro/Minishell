/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_print_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:52:58 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/19 13:52:58 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_pwd(char **args, char ***env)
{
	char	*line;

	if (args[1])
	{
		ft_printf("pwd: too many arguments\n");
		return (1);
	}
	line = getcwd(0, 0);
	env = 0;
	ft_printf("%s\n", line);
	free(line);
	return (0);
}
