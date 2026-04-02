//rado soln -buggy (you never read more than 1 character per call, so you don’t build a full line.)
#include "gnl.h"

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos = 0;
	static int buffer_read = 0;
	int i = 0;
	int line_size = 10000;
	char *line = NULL;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(line_size);
	if (!line)		
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			if (buffer_read < 0)
				return (free(line), NULL);
			buffer_pos = 0;
			if (buffer_read == 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
		line[i] = '\0';
		if (i == 0)
			return (free(line), NULL);
		return (line);
	}
