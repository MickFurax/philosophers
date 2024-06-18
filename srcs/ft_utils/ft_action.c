#include "../../philosophers.h"

void	thinking(t_data *data, t_philo *philo)
{
		pthread_mutex_lock(&data->data_mutex);
		if (philo->state == -1)
		{
			philo->last_meal = get_time();
			philo->state = 1;
			printf("%ld %d is thinking\n", get_time() - data->start,
				philo->number);
		}
		pthread_mutex_unlock(&data->data_mutex);
}

void	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	printf("%ld %d has taken a fork\n", get_time() - data->start,
		philo->number);
	philo->fork_held++;
	pthread_mutex_lock(philo->lfork);
	printf("%ld %d has taken a fork\n", get_time() - data->start,
		philo->number);
	philo->fork_held++;
	if (philo->fork_held == 2)
	{
		printf("%ld %d is eating\n", get_time() - data->start, philo->number);
		philo->state = 2;
		pthread_mutex_unlock(&data->data_mutex);
		ft_sleep(data->time_to_eat);
		pthread_mutex_lock(&data->data_mutex);
	}
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	sleeping(t_data *data, t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - data->start, philo->number);
	ft_sleep(data->time_to_sleep);
	pthread_mutex_lock(&data->data_mutex);
	printf("%ld %d is thinking\n", get_time() - data->start, philo->number);
	pthread_mutex_unlock(&data->data_mutex);
}