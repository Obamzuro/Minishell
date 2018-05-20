/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:05:22 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/20 19:33:58 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		replace_env_variable(char **args, char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '$')
			{
				args[i][j] = 0;
				temp = args[i];
				args[i] = ft_strjoin(args[i], get_env(args[i] + j + 1, env));
				free(temp);
				break ;
			}
		}
	}
}

static void		handle_commands(char *line, t_comm_corr commands[AM_COMMANDS],
		char ***env)
{
	int		i;
	char	**args;

	args = ft_strsplit2(line, " \t");
	if (!args[0])
	{
//		free(args);
		return ;
	}
	replace_env_variable(args, *env);
	i = -1;
	while (++i < AM_COMMANDS)
	{
		if (!ft_strncmp(commands[i].comm, args[0],
					ft_strlen(commands[i].comm) + 1))
		{
			commands[i].func(args, env);
			break ;
		}
	}
	if (i == AM_COMMANDS)
		ft_exec(args, env);
	free_args(args);
}

int				main(void)
{
	char		*line;
	int			i;
	char		**env;
	t_comm_corr	commands[AM_COMMANDS];
	char		**args;

	g_sigint = 0;
	signal(SIGINT, int_handler);
	fill_commands(commands);
	env = fill_env();
	while (1)
	{
		ft_printf("$> ");
		g_sigint = 0;
		get_next_line(0, &line);
		g_sigint = 1;
		args = ft_strsplit(line, ';');
		i = -1;
		while (args[++i])
			handle_commands(args[i], commands, &env);
		free_args(args);
		free(line);
	}
	free_args(env);
	return (0);
}
