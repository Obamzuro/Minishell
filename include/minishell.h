/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 15:06:10 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/18 13:26:16 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H
# define AM_COMMANDS 7
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct	s_comm_corr
{
	char	*comm;
	int		(*func)(char **, char ***);
}				t_comm_corr;

pid_t			g_child;

volatile sig_atomic_t	g_sigint;

char			*msh_strjoin_char(const char *s1, const char *s2, char c);
char			*msh_strjoin_path(const char *s1, const char *s2);
#endif
