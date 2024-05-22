#include "../../philosophers.h"

t_philosopher	*ft_newphilo(int number)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->number = number;
	philo->state = 1;
	philo->fork_held = 0;
	philo->right_fork = NULL;
	philo->left_fork = NULL;
	philo->right_philo = NULL;
	philo->left_philo = NULL;
	philo->spagh_eaten = 0;
    return (philo);
}
