/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:11:13 by ykarakur          #+#    #+#             */
/*   Updated: 2024/04/03 12:11:17 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static inline void	*ft_free_stash(char **stash, int create_line)
{
	char	*line;

	if (*stash && !create_line)
		return (free(*stash), *stash = NULL);
	else if (*stash && create_line)
		return (line = ft_strdup(*stash), free(*stash), *stash = NULL, line);
	return (NULL);
}

static inline char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!stash)
		return (NULL);
	i = ft_strchr(stash, '\n') - stash;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i + 1)
		line[j] = stash[j];
	return (line[j] = '\0', line);
}

static inline char	*ft_recreate_stash(char *stash)
{
	char	*res;

	if (!stash)
		return (NULL);
	if (!*(ft_strchr(stash, '\n') + 1))
		return (ft_free_stash(&stash, 0));
	res = ft_strdup(ft_strchr(stash, '\n') + 1);
	return (ft_free_stash(&stash, 0), res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char	*stash = NULL;
	char		*line;
	char		*res;

	ret = BUFFER_SIZE;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret == 0 && !stash) || ret == -1)
			return (ft_free_stash(&stash, 0));
		buf[ret] = '\0';
		res = ft_strjoin(stash, buf);
		ft_free_stash(&stash, 0);
		stash = res;
		if (ft_strchr(stash, '\n'))
		{
			line = ft_extract_line(stash);
			if (!line)
				return (ft_free_stash(&stash, 0));
			return (stash = ft_recreate_stash(stash), line);
		}
	}
	return (ft_free_stash(&stash, 1));
}
