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

typedef struct s_data		t_data;
typedef struct s_philospher	t_philo;
typedef struct s_fork		t_fork;

typedef struct s_current
{
	t_data					*data;
	t_philo					*philo;
}							t_current;

/* first_fork is the fork to the right of the first philosopher
last_fork is the fork to the left of the first philosopher
last_fork is the fork to the right of the first philosopher if there is only one philosopher
nb: same for the last_philo */
typedef struct s_data
{
	int						philosophers;
	t_philo					*first_philo;
	t_philo					*last_philo;
	t_fork					*first_fork;
	t_fork					*last_fork;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						times_each_philosopher_must_eat;
}							t_data;

/* stateu
0: dead
1: thinking
2: eating */
typedef struct s_philospher
{
	pthread_t				*thread;
	int						number;
	int						state;
	t_fork					*right_fork;
	t_fork					*left_fork;
	t_philo					*right_philo;
	t_philo					*left_philo;
	int						spagh_eaten;
	t_data					data;
}							t_philo;

typedef struct s_fork
{
	t_philo					*owner;
	int						picked;
	pthread_mutex_t			*fork_state;
}							t_fork;

t_philo						*ft_newphilo(int number);
t_fork						*ft_newfork(t_philo *owner);

t_philo						*ft_lastphilo(t_philo *philo);
void						ft_addphilo(t_philo **philos, t_philo *newphilo);

void						ft_createphilos(t_data *data, char *argv[]);
void						ft_initdata(t_data *data, char *argv[]);
void						ft_freedata(t_data *data);

#endif
