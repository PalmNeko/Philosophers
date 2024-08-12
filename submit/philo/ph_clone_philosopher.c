/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_clone_philosopher.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:20:56 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/12 14:23:27 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>

t_philosopher	*ph_clone_philosopher(t_philosopher *philo)
{
	t_philosopher	*cloned;

	cloned = ph_new_philosopher(
			philo->time_to_die,
			philo->time_to_eat,
			philo->time_to_sleep,
			philo->must_eat_times);
	return (cloned);
}
