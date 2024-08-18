/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:18:58 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 17:18:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	*ph_routine_philo(t_philosopher *philo)
{
	int	cnt;

	cnt = 0;
	while (philo->manager->must_eat_times == -1
		|| cnt < philo->manager->must_eat_times)
	{
		ph_observe_death(philo);
		ph_run_think(philo);
		ph_observe_death(philo);
		ph_run_eat(philo);
		ph_observe_death(philo);
		ph_run_sleep(philo);
		cnt++;
	}
	if (ph_is_alive(philo) == false)
		return (NULL);
	return (NULL);
}
