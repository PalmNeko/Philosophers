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
	int		cnt;
	bool	in_process;

	cnt = 0;
	while (philo->manager->must_eat_times == -1
		|| cnt < philo->manager->must_eat_times)
	{
		ph_run_think(philo);
		ph_run_eat(philo);
		ph_run_sleep(philo);
		pthread_mutex_lock(&philo->manager->lock);
		in_process = philo->manager->in_process;
		pthread_mutex_unlock(&philo->manager->lock);
		if (in_process == false)
			return (NULL);
		cnt++;
	}
	return (NULL);
}
