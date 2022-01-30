/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:31:36 by tbesson           #+#    #+#             */
/*   Updated: 2022/01/28 18:57:40 by tbesson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*s[127];

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 127)
		return (NULL);
	s[fd] = ft_read(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	l = ft_getline(s[fd]);
	s[fd] = ft_new_static(s[fd]);
	return (l);
}
