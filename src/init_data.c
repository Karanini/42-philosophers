/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:55:29 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/31 11:24:34 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/**
 * @brief Initializes the main data structure for the simulation and the mutexes
 * required for synchronization. Assigns the forks to the philosophers.
 *
 * @param ac The argument count from the command line.
 * @param av The argument vector containing the simulation parameters as strings.
 * @return A pointer to the allocated and initialized `t_data` structure, or NULL
 *         if memory allocation fails or a mutex initialization fails.
 */
t_data	*ft_init_data(int ac, char *av[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->input_args = NULL;
	data->philo_tab = NULL;
	data->fork_mtx = NULL;
	data->input_args = ft_init_args_struct(ac, av);
	if (!data->input_args)
		return (ft_free_data(data), NULL);
	data->death_flag = 0;
	data->monitor_tid = -1;
	data->sim_start_time = 0;
	data->philo_tab = ft_init_philosophers(data);
	if (!data->philo_tab)
		return (ft_free_data(data), NULL);
	if (ft_init_mutexes(data) == -1)
		return (ft_free_data(data), NULL);
	ft_assign_forks_to_philos(data->philo_tab, data->fork_mtx,
		data->input_args->num_of_philos);
	return (data);
}

/*
* This function parses the command-line arguments and populates the `t_args`
 * structure with the simulation parameters (number of philosophers,
 * time to die, time to eat, time to sleep, and optionally the number
 * of times each philosopher must eat).
 *
 * @returns
 * `NULL` if parsing fails or `args` structure if parsing succeeds
*/
t_args	*ft_init_args_struct(int ac, char *av[])
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->num_of_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->number_of_meals = ft_atoi(av[5]);
	else
		args->number_of_meals = -1;
	if (ft_parse_input_args(args, ac - 1) == -1)
		return (NULL);
	return (args);
}

/*
* initializes the data structures specific to each philosopher
*/
t_philo	*ft_init_philosophers(t_data *data)
{
	t_philo	*philo_tab;
	int		num_philo;
	int		i;

	num_philo = data->input_args->num_of_philos;
	philo_tab = malloc(sizeof(t_philo) * num_philo);
	if (!philo_tab)
		return (NULL);
	i = 0;
	while (i < num_philo)
	{
		philo_tab[i].tid = -1;
		philo_tab[i].philo_id = i + 1;
		philo_tab[i].start_time = 0;
		philo_tab[i].meals_eaten = 0;
		philo_tab[i].data = data;
		i++;
	}
	return (philo_tab);
}
