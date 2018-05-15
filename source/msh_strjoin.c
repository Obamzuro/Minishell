/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 09:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/15 09:39:18 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_strjoin_char(const char *s1, const char *s2, char c)
{
	char	*a;
	size_t	i;
	size_t	s1l;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	i = s1l + ft_strlen(s2) + 2;
	a = ft_strnew(i);
	if (!a)
		return (NULL);
	ft_strcpy(a, s1);
	a[s1l] = c;
	ft_strcpy(a + s1l + 1, s2);
	return (a);
}
