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
	void	*ptr;
	size_t		i;

	i = 0;
	if (n == 0)
		return (dest);
	ptr = dest;
	if (src < dest && dest <= src + (n - 1))
	{
		while (n-- > 0)
			*((unsigned char *)dest + n) = *((unsigned const char *)src + n);
	}
	else
		while (i++ < n)
		*(unsigned char *)dest++ = *(unsigned const char *)src++;
	return (ptr);
}

void	divide(char	*buffer, char *leftover, char **line_to_return)
{
	char	*line_ptr;
	size_t	line_len;
	size_t	leftover_len;

	line_ptr = ft_strchr(buffer, '\n');
	if (!line_ptr)
		return ;
	line_len = ft_strlen(buffer, '\n') + 1;
	leftover_len = ft_strlen(buffer, '\0') - line_len;
	*line_to_return = ft_substr(buffer, 0, line_len);
	leftover = ft_memmove(buffer, line_ptr + 1, leftover_len);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		buffer[BUFFER_SIZE + 1];
	char		*line_to_return;
	int			bytes_read;
	
	line_to_return = NULL;
	if (ft_strlen(leftover, '\0') > 0)
	{
		//printf("Beginning of if\n");
		ft_memmove(buffer, leftover, ft_strlen(leftover, '\0'));
		bytes_read = read(fd, buffer + ft_strlen(leftover, '\0'), BUFFER_SIZE);
		//printf("End of if\n");
	}
	else
	{
		//printf("Beginning of else\n");
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//printf("Enf of else\n");
	}
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (ft_strchr(buffer, '\n'))
		divide(buffer, leftover, &line_to_return);
	else
		line_to_return = ft_substr(buffer, 0, bytes_read);
	return (line_to_return);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
