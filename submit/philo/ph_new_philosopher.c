/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_new_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:47:47 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 19:47:47 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <stdlib.h>

/**
 * @param must_eat_times negative: unlimited
 */
t_philosopher	*ph_new_philosopher(
		int time_to_die,
		int time_to_eat,
		int time_to_sleep,
		int must_eat_times)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (philo == NULL)
		return (NULL);
	philo->time_to_die = time_to_die;
	philo->time_to_eat = time_to_eat;
	philo->time_to_sleep = time_to_sleep;
	philo->must_eat_times = must_eat_times;
	return (philo);
}
