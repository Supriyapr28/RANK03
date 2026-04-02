// Streaming implementation of the filter subject without malloc

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 2 || av[1][0] == '\0')
        return (1);

    char   *pat = av[1];
    size_t plen = strlen(pat);
    if (plen == 0)
        return (1);

    char   window[plen + 1];
    size_t wlen = 0;
    char   c;
    ssize_t n;

    while ((n = read(0, &c, 1)) > 0)
    {
        window[wlen++] = c;
        if (wlen == plen)
        {
            size_t k = 0;
            while (k < plen && window[k] == pat[k])
                k++;
            if (k == plen)
            {
                for (size_t j = 0; j < plen; ++j)
                    printf("*");
                wlen = 0;
            }
            else
            {
                printf("%c", window[0]);
                for (size_t i = 1; i < wlen; ++i)
                    window[i - 1] = window[i];
                wlen--;
            }
        }
    }
    if (n < 0)
    {
        perror("Error: ");
        return (1);
    }
    for (size_t i = 0; i < wlen; ++i)
        printf("%c", window[i]);
    return (0);
}

