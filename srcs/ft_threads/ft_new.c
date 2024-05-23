#include "../../philosophers.h"

t_philosopher	*ft_newphilo(int number)
{
	t_philosopher	*philo;
	pthread_t		thread;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->thread = thread;
	philo->number = number;
	philo->state = -1;
	philo->fork_held = 0;
	philo->right_fork = NULL;
	philo->left_fork = NULL;
	philo->right_philo = NULL;
	philo->left_philo = NULL;
	philo->spagh_eaten = 0;
	return (philo);
}

t_fork	*ft_newfork(t_philosopher *owner)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->owner = owner;
	fork->next = NULL;
	fork->prev = NULL;
	fork->picked = 0;
}
