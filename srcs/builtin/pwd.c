#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	pwd(void)
{
	char	buffer[100];

	if (getcwd(buffer, 100) == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}

int main(void)
{
	return (pwd());
}
