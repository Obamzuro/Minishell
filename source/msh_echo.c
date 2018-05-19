/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:52:29 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/19 13:52:30 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_echo(char **args, char ***env)
{
	int		i;
	int		first;

	i = 1;
	first = 0;
	while (args[i])
	{
		if (!first)
		{
			ft_printf("%s", args[i]);
			first = 1;
		}
		else
			ft_printf(" %s", args[i]);
		++i;
	}
	ft_printf("\n");
	return (0);
}
