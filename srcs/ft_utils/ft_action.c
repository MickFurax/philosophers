#include "../../philosophers.h"

/* void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->data_mutex);
    philo->state = 2;
    philo->last_meal = get_time();
    printf("%ld %d is eating\n", get_time() - philo->data->start, philo->number);
    pthread_mutex_unlock(&philo->data->data_mutex);
    ft_sleep(philo->data->time_to_eat);
} */