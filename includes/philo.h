/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:40:32 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/25 15:48:04 by bkaras-g         ###   ########.fr       */
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

typedef struct s_data t_data;

// input args of the program
typedef struct s_args
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
}					t_args;

//data specific to each philosopher
typedef struct s_philo
{
	pthread_t		tid;
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long start_time; // (1) beginning of the simulation or (2) when the philosopher
							// starts to eat
	t_data			*data;
}					t_philo;

//structure containing (or linking to) all the data of the program
typedef struct s_data
{
	t_args			*input_args;
	t_philo			*philo_tab;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	starting_mtx;
	pthread_mutex_t	print_mtx;
}					t_data;

/**********INIT ****************/
t_data				*ft_init_data(int ac, char *av[]);
t_args				*ft_init_args_struct(int ac, char *av[]);
t_philo				*ft_init_philosophers(t_data *data);
pthread_mutex_t		*ft_init_fork_mutexes(t_args *input_args);
void				ft_assign_forks_to_philos(t_philo *philo_tab,
						pthread_mutex_t *fork_mtx, int num_philos);
int					ft_mutex_init(pthread_mutex_t *mutex);
int					ft_init_threads(t_data *data);

/**********UTILS ****************/
int					ft_atoi(const char *nptr);

/**********RUN IT ****************/
void				*ft_wise_life(void *data);

/**********DIRTY LAUNDRY ****************/
void				ft_cleanup(t_data *data);

#endif
