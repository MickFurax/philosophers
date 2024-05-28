/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabeman <arabeman@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:59:58 by arabeman          #+#    #+#             */
/*   Updated: 2024/05/20 11:00:01 by arabeman         ###   ########.fr       */
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

typedef struct s_data
{
	int					philosophers;
	t_philo				**philos;
	char				*forks;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_each_philosopher_must_eat;
	pthread_mutex_t		data_mutex;
}						t_data;

/* state
0: dead
1: thinking
2: eating */
typedef struct s_philo
{
	pthread_t			thread;
	int					number;
	int					state;
	int					spagh_eaten;
	t_data				*data;
	pthread_mutex_t		philo_mutex;
}						t_philo;

t_philo					*ft_newphilo(int number);
// t_fork						*ft_newfork(t_philo *owner);

void					ft_createphilos(t_data *data, char *argv[]);
void					ft_initdata(t_data *data, char *argv[]);
void					ft_freedata(t_data *data);

#endif
