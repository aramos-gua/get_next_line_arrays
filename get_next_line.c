/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:32:26 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/04/15 22:49:24 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;
	size_t				i;

	if (!dest || !src || dest == src || n == 0)
		return (dest);
	destination = (unsigned char *)dest;
	source = (const unsigned char *)src;
	i = 0;
	if (source < destination && destination <= source + (n - 1))
	{
		while (n-- > 0)
			destination[n] = source[n];
	}
	else
	{
		while (i < n)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (dest);
}

void	divide(char	*buffer, char **line_to_return)
{
	char	*line_ptr;
	char	*temp;
	char	*joined;
	size_t	line_len;
	size_t	leftover_len;

	line_ptr = ft_strchr(buffer, '\n');
	if (!line_ptr)
		return ;
	line_len = ft_strlen(buffer, '\n') + 1;
	leftover_len = ft_strlen(buffer, '\0') - line_len;
	temp = ft_substr(buffer, 0, line_len);
	if (!temp)
		return ;
	if (*line_to_return)
	{
		joined = gnl_strjoin(*line_to_return, temp);
		*line_to_return = joined;
	}
	else
	{
		*line_to_return = temp;
		temp = NULL;
	}
	free(temp);
	ft_memmove(buffer, line_ptr + 1, leftover_len);
	buffer[leftover_len] = '\0';
}

static void	pass_buffer_data(char *buffer, char **line_to_return)
{
	*line_to_return = gnl_strjoin(*line_to_return, buffer);
	buffer[0] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line_to_return;
	int			bytes_read;
	
	line_to_return = NULL;
	bytes_read = 1;
	if (ft_strlen(buffer, '\0') > 0)
	{
		if (ft_strchr(buffer, '\n'))
			return(divide(buffer, &line_to_return), line_to_return);
		else
			pass_buffer_data(buffer, &line_to_return);
	}
	while (!(ft_strchr(buffer, '\n') && bytes_read > 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((bytes_read == 0 || bytes_read < BUFFER_SIZE) && !ft_strchr(buffer, '\n'))
		{
			pass_buffer_data(buffer, &line_to_return);
			break ;
		}
		if (ft_strchr(buffer, '\n'))
		{
			divide(buffer, &line_to_return);
			break ;
		}
		else
			pass_buffer_data(buffer, &line_to_return);
	}
	if (!line_to_return)
		return (NULL);
	return (line_to_return);
}

int	main(void)
{
	int		fd;
	char	*line;
	int	n = 6;

	fd = open("a.txt", O_RDONLY);
	while (n -- > 0)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
