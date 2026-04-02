//sup soln- didnt clear by tester
#include "gnl.h"

// Helper: Standard string length
size_t ft_strlen(const char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return (i);
}

// Helper: Standard strchr with null-check
char *ft_strchr(const char *s, int c)
{
    while (s && *s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

// Helper: Copy memory safely
void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if (!dest && !src)
        return (NULL);
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

// Fixed: Correctly handles pointer to pointer to reallocate memory(similar to strjoin but for memory blocks)
int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *temp = malloc(size1 + size2 + 1);
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

char *get_next_line(int fd)
{  
    static char b[BUFFER_SIZE + 1] = {0};
    char *line = NULL;// remaining line in buffer or line being built
    char *temp; // stores position of newline in buffer
    int bytes_read= 1;//read counter

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    while (1)
    {
        // Check if there's already a newline in our static buffer
        temp = ft_strchr(b, '\n');
        if (temp)
        {
            // We found a newline! Append everything up to and including the newline to our return string
            if (!str_append_mem(&line, b, (temp - b) + 1))
            {
                free(line);
                return (NULL);
            }
            // Shift the remaining data to the start of the buffer
            ft_memcpy(b, temp + 1, ft_strlen(temp + 1) + 1);
            // Return the line we've built with the newline
            return (line);
        }
        
        // No newline found? Append the whole buffer and read more
        if (b[0] != '\0')
        {
            if (!str_append_mem(&line, b, ft_strlen(b)))
            {
                free(line);
                return (NULL); 
            }
        }
        bytes_read = read(fd, b, BUFFER_SIZE);
        if (bytes_read <= 0) // Error or EOF
        {
            b[0] = '\0'; // Clear buffer on end
            if (bytes_read == 0 && line && *line)
                return (line);
            free(line);
            return (NULL); // Return what we have (if any)
        }
        b[bytes_read] = '\0';
    }
}

