#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "gnl.h" // Or include your header if you have one

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     line_count;

    line_count = 1;
    // If a filename is provided, open it. Otherwise, read from stdin (fd 0)
    if (argc == 2)
        fd = open(argv[1], O_RDONLY);
    else
        fd = 0;

    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    printf("--- Starting GNL Test ---\n");

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line [%02d]: %s", line_count++, line);
        
        // Safety: If the line doesn't end in \n, add one for display clarity
        if (line[strlen(line) - 1] != '\n')
            printf("\n");//[EOF reached - no newline]
        
        free(line); // Critical: Avoid memory leaks!
    }

    printf("\n--- End of File ---\n");
    
    if (fd != 0)
        close(fd);
    return (0);
}

