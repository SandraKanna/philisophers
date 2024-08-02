#include <stdio.h> // printf
#include <sys/time.h> // time
#include <stdint.h> // uint64_t
#include <unistd.h> // usleep

void	print_hello(void)
{
	printf("HEllo");
	usleep(10000);
}

void	print_world(void)
{
	printf("\t\tWorld");
	usleep(10000);
}

int	main(void)
{
	print_hello();
	print_world();

	return (0);
}
