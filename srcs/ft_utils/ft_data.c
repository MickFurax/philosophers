#include "../../philosophers.h"

//One fork per thread

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

void	ft_initpriority(t_data *data)
{
	int	i;
	int	start;

	i = 0;
	start = 1;
	while (i < data->philosophers / 2)
	{
		data->priority[i] = start;
		start += 2;
		i++;
	}
}

void	ft_initdata(t_data *data, char *argv[])
{
	data->philosophers = atoi(argv[1]);
	ft_createphilos(data);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		printf("Mutex init failed\n");
		exit(1);
	}
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->times_each_philosopher_must_eat = -1;
	data->philo_ready = 0;
	data->start = 0;
	data->no_deaths = 1;
	data->finished_eating = 0;
	data->terminate = 1;
	data->priority = malloc(sizeof(int) * (data->philosophers / 2));
	if (!data->priority)
		return ;
	ft_initpriority(data);
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
	free(data->priority);
	free(data->philos);
}