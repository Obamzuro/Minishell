/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 14:48:42 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/19 13:32:24 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_gnl(int s1l, const char *s1, int s2l, const char *s2)
{
	char	*a;
	char	*b;
	size_t	i;

	i = s1l + s2l + 1;
	a = (char *)malloc(sizeof(char) * i);
	b = a;
	if (!a)
		return (NULL);
	if (s1)
		b = ft_strcpy_gnl(b, s1);
	if (s2)
		b = ft_strcpy_gnl(b, s2);
	return (a);
}

static int	read_line(const int fd, t_gnl_list *nd, char **line, int linelen)
{
	int		ret;
	char	*dop[2];

	while ((ret = read(fd, nd->buf, BUFF_SIZE)) > 0)
	{
		if ((dop[0] = ft_strchr(nd->buf, '\n')))
		{
			*dop[0] = 0;
			SMARTCHECK(dop[1] = ft_strjoin_gnl(linelen, *line,
						dop[0] - nd->buf, nd->buf));
			free(*line);
			*line = dop[1];
			nd->last = dop[0] - nd->buf + 1;
			return (1);
		}
		SMARTCHECK(dop[1] = ft_strjoin_gnl(linelen, *line, ret, nd->buf));
		free(*line);
		*line = dop[1];
		ft_memset(nd->buf, 0, BUFF_SIZE);
		linelen += ret;
	}
	if (ret == -1)
		return (-1);
	return (*line ? 1 : 0);
}

static int	handle_not_fd(const int fd, t_gnl_list *back, char **line)
{
	back->fd = fd;
	back->last = 0;
	ft_memset(back->buf, 0, BUFF_SIZE + 1);
	back->next = 0;
	return (read_line(fd, back, line, 0));
}

int			get_next_line(const int fd, char **line)
{
	static t_gnl_list	*head;
	int					ret;

	head = 0;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	*line = 0;
	if (!head)
	{
		SMARTCHECK(head = (t_gnl_list *)malloc(sizeof(t_gnl_list)));
		ret = handle_not_fd(fd, head, line);
		free(head);
		return (ret);
	}
	return (-1);
}
