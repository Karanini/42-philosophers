/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:21:11 by michel_32         #+#    #+#             */
/*   Updated: 2025/12/31 11:26:48 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
* initialization of the mutexes. If a mutex init fails, the precedent mutexes
* successfully initialized are destroyed before returning `-1`
*/
int	ft_init_mutexes(t_data *data)
{
	if (ft_single_mutex_init(&data->print_mtx) == -1)
		return (-1);
	if (ft_single_mutex_init(&data->starting_mtx) == -1)
		return (pthread_mutex_destroy(&data->print_mtx), -1);
	if (ft_single_mutex_init(&data->death_flag_mtx) == -1)
	{
		pthread_mutex_destroy(&data->print_mtx);
		pthread_mutex_destroy(&data->starting_mtx);
		return (-1);
	}
	data->fork_mtx = ft_init_fork_mutexes(data->input_args->num_of_philos);
	if (!data->fork_mtx)
	{
		ft_destroy_global_mutexes(data);
		return (-1);
	}
	if (ft_init_meal_mutexes(data) == -1)
	{
		ft_destroy_global_mutexes(data);
		ft_destroy_fork_mutexes(data);
		return (-1);
	}
	return (0);
}

int	ft_single_mutex_init(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret != 0)
		return (-1);
	return (0);
}

pthread_mutex_t	*ft_init_fork_mutexes(int num_of_philos)
{
	pthread_mutex_t	*fork_mtx;
	int				i;

	fork_mtx = malloc(sizeof(pthread_mutex_t)
			* num_of_philos);
	if (!fork_mtx)
		return (NULL);
	i = 0;
	while (i < num_of_philos)
	{
		if (ft_single_mutex_init(&fork_mtx[i]) == -1)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork_mtx[i]);
			free(fork_mtx);
			return (NULL);
		}
		i++;
	}
	return (fork_mtx);
}

/**
 * @brief Assigns fork mutexes to each philosopher.
 *
 * This function iterates through the array of philosophers and assigns pointers
 * to the appropriate fork mutexes (left and right) for each philosopher.
 * It handles the logic to ensure that adjacent philosophers share the correct
 * forks.
 *
 * @param philo_tab Pointer to the array of philosopher structures.
 * @param fork_mtx  Pointer to the array of mutexes representing the forks.
 * @param philo_nbr The total number of philosophers.
 */
void	ft_assign_forks_to_philos(t_philo *philo_tab, pthread_mutex_t *fork_mtx,
		int num_philos)
{
	int	i;

	philo_tab[0].left_fork = &fork_mtx[num_philos - 1];
	philo_tab[0].right_fork = &fork_mtx[0];
	i = 1;
	while (i < num_philos)
	{
		philo_tab[i].left_fork = &fork_mtx[i - 1];
		philo_tab[i].right_fork = &fork_mtx[i];
		i++;
	}
}

int	ft_init_meal_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_args->num_of_philos)
	{
		if (ft_single_mutex_init(&data->philo_tab[i].meal_mtx) == -1)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philo_tab[i].meal_mtx);
			return (-1);
		}
		i++;
	}
	return (0);
}
