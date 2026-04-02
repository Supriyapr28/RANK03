#include <unistd.h>

int  ft_strlen(char *s)
{
    int len = 0;
    while (s[len])
        len++;
    return len;
}

void find_removals(char *s, int *rem_open, int *rem_close)
{
    int i = 0;
    *rem_open = 0;
    *rem_close = 0;
    while (s[i])
    {
        if (s[i] == '(')
            (*rem_open)++;
        else if (s[i] == ')')
        {
            if (rem_open > 0)
                (*rem_open)--;
            else
                (*rem_close)++;
        }
        i++;
    }
}

void backtrack(char *in, char *out, int pos, int len,
                      int open_count, int rem_open, int rem_close)
{
    if (pos == len)
    {
        if (open_count == 0 && rem_open == 0 && rem_close == 0)
        {
            write(1, out, len);
            write(1, "\n", 1);
        }
        return;
    }
    if (in[pos] == '(')
    {
        if (rem_open > 0)
        {
            out[pos] = ' ';
            backtrack(in, out, pos + 1, len, open_count, rem_open - 1, rem_close);
        }
        out[pos] = '(';
        backtrack(in, out, pos + 1, len, open_count + 1, rem_open, rem_close);
    }
    else if (in[pos] == ')')
    {
        if (rem_close > 0)
        {
            out[pos] = ' ';
            backtrack(in, out, pos + 1, len, open_count, rem_open, rem_close - 1);
        }
        if (open_count > 0)
        {
            out[pos] = ')';
            backtrack(in, out, pos + 1, len, open_count - 1, rem_open, rem_close);
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    int   len = ft_strlen(av[1]);
    if (len == 0)
        return 0;
    int rem_open, rem_close;
    find_removals(av[1], &rem_open, &rem_close);
    char out[len];
    backtrack(av[1], out, 0, len, 0, rem_open, rem_close);
    return 0;
}