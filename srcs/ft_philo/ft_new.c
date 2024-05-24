#include "../../philosophers.h"

t_philo	*ft_newphilo(int number)
{
	t_philo	*philo;
	pthread_t		*thread;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->thread = malloc(sizeof(pthread_t));
	if (!philo->thread)
		return (free(philo), NULL);
	philo->number = number;
	philo->state = -1;
	philo->right_fork = NULL;
	philo->left_fork = NULL;
	philo->right_philo = NULL;
	philo->left_philo = NULL;
	philo->spagh_eaten = 0;
	return (philo);
}

t_fork	*ft_newfork(t_philo *owner)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->owner = owner;
	fork->picked = 0;
}
