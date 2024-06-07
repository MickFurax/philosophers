#include "../../philosophers.h"

t_philo	*ft_newphilo(int number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->number = number;
	philo->state = -1;
	philo->spagh_eaten = 0;
	philo->fork_held = 0;
	philo->thread = 0;
	philo->rfork = malloc(sizeof(pthread_mutex_t));
	if (!philo->rfork)
		return (NULL);
	pthread_mutex_init(philo->rfork, NULL);
	philo->lfork = NULL;
	philo->last_meal = 0;
	return (philo);
}

void	get_priority(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers / 2)
	{
		data->priority[i] = data->priority[i] + 1;
		if (data->priority[i] > data->philosophers)
			data->priority[i] = 1;
		i++;
	}
}

int is_priority(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->philosophers)
	{
		if (data->priority[i] == philo->number)
			return (1);
		i++;
	}
	return (0);
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