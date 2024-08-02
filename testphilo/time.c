#include <stdio.h> // printf
#include <sys/time.h> // time
#include <stdint.h> // uint64_t
#include <unistd.h> // usleep


long long	get_secs(void)
{
	struct timeval	tv;
	long long		time;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	time = tv.tv_sec + (tv.tv_usec / 1000000);
	return (time);
}

long long	get_milisecs(void)
{
	struct timeval	tv;
	long long		time;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	get_cur_time_in_secs(void)
{
	struct timeval	tv;
	long long		start;
	long long		now;

	start = get_secs();
	sleep(1);
	now = get_secs();
	printf("secs passed since start: %lld \n", now - start);
}

void	get_cur_time_in_ms(void)
{
	struct timeval	tv;
	long long		start;
	long long		now;

	start = get_milisecs();
	usleep(20000);
	now = get_milisecs();
	printf("milisecs passed since start: %lld \n", now - start);
}


int	main(void)
{
	long long	secs;
	long long	milisecs;

	get_cur_time_in_ms();
	get_cur_time_in_secs();
	secs = get_secs();
	printf("seconds: %lld \n", secs);
	sleep(1);
	fflush(stdout);
	milisecs = get_milisecs();
	printf("miliseconds: %lld \n", milisecs);
	
	return (0);
}