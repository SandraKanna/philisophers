#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>
#include <stdio.h> // printf


void	*print_hello(void *arg)
{
	int i = 0;

	while (i < 20)
	{
		printf("HEllo");
		i++;
		usleep(1000);
	}
	return (NULL);
}

void	*print_world(void *arg)
{
	int i = 0;

	while (i < 10)
	{
		printf("\t\tworld\n");
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	print_threads_1(void)
{
	pthread_t	t_1;
	pthread_t	t_2;

	if (pthread_create(&t_1, NULL, print_hello, NULL))
		exit (1);
	if (pthread_create(&t_2, NULL, print_world, NULL))
		exit (1);
	if (pthread_join(t_1, NULL))
		exit (1);
	if (pthread_join(t_2, NULL))
		exit (1);
}

void	*increment(void *arg)
{
	int	*num;
	int	i;

	num = (int *)arg;
	i = 0;
	while (i < 500)
	{
		(*num)++;
		i++;
	}
	return (NULL);
}

void	increment_and_print(void)
{
	pthread_t	t_1;
	pthread_t	t_2;
	int			*num;

	num = malloc(sizeof(int));
	if (!num)
		exit (1);
	*num = 0;
	if (pthread_create(&t_1, NULL, increment, num))
	{
		free(num);
		exit (2);
	}
	if (pthread_create(&t_2, NULL, increment, num))
	{
		free(num);
		exit (2);
	}
	if (pthread_join(t_1, NULL))
		exit (1);
	if (pthread_join(t_2, NULL))
		exit (1);
	printf("num: %d\n", *num);
	// pthread_detach(t_1);
	// pthread_detach(t_2);
}

int	main(void)
{
	// print_hello(NULL);
	// print_world(NULL);
	// print_threads_1();
	increment_and_print();
	return (0);
}