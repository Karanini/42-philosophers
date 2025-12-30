/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:34:07 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/30 15:37:14 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_lock_forks(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	ft_print_msg(philo, FORK);
	pthread_mutex_lock(second_fork);
	ft_print_msg(philo, FORK);
}

void	ft_unlock_forks(pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

void	ft_grant_more_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->start_time = ft_get_time();
	pthread_mutex_unlock(&philo->meal_mtx);
}

void	ft_mark_full_belly(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mtx);
}
