/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:17:35 by bkaras-g          #+#    #+#             */
/*   Updated: 2025/12/31 11:45:43 by bkaras-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
* checks if the input args have the correct format. The input args have been
* precedently converted to `int` by the `ft_atoi` function.
* If an incorrect number is detected, `ft_atoi` returns a negative number.
*/
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
