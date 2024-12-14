#include "get_next_line.h"

char *read_until_line_end(int fd, char *line)
{
    char *buffer;
    ssize_t read_bytes;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    read_bytes = 1;
    while (!ft_strchr(line, '\n') && read_bytes > 0)
    {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[read_bytes] = '\0';
        line = ft_strjoin(line, buffer);
    }
    free(buffer);
    return (line);
}

char *extract_line(char *str)
{
    char *line;
    size_t length;

	if(!str || !*str)
		return (NULL);
    length = 0;
    while (str[length] != '\0' && str[length] != '\n')
        length++;
    line = malloc(length + 2);
    if (!line)
        return (NULL);
    length = 0;
    while (str[length] != '\0' && str[length] != '\n')
    {
        line[length] = str[length];
        length++;
    }
    if (str[length] == '\n')
    {
        line[length] = '\n';
        length++;
    }
    line[length] = '\0';
    return (line);
}

char *trim_line_after_newline(char *str)
{
    size_t index = 0;
    size_t len = 0;
    char *new_str;

    while (str[index] && str[index] != '\n')
        index++;
    if (str[index] == '\0')
    {
        free(str);
        return NULL;
    }
    len = ft_strlen(str + index + 1);
    new_str = malloc(len + 1);
    if (!new_str)
    {
        free(str);
        return NULL;
    }
    index++;
    len = 0;
    while (str[index])
        new_str[len++] = str[index++];
    new_str[len] = '\0';
    free(str);
    return new_str;
}

char *get_next_line(int fd)
{
    static char *line;
    char *result;

    line = read_until_line_end(fd, line);
    if (!line)
        return NULL;
    result = extract_line(line);
    line = trim_line_after_newline(line); 
    return (result);
}

int main()
{
	int fd;
	char *line;

	fd = open("a.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}