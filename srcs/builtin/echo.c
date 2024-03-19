#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

int	echo(int n, char *args[])
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (n > 1 && ft_strncmp(args[1], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (i < n)
	{
		if (printf("%s", args[i]) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	if (nl)
		return (printf("\n") != -1);
	return (EXIT_SUCCESS);
}

int main(int n, char *args[])
{
	return (echo(n, args));
}
