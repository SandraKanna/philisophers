#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_data
{
	int				num;
	pthread_mutex_t	lock_num;
}	t_data;

void	clean_struct(t_data *data)
{
	pthread_mutex_destroy(&data->lock_num);
	free(data);
}

void	*increment(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	pthread_mutex_lock(&data->lock_num);
	while (i < 500)
	{
		data->num++;
		pthread_mutex_unlock(&data->lock_num);
		i++;
	}
	return (NULL);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit (1);
	data->num = 0;
	pthread_mutex_init(&data->lock_num, NULL);
	return (data);
}

void	increment_and_print(void)
{
	pthread_t	t_1;
	pthread_t	t_2;
	t_data		*data;

	data = init_data();
	if (pthread_create(&t_1, NULL, increment, data))
	{
		clean_struct(data);
		exit (2);
	}
	if (pthread_create(&t_2, NULL, increment, data))
	{
		clean_struct(data);
		exit (2);
	}
	if (pthread_join(t_1, NULL))
		exit (1);
	if (pthread_join(t_2, NULL))
		exit (1);
	printf("num: %d\n", data->num);
	clean_struct(data);
	// pthread_detach(t_1);
	// pthread_detach(t_2);
}

int	main(void)
{
	increment_and_print();
	return (0);
}
