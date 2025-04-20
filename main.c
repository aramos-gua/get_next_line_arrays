#include <fcntl.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	int		fd;
	int		fd2;
	char	*line;
	char	*line2;

	fd = open("get_next_line.c", O_RDONLY);
	fd2 = open("get_next_line.c", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);

	}
	while ((line2 = get_next_line(fd2)) != NULL)
	{
		printf("%s", line2);
		free(line2);
	}
	close(fd);
	close(fd2);
	return (0);
}
