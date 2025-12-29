/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solitary_life.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:42:44 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/29 16:03:17 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
* Routine for a solitary philosopher. Since there is only one fork, the philo
* can not start eating so it starves when `time_to_die` is reached.
*/
void	*ft_solitary_life(void *philo_struct)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	data = philo->data;
	pthread_mutex_lock(&data->starting_mtx);
	pthread_mutex_unlock(&data->starting_mtx);
	philo->start_time = data->sim_start_time;
	pthread_mutex_lock(philo->left_fork);
	ft_print_msg(philo, FORK);
	while (1)
	{
		if (ft_check_death_flag(data))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
	}
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
