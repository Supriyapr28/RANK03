#include <unistd.h>

int	ft_strlen(char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_sort(char *s)
{
	char tmp;
	for (int i = 0; s[i]; i++)
	{
		for (int j = i + 1; s[j]; j++)
		{
			if (s[i] > s[j])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
		}
	}
}

void	permute(char *src, int len, int *used, char *perm, int idx)
{
	if (idx == len)
	{
		write(1, perm, len);
		write(1, "\n", 1);
		return ;
	}
	int i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			perm[idx] = src[i];
			permute(src, len, used, perm, idx + 1);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	len = ft_strlen(argv[1]);
	if (len <= 0)
		return (0);
	ft_sort(argv[1]);
	// VLA on the stack instead of malloc
	int used[len];
	char perm[len + 1];
	int i = 0;
	while (i < len)
		used[i++] = 0;
	perm[len] = '\0';
	permute(argv[1], len, used, perm, 0);
	return (0);
}

//method: 2 without permutation function

#include <unistd.h>

int main(int ac, char **av)
{
    char *s;
    int   len;
    int   i, j;
    char  tmp;

    if (ac != 2)
        return (1);
    s = av[1];

    /* length */
    len = 0;
    while (s[len])
        len++;
    if (len == 0)
        return (0);

    /* sort s ascending so we start from first permutation */
    i = 0;
    while (i < len)
    {
        j = i + 1;
        while (j < len)
        {
            if (s[i] > s[j])
            {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
            j++;
        }
        i++;
    }

    /* generate all permutations in lexicographic order */
    while (1)
    {
        write(1, s, len);
        write(1, "\n", 1);

        /* find rightmost i such that s[i] < s[i+1] */
        i = len - 2;
        while (i >= 0 && s[i] >= s[i + 1])
            i--;
        if (i < 0)           /* no more permutations */
            break;

        /* find rightmost j > i with s[j] > s[i] */
        j = len - 1;
        while (s[j] <= s[i])
            j--;

        /* swap s[i], s[j] */
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;

        /* reverse tail s[i+1..len-1] */
        int l = i + 1;
        int r = len - 1;
        while (l < r)
        {
            tmp = s[l];
            s[l] = s[r];
            s[r] = tmp;
            l++;
            r--;
        }
    }
    return (0);
}