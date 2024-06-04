#include "../../philosophers.h"

t_fork	*ft_newfork(int number)
{
	t_fork			*fork;
	pthread_mutex_t	mutex;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->number = number;
	fork->state = 1;
	pthread_mutex_init(&mutex, NULL);
	fork->fork_mutex = mutex;
	return (fork);
}

void	ft_takerightfork(t_data *data, t_philo *philo)
{
	t_fork	**forks;
	int		index;

	index = philo->number - 1;
	forks = data->forks;
	if (forks[index]->state == 1)
	{
		pthread_mutex_lock(&forks[index]->fork_mutex);
		forks[index]->state = 0;
		printf("%d takes a fork at his right\n", philo->number);
		philo->fork_held += 1;
		pthread_mutex_unlock(&forks[index]->fork_mutex);
	}
}

void	ft_takeleftfork(t_data *data, t_philo *philo)
{
	t_fork	**forks;
	int		index;

	index = philo->number - 1;
	forks = data->forks;
	if (index == 0)
		index = data->philosophers - 1;
	if (forks[index]->state == 1)
	{
		pthread_mutex_lock(&forks[index]->fork_mutex);
		forks[index]->state = 0;
		printf("%d takes a fork at his left\n", philo->number);
		philo->fork_held += 1;
		pthread_mutex_unlock(&forks[index]->fork_mutex);
	}
}
