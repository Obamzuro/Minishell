/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 22:22:33 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/18 18:48:26 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*a;
	size_t	i;
	size_t	s1l;

	s1l = ft_strlen(s1);
	i = s1l + ft_strlen(s2) + 1;
	a = ft_strnew(i);
	if (!a)
		return (NULL);
	ft_strcpy(a, s1);
	ft_strcpy(a + s1l, s2);
	return (a);
}
