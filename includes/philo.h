/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:40:32 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/18 11:14:04 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
}					t_args;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	long long start_time; // beginning of the simulation or when the philosopher
							// starts to eat
}					t_philo;

typedef struct s_data
{
	t_args			*input_args;
	t_philo			*philo_tab;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	starting_mtx;
	int				philo_id;
}					t_data;

/**********INIT ****************/
t_args				*ft_init_args_struct(int ac, char *av[]);
t_philo				*ft_init_philosophers(t_data *data);
pthread_mutex_t		*ft_init_fork_mutexes(t_args *input_args,
						t_philo *philo_tab);
void				ft_assign_forks_to_philos(t_philo *philo_tab,
						pthread_mutex_t *fork_mtx, int num_philos);
int					ft_mutex_init(pthread_mutex_t mutex);

/**********UTILS ****************/
int					ft_atoi(const char *nptr);

/**********RUN IT ****************/
void				*ft_wise_life(t_data *data);

#endif
