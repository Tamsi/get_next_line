/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:33:16 by tbesson           #+#    #+#             */
/*   Updated: 2022/01/27 16:00:08 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	tmp = ft_substr(s, 0, i + 1);
	return (tmp);
}

char	*ft_read(int fd, char *s)
{
	char	*buf;
	int		ret;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	ret = 1;
	while (!ft_strchr(s, '\n') && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	return (s);
}

char	*ft_new_static(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	tmp = ft_substr(s, i + 1, ft_strlen(s));
	free(s);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*l;
	static char	*s;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	s = ft_read(fd, s);
	if (!s)
		return (NULL);
	l = ft_getline(s);
	s = ft_new_static(s);
	return (l);
}
