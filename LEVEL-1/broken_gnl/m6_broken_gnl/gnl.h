#ifndef GNL_H
# define GNL_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# include <stdlib.h>
# include <unistd.h>

char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
void *ft_memcpy(void *dest, const void *src, size_t n);
int str_append_mem(char **s1, char *s2, size_t size2);

#endif