//tudor soln
#include "get_next_line.h"

char	*ft_strchr(char *s, char c)
{
	int	i = 0;
	if (!s)
		return NULL;
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (c == '\0')
		return (s + i);
	return NULL;
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

size_t ft_strlen(char *s)
{
	size_t	ret = 0;

	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int	str_app_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = *s1 ? ft_strlen(*s1) : 0;
	char *temp;

	if (!s1 || !s2)
		return (0);
	temp = (char *)malloc(size1 + size2 + 1);
	if (!temp)
		return (0);
	if (*s1)
		ft_memcpy(temp, *s1, size1);
	ft_memcpy(temp + size1, s2, size2);
	temp[size1 + size2] = '\0';
	free(*s1);
	*s1 = temp;
	return (1);
}

int	str_app_str(char **s1, char *s2)
{
	return (str_app_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, void *src, size_t n)
{
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	size_t	i = n;
	while (i > 0)
	{
		i--;
		((char *)dest)[i] = ((char *)src)[i];
	}
	return (dest);
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *res = malloc(1);
	char *temp;
	ssize_t b_read;

	if (fd < 0 || !res)
		return(free(res), NULL);
	res[0] = 0;
	while (1)
	{
		temp = ft_strchr(b, '\n');
		if (temp)
		{
			if (!str_app_mem(&res, b, temp - b + 1))
				return (free(res), NULL);
			ft_memmove(b, temp + 1, ft_strlen(temp + 1) + 1);
			return (res);
		}
		if (ft_strlen(b) > 0)
		{
			if (!str_app_str(&res, b))
				return (free(res), NULL);
			b[0] = 0;
		}
		b_read = read(fd, b, BUFFER_SIZE);
		if (b_read == -1)
			return (free(res), NULL);
		if (b_read == 0)
		{
			if (ft_strlen(res) == 0)
				return (free(res), NULL);
			return (res);
		}
		b[b_read] = '\0';
	}
}

// int main(void)
// {
// 	int fd = open("test_no_newline.txt", O_RDONLY);
// 	char *line;
// 	if (fd == -1)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }
