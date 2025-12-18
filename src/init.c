/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:55:29 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/18 11:44:10 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// ft_init_args_struct()
// 	ft_init_mutexes();
// 	ft_init_threads();

t_data	*ft_init_data(int ac, char *av[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	//useful to init to NULL to optimize ft_cleanup in case of ?
	data->input_args = NULL;
	data->philo_tab = NULL;
	data->fork_mtx = NULL;
	data->input_args = ft_init_args_struct(ac, av);
	data->philo_id = -1;
	if (!data->input_args)
		return (ft_cleanup(data), NULL);
	data->philo_tab = ft_init_philosophers(data);
	if (!data->philo_tab)
		return (ft_cleanup(data), NULL);
	data->fork_mtx = ft_init_fork_mutexes(data->input_args, data->philo_tab);
	if (!data->fork_mtx)
		return (ft_cleanup(data), NULL);
	ft_assign_forks_to_philos(data->philo_tab, data->fork_mtx,
		data->input_args->number_of_philosophers);
}

t_args	*ft_init_args_struct(int ac, char *av[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->number_of_philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->number_of_meals = ft_atoi(av[5]);
	else
		args->number_of_meals = -1;
	return (args);
}

t_philo	*ft_init_philosophers(t_data *data)
{
	t_philo	*philo_tab;
	int		num_philo;
	int		i;

	num_philo = data->input_args->number_of_philosophers;
	philo_tab = malloc(sizeof(t_philo) * num_philo);
	if (!philo_tab)
		return (NULL);
	i = 0;
	while (i < num_philo)
	{
		philo_tab[i].tid = -1;
		philo_tab[i].start_time = 0;
		if (ft_mutex_init(philo_tab[i].print_mtx) == -1)
			return (NULL);
		i++;
	}
	return (philo_tab);
}

pthread_mutex_t	*ft_init_fork_mutexes(t_args *input_args, t_philo *philo_tab)
{
	pthread_mutex_t	*fork_mtx;
	int				i;

	fork_mtx = malloc(sizeof(pthread_mutex_t)
			* input_args->number_of_philosophers);
	if (!fork_mtx)
		return (NULL);
	i = 0;
	while (i < input_args->number_of_philosophers)
	{
		if (ft_mutex_init(fork_mtx[i]) == -1)
			return (NULL);
		i++;
	}
	return (fork_mtx);
}

void	ft_assign_forks_to_philos(t_philo *philo_tab, pthread_mutex_t *fork_mtx,
		int num_philos)
{
	int	i;

	philo_tab[0].left_fork = fork_mtx[num_philos - 1];
	philo_tab[0].right_fork = fork_mtx[0];
	i = 1;
	while (i < num_philos)
	{
		philo_tab[i].left_fork = fork_mtx[i - 1];
		philo_tab[i].right_fork = fork_mtx[i];
		i++;
	}
}
