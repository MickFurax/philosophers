#include "../../philosophers.h"

void	ft_createphilos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * data->philosophers);
	if (!data->philos)
		return ;
	data->forks = malloc(sizeof(t_fork *) * data->philosophers);
	if (!data->forks)
		return ;
	while (i < data->philosophers)
	{
		data->philos[i] = ft_newphilo(i + 1);
		data->forks[i] = ft_newfork(i + 1);
		data->philos[i]->data = data;
		pthread_mutex_init(&data->philos[i]->philo_mutex, NULL);
		i++;
	}
}

void	ft_initdata(t_data *data, char *argv[])
{
	char	*forks;

	data->philosophers = atoi(argv[1]);
	ft_createphilos(data);
	pthread_mutex_init(&data->data_mutex, NULL);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->times_each_philosopher_must_eat = -1;
	forks = malloc(sizeof(char) * (data->philosophers + 1));
	if (!forks)
		return ;
	memset(forks, '1', sizeof(char) * (data->philosophers + 1));
	forks[data->philosophers] = '\0';
	data->forks = forks;
}

// Join aloha
void	ft_freedata(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philosophers)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->philosophers)
	{
		pthread_mutex_destroy(&data->philos[i]->philo_mutex);
		free(data->philos[i]);
		i++;
	}
	pthread_mutex_destroy(&data->data_mutex);
	free(data->philos);
	free(data->forks);
}