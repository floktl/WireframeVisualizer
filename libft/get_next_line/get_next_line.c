/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:40:04 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/26 13:16:20 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_count_new_line(char **buf)
{
	int	i;

	i = 1;
	while ((*buf)[i - 1] != '\n' && (*buf)[i - 1] != '\0' && **buf)
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	counter;
	char	*char_s;

	counter = 0;
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	char_s = (char *)str;
	while (counter < (count * size))
	{
		char_s[counter] = 0;
		counter++;
	}
	return (str);
}

int	read_buf(int fd, char **buf, int *end)
{
	int		read_bytes;
	char	*new_buf;

	new_buf = NULL;
	read_bytes = 1;
	while (read_bytes > 0 || *buf == NULL)
	{
		if (*end != 0)
		{
			new_buf = double_bufsize_fill_with_null(*buf);
			free(*buf);
			if (new_buf == NULL)
				return (-1);
			*buf = new_buf;
		}
		read_bytes = read(fd, *buf + *end, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-1);
		*end += read_bytes;
		(*buf)[*end] = '\0';
		if (ft_check_if_newline(*buf))
			break ;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	static int	i = 0;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buf);
		i = 0;
		return (buf = NULL, NULL);
	}
	if (!buf)
		buf = ft_calloc(BUFFER_SIZE, 1);
	if (!buf)
		return (NULL);
	if (read_buf(fd, &buf, &i) == -1 || extract_line(&line, &buf, &i) == NULL)
	{
		free(buf);
		buf = NULL;
		i = 0;
		return (NULL);
	}
	free(buf);
	buf = NULL;
	return (line);
}
