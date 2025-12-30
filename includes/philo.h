/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:40:32 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/30 13:59:45 by bkaras-g         ###   ########.fr       */
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

typedef enum e_print_msg_type
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}						t_print_msg_type;

typedef struct s_data	t_data;

// input args of the program
typedef struct s_args
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
}						t_args;

// data specific to each philosopher
typedef struct s_philo
{
	pthread_t			tid;
	int					philo_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			start_time;
	int					meals_eaten;
	pthread_mutex_t		meal_mtx;
	t_data				*data;
}						t_philo;

// structure containing (or linking to) all the data of the program
typedef struct s_data
{
	t_args				*input_args;
	t_philo				*philo_tab;
	pthread_mutex_t		*fork_mtx;
	pthread_mutex_t		starting_mtx;
	pthread_mutex_t		print_mtx;
	int					death_flag;
	pthread_mutex_t		death_flag_mtx;
	pthread_t			monitor_tid;
	long long			sim_start_time;
}						t_data;

/**********INIT ****************/
t_data					*ft_init_data(int ac, char *av[]);
t_args					*ft_init_args_struct(int ac, char *av[]);
t_philo					*ft_init_philosophers(t_data *data);
int						ft_init_mutexes(t_data *data);
pthread_mutex_t			*ft_init_fork_mutexes(int num_of_philos);
void					ft_assign_forks_to_philos(t_philo *philo_tab,
							pthread_mutex_t *fork_mtx, int num_philos);
int						ft_single_mutex_init(pthread_mutex_t *mutex);
int						ft_init_threads(t_data *data);

/**********PARSING ****************/
int						ft_parse_input_args(t_args *args, int nb_args);

/**********UTILS ****************/
int						ft_atoi(const char *nptr);
long long				ft_get_time(void);
void					ft_precise_usleep(long usec);
int						ft_wait_and_check(t_philo *philo, int time_to_wait);
int						ft_check_death_flag(t_data *data);
void					ft_raise_death_flag(t_data *data);
void					ft_print_msg(t_philo *philo, t_print_msg_type msg_type);
void					ft_lock_forks(t_philo *philo,
							pthread_mutex_t *first_fork,
							pthread_mutex_t *second_fork);
void					ft_unlock_forks(pthread_mutex_t *first_fork,
							pthread_mutex_t *second_fork);

/**********RUN IT ****************/
void					*ft_wise_life(void *data);
int						ft_eat(t_philo *philo);
void					*ft_solitary_life(void *philo_struct);

/**********MONITORING ****************/
void					*ft_monitoring(void *data_struct);

/**********DIRTY LAUNDRY ****************/
void					ft_cleanup(t_data *data);
void					ft_free_data(t_data *data);
void					ft_destroy_fork_mutexes(t_data *data);

#endif
