#include "../../philosophers.h"

void	thinking(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->data_mutex);
	if (philo->state == -1)
	{
		philo->last_meal = get_time();
		philo->state = 1;
		printf("%ld %d is thinking\n", get_time() - data->start, philo->number);
	}
	pthread_mutex_unlock(&data->data_mutex);
}

void eating(t_data *data, t_philo *philo, int time_to_eat)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    // Determine the order of forks to lock based on philosopher number
    if (philo->number % 2 == 0)
    {
        first_fork = philo->lfork;
        second_fork = philo->rfork;
    }
    else
    {
        first_fork = philo->rfork;
        second_fork = philo->lfork;
    }

    // Acquire forks in a consistent order
    pthread_mutex_lock(first_fork);
    printf("%ld %d has taken a fork\n", get_time() - data->start, philo->number);
    philo->fork_held++;
    
    pthread_mutex_lock(second_fork);
    printf("%ld %d has taken a fork\n", get_time() - data->start, philo->number);
    philo->fork_held++;

    // Check if the philosopher has both forks
    if (philo->fork_held == 2)
    {
        philo->last_meal = get_time();
        printf("\033[1;93m%ld %d is eating\033[0m\n", get_time() - data->start, philo->number);
        philo->state = 2;
        ft_sleep(time_to_eat);
    }

    // Release the forks
    pthread_mutex_unlock(first_fork);
    pthread_mutex_unlock(second_fork);
    philo->fork_held -= 2;
}


void	sleeping(t_data *data, t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time() - data->start, philo->number);
	ft_sleep(data->time_to_sleep);
	pthread_mutex_lock(&data->data_mutex);
	printf("%ld %d is thinking\n", get_time() - data->start, philo->number);
	pthread_mutex_unlock(&data->data_mutex);
}