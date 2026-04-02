#include <unistd.h>
#include <stdlib.h> // for atoi

static int	is_safe(int *pos, int col, int row)
{
	int i;

	i = 0;
	while (i < col)
	{
		int prow = pos[i];
		if (prow == row ||
			prow - i == row - col ||
			prow + i == row + col)
			return (0);
		i++;
	}
	return (1);
}

static void	write_int(int n)
{
	char buf[12];
	int  i;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	i = 0;
	while (n > 0)
	{
		buf[i++] = (char)('0' + (n % 10));
		n /= 10;
	}
	while (--i >= 0)
		write(1, &buf[i], 1);
}

static void	print_solution(int *pos, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (i > 0)
			write(1, " ", 1);
		write_int(pos[i]);
		i++;
	}
	write(1, "\n", 1);
}

static void	solve(int *pos, int col, int n)
{
	if (col == n)
	{
		print_solution(pos, n);
		return ;
	}
	int row = 0;
	while (row < n)
	{
		if (is_safe(pos, col, row))
		{
			pos[col] = row;
			solve(pos, col + 1, n);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '-')
		return (1);
	int n = atoi(av[1]);
	if (n <= 0)
		return (0);
	int pos[n];
	int i = 0;
	while (i < n)
		pos[i++] = 0;
	solve(pos, 0, n);
	return (0);
}

