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

void	divide(char	*buffer, char **line_to_return)
{
	char	*line_ptr;
	char	*temp;
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
		*line_to_return = gnl_strjoin(*line_to_return, temp);
	else
	{
		*line_to_return = temp;
		temp = NULL;
	}
	free(temp);
	ft_memmove(buffer, line_ptr + 1, leftover_len);
	buffer[leftover_len] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line_to_return;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_to_return = NULL;
	bytes = 1;
	if (ft_strlen(buffer, '\0') > 0)
	{
		if (ft_strchr(buffer, '\n'))
			return (divide(buffer, &line_to_return), line_to_return);
		else
			line_to_return = gnl_strjoin(line_to_return, buffer);
	}
	while (!(ft_strchr(buffer, '\n') && bytes > 0))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		if (ft_strchr(buffer, '\n'))
		{
			divide(buffer, &line_to_return);
			break ;
		}
		if ((bytes == 0 || bytes < BUFFER_SIZE) && !ft_strchr(buffer, '\n'))
		{
			line_to_return = gnl_strjoin(line_to_return, buffer);
			break ;
		}
		if (!(ft_strchr(buffer, '\n')))
			line_to_return = gnl_strjoin(line_to_return, buffer);
	}
	if (!line_to_return || line_to_return[0] == '\0')
		return (free(line_to_return), NULL);
	return (line_to_return);
}

//int	main(void)
//{
//	int		fd;
//	char	*line;
//
//	fd = open("a.txt", O_RDONLY);
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	close(fd);
//	return (0);
//}
