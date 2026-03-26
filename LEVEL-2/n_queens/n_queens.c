#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int is_safe(int *positions, int current_col, int current_row)
{
	//starts from col 0 and checks all previously placed queens to see if the current position is safe
	for (int prev_col = 0; prev_col < current_col; prev_col++)
	{
		int prev_row = positions[prev_col];
		// Check if the current position is in the same row or diagonal as any previously placed queen
		//if condition true there is a conflict and we return 0 (not safe)
		if (prev_row == current_row || // check same row
			prev_row - prev_col == current_row - current_col || //check main diagonal
			prev_row + prev_col == current_row + current_col)  //check anti-diagonal
			return 0;
	}
	return 1;
}

void solve(int *positions, int col, int n)
{
	if (col == n)
	{
		int i = 0;
		while(i < n)
		{
			if (i > 0) // Print space before the number, but not before the first one
				printf(" ");
			printf("%d", positions[i]);
			i++;
		}
		printf("\n");
		return;
	}
	int row = 0;
	while(row < n)
	{
		if(is_safe(positions, col, row))
		{
			positions[col] = row;
			solve(positions, col + 1, n);
		}
		row++;
	}
}

int main(int ac, char **av)
{
	if(ac == 2 && av[1][0] != '-')
	{
		int n = atoi(av[1]);// convert string to integer
		int *q_positions = malloc(sizeof(int) * n);//arr to store q positions
		if (!q_positions)
			return 1;
		solve(q_positions, 0, n);
		free(q_positions);
	}
	return 0;
}