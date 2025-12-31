/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:16:23 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/31 11:31:06 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	ft_all_philos_ate_well(t_data *data);
static int	ft_reaper(t_data *data);

/*
* monitoring routine to check if a philosopher died or, if applicable, if all
* the philosophers ate enough meals
*/
void	*ft_monitoring(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);
	while (1)
	{
		ft_precise_usleep(5000);
		if (ft_reaper(data))
			return (NULL);
		if (data->input_args->number_of_meals > 0
			&& ft_all_philos_ate_well(data))
			return (ft_raise_death_flag(data), NULL);
	}
	return (NULL);
}

/*
* checks if a philosopher died of starvation. If it's the case,
* prints a message announcing the death and raises the death_flag
* to stop the simulation
*/
static int	ft_reaper(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_args->num_of_philos)
	{
		pthread_mutex_lock(&data->philo_tab[i].meal_mtx);
		if (ft_get_time()
			- data->philo_tab[i].start_time > data->input_args->time_to_die)
		{
			pthread_mutex_unlock(&data->philo_tab[i].meal_mtx);
			ft_raise_death_flag(data);
			ft_print_msg(&data->philo_tab[i], DIE);
			return (1);
		}
		pthread_mutex_unlock(&data->philo_tab[i].meal_mtx);
		i++;
	}
	return (0);
}

/*
* checks if all the philos ate `number_of_meals` times, if this argument is
* specified.
*/
static int	ft_all_philos_ate_well(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_args->num_of_philos)
	{
		pthread_mutex_lock(&data->philo_tab[i].meal_mtx);
		if (data->philo_tab[i].meals_eaten < data->input_args->number_of_meals)
			return (pthread_mutex_unlock(&data->philo_tab[i].meal_mtx), 0);
		pthread_mutex_unlock(&data->philo_tab[i].meal_mtx);
		i++;
	}
	ft_raise_death_flag(data);
	return (1);
}
