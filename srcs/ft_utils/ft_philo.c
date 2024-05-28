#include "../../philosophers.h"

t_philo	*ft_newphilo(int number)
{
	t_philo			*philo;
	pthread_t		thread;
	pthread_mutex_t	mutex;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->number = number;
	philo->state = -1;
	philo->spagh_eaten = 0;
	philo->thread = thread;
	philo->philo_mutex = mutex;
	pthread_mutex_init(&philo->philo_mutex, NULL);
	return (philo);
}

/* void	ft_addphilo(t_philo **philos, t_philo *newphilo)
{
	t_philo	*last;
	t_fork	*fork;

	if (!newphilo)
		return ;
	fork = ft_newfork(newphilo);
	if (!fork)
		return ;
	newphilo->right_fork = fork;
	if (*philos)
	{
		last = ft_lastphilo(*philos);
		last->right_philo = newphilo;
		newphilo->left_philo = last;
		newphilo->right_philo = *philos;
		(*philos)->left_philo = newphilo;
		newphilo->left_fork = last->right_fork;
	}
	else
	{
		(*philos) = newphilo;
		newphilo->right_philo = newphilo;
		newphilo->left_philo = newphilo;
		newphilo->left_fork = fork;
	}
}

t_philo	*ft_lastphilo(t_philo *philo)
{
	t_philo	*last;

	if (!philo)
		return (NULL);
	last = philo;
	while (last->right_philo != philo)
		last = last->right_philo;
	return (last);
}



t_fork	*ft_newfork(t_philo *owner)
{
	t_fork *fork;
	pthread_mutex_t *mutex;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex)
		return (NULL);
	fork->owner = owner;
	fork->picked = 0;
	fork->fork_state = mutex;
} */