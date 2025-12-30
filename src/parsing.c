/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:17:35 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/30 10:28:30 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_parse_input_args(t_args *args, int nb_args)
{
	if (nb_args == 4)
	{
		if (args->num_of_philos <= 0 || args->time_to_die < 0
			|| args->time_to_eat < 0 || args->time_to_sleep < 0)
		{
			printf("Error: one or more arguments have an incorrect format\n");
			return (-1);
		}
	}
	else if (nb_args == 5)
	{
		if (args->num_of_philos <= 0 || args->time_to_die < 0
			|| args->time_to_eat < 0 || args->time_to_sleep < 0
			|| args->number_of_meals <= 0)
		{
			printf("Error: one or more arguments have an incorrect format\n");
			return (-1);
		}
	}
	return (0);
}
