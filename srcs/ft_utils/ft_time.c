#include "../../philosophers.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_sleep(size_t time)
{
    usleep(time * 1000);
}

void	ft_getstart(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	data->philo_ready++;
	pthread_mutex_unlock(&data->data_mutex);
	pthread_mutex_lock(&data->data_mutex);
	if (data->philo_ready == data->philosophers)
	{
		if (data->start == 0)
			data->start = get_time();
	}
	pthread_mutex_unlock(&data->data_mutex);
}