#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <stdio.h>

void	find_removals(char *input, int *remove_open, int *remove_close)
{
	int	i;

	i = 0;
	*remove_open = 0;
	*remove_close = 0;
	while (input[i])
	{
		if (input[i] == '(')
			(*remove_open)++;
		else if (input[i] == ')')
		{
			if (*remove_open > 0)
				(*remove_open)--;
			else
				(*remove_close)++;
		}
		i++;
	}
}

void	generate(char *input, char *output, int pos,
		int open_count, int remove_open, int remove_close)
{
	if (!input[pos])
	{
		if (open_count == 0 && remove_open == 0 && remove_close == 0)
			printf("%s\n", output);
		return ;
	}
	output[pos] = input[pos];
	if (input[pos] == '(')
	{
		if (remove_open > 0)
		{
			//exclude
			output[pos] = ' ';
			generate(input, output, pos + 1, open_count, remove_open - 1, remove_close);
		}
		//include
		output[pos] = '(';
		generate(input, output, pos + 1, open_count + 1, remove_open, remove_close);
	}
	else if (input[pos] == ')')
	{
		if (remove_close > 0)
		{
			//exclude
			output[pos] = ' ';
			generate(input, output, pos + 1, open_count, remove_open, remove_close - 1);
		}
		if (open_count > 0)
		{
			// include
			output[pos] = ')';
			generate(input, output, pos + 1, open_count - 1, remove_open, remove_close);
		}
	}
	else
		generate(input, output, pos + 1, open_count, remove_open, remove_close);
}

int	main(int argc, char **argv)
{
	char	*input;
	char	*output;
	int		remove_open;
	int		remove_close;

	if (argc != 2)
		return (0);
	input = argv[1];
	output = (char *)malloc(sizeof(char) * (strlen(input) + 1));
	if (!output)
		return (1);
	find_removals(input, &remove_open, &remove_close);
	generate(input, output, 0, 0, remove_open, remove_close);
	free(output);
	return (0);
}
