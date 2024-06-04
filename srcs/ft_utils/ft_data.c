#include "../../philosophers.h"

void	ft_createphilos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo *) * data->philosophers);
	if (!data->philos)
		return ;
	while (i < data->philosophers)
	{
		data->philos[i] = ft_newphilo(i + 1);
		data->philos[i]->data = data;
		pthread_mutex_init(&data->philos[i]->philo_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < data->philosophers)
	{
		if (i == 0)
			data->philos[i]->lfork = data->philos[data->philosophers
				- 1]->rfork;
		else
			data->philos[i]->lfork = data->philos[i - 1]->rfork;
		i++;
	}
}

void	ft_initdata(t_data *data, char *argv[])
{
	data->philosophers = atoi(argv[1]);
	ft_createphilos(data);
	pthread_mutex_init(&data->data_mutex, NULL);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->times_each_philosopher_must_eat = -1;
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
		pthread_mutex_destroy(data->philos[i]->rfork);
		free(data->philos[i]->rfork);
		free(data->philos[i]);
		i++;
	}
	pthread_mutex_destroy(&data->data_mutex);
	free(data->philos);
}