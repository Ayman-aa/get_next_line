#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (c == '\0' ? (char *)s : NULL);
}


char    *ft_strjoin(char *line, char *buff)
{
    size_t    i;
    size_t    j;
    char    *str;

    if (!line)
    {
        line = (char *)malloc(1 * sizeof(char));
        line[0] = '\0';
    }
    if (!line || !buff)
        return (NULL);
    str = malloc(sizeof(char) * ((ft_strlen(line) + ft_strlen(buff)) + 1));
    if (str == NULL)
        return (NULL);
    i = -1;
    j = 0;
    if (line)
        while (line[++i] != '\0')
            str[i] = line[i];
    while (buff[j] != '\0')
        str[i++] = buff[j++];
    str[ft_strlen(line) + ft_strlen(buff)] = '\0';
    free(line);
    return (str);
}