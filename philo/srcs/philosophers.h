/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:06:58 by arabeman          #+#    #+#             */
/*   Updated: 2024/06/20 09:07:02 by arabeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_arg
{
	t_data				*data;
	t_philo				*philo;
}						t_arg;

typedef struct s_data
{
	int					philosophers;
	t_philo				**philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_each_philosopher_must_eat;
	int					finished_eating;
	int					no_deaths;
	int					*priority;
	size_t				start;
	pthread_mutex_t		data_mutex;
}						t_data;

/* state
-1: none
0: dead
1: thinking
2: eating
3: sleeping */
typedef struct s_philo
{
	pthread_t			thread;
	int					number;
	int					state;
	int					spagh_eaten;
	size_t				last_meal;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		philo_mutex;
}						t_philo;

void					init_data(t_data *data, int argc, char *argv[]);
void					free_data(t_data *s_data);

t_philo					*newphilo(int number);
void					create_philos(t_data *data);
void					launch_philos(t_data *data);
void					*routine(void *arg);

size_t					get_time(void);
void					ft_sleep(int time);

#endif
