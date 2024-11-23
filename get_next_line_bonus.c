#include "get_next_line_bonus.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	len;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
	{
		line[len] = stash[len];
		len++;
	}
	if (stash[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	size_t	start;
	size_t	len;
	char	*new_stash;

	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (!stash[start])
		return (free(stash), NULL);
	start++;
	len = ft_strlen(stash + start);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(stash), NULL);
	len = 0;
	while (stash[start])
		new_stash[len++] = stash[start++];
	new_stash[len] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
