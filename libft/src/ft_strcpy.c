/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:24:09 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/18 18:48:52 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char *dstc;

	if (!dst || !src)
		return (0);
	dstc = dst;
	while (*src)
		*dstc++ = *src++;
	*dstc = *src;
	return (dst);
}
