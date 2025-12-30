/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:16:23 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/30 15:18:33 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	ft_all_philos_ate_well(t_data *data);
static int	ft_reaper(t_data *data);

void	*ft_monitoring(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);
	while (1)
	{
		ft_precise_usleep(1000);
		if (ft_reaper(data))
			return (NULL);
		// while (i < data->input_args->num_of_philos)
		// {
		// 	if (ft_get_time()
		// 		- data->philo_tab[i].start_time > data->input_args->time_to_die)
		// 	{
		// 		ft_print_msg(&data->philo_tab[i], DIE);
		// 		ft_raise_death_flag(data);
		// 		return (NULL);
		// 	}
		// 	i++;
		// }
		if (data->input_args->number_of_meals > 0
			&& ft_all_philos_ate_well(data))
		{
			ft_raise_death_flag(data);
			return (NULL);
		}
	}
	return (NULL);
}

static int	ft_reaper(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_args->num_of_philos)
	{
		if (ft_get_time()
			- data->philo_tab[i].start_time > data->input_args->time_to_die)
		{
			ft_print_msg(&data->philo_tab[i], DIE);
			ft_raise_death_flag(data);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_all_philos_ate_well(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_args->num_of_philos)
	{
		if (data->philo_tab[i].meals_eaten < data->input_args->number_of_meals)
			return (0);
		i++;
	}
	ft_raise_death_flag(data);
	return (1);
}
