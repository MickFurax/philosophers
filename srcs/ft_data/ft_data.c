#include "../../philosophers.h"

void	ft_createphilos(t_data *data, char *argv[])
{
	t_philo	*philo;
	t_philo	*temp;
	int		i;

	philo = NULL;
	i = 1;
	while (i <= data->philosophers)
	{
		ft_addphilo(&philo, ft_newphilo(i));
		i++;
	}
	data->first_philo = philo;
	data->last_philo = ft_lastphilo(philo);
	i = 1;
	temp = philo;
	while (i <= data->philosophers)
	{
		philo->data = *data;
		philo = philo->right_philo;
		i++;
	}
}

void	ft_initdata(t_data *data, char *argv[])
{
	data->philosophers = atoi(argv[1]);
	ft_createphilos(data, argv);
	data->first_fork = data->first_philo->right_fork;
	data->last_fork = data->first_philo->left_fork;
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
}

void	ft_freedata(t_data *data)
{
	t_philo *temp;
	int i;

	i = 0;
	while (i < data->philosophers)
	{
		temp = data->first_philo;
		data->first_philo = data->first_philo->right_philo;
		pthread_join(*(temp->thread), NULL);
		free(temp->thread);
		free(temp->right_fork);
		free(temp);
		i++;
	}
}