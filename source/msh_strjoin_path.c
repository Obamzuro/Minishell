/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strjoin_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 10:11:50 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/17 10:12:11 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_strjoin_path(const char *s1, const char *s2)
{
	char	*a;
	size_t	i;
	size_t	s1l;
	char	needslash;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	needslash = 1;
	if (s1[s1l - 1] == '/')
		needslash = 0;
	i = s1l + ft_strlen(s2) + 1 + needslash;
	a = ft_strnew(i);
	if (!a)
		return (NULL);
	ft_strcpy(a, s1);
	if (needslash)
		a[s1l] = '/';
	ft_strcpy(a + s1l + needslash, s2);
	return (a);
}
