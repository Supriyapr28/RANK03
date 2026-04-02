#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_sort(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
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
}

void	ft_solve(char *str, int *used, char *perm, int perm_idx, int len)
{
	if (perm_idx == len)
	{
		int	i = 0;
		while (perm[i])
			i++;
		write(1, perm, i);
		write(1, "\n", 1);
		return ;
	}
	int	i = 0;
	while (i < len)
	{
		if (used[i] == 0)
		{
			used[i] = 1;
			perm[perm_idx] = str[i];
			ft_solve(str, used, perm, perm_idx + 1, len);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		len;
	int		*used;
	char	*perm;

	if (argc != 2)
		return (1);
	len = 0;
	while (argv[1][len])
		len++;
	ft_sort(argv[1]);
	used = (int *)calloc(len, sizeof(int));
	perm = (char *)calloc(len + 1, sizeof(char));
	if (!used || !perm)
		return (1);
	ft_solve(argv[1], used, perm, 0, len);
	free(used);
	free(perm);
	return (0);
}

/*Recursive tree for input "abc":
                            START (perm="", used={0,0,0})
                                       |
          ---------------------------------------------------------
          |                            |                          |
    Pick 'a' (i=0)               Pick 'b' (i=1)             Pick 'c' (i=2)
    (perm="a", used={1,0,0})     (perm="b", used={0,1,0})   (perm="c", used={0,0,1})
          |                            |                          |
    -------------                -------------              -------------
    |           |                |           |              |           |
 Pick 'b'    Pick 'c'         Pick 'a'    Pick 'c'       Pick 'a'    Pick 'b'
 (perm="ab") (perm="ac")      (perm="ba") (perm="bc")    (perm="ca") (perm="cb")
    |           |                |           |              |           |
    |           |                |           |              |           |
 Pick 'c'    Pick 'b'         Pick 'c'    Pick 'a'       Pick 'b'    Pick 'a'
 (perm="abc")(perm="acb")     (perm="bac")(perm="bca")   (perm="cab")(perm="cba")
    |           |                |           |              |           |
  PRINT       PRINT            PRINT       PRINT          PRINT       PRINT
  "abc"       "acb"            "bac"       "bca"          "cab"       "cba"
*/