/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:53:09 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 17:53:09 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ph.h"

bool	ph_is_alive(t_philosopher *philo)
{
	bool			in_progress;
	t_manager		*manager;
	struct timeval	added_tv;

	manager = philo->manager;
	pthread_mutex_lock(&manager->lock);
	in_progress = manager->in_process;
	if (in_progress == true)
	{
		timeradd(&philo->last_eat, &manager->config->die_tv, &added_tv);
		if (timercmp(&added_tv, &manager->now, <))
		{
			ph_append_log(philo, PH_DIE);
			manager->in_process = false;
			in_progress = false;
		}
	}
	pthread_mutex_unlock(&manager->lock);
	return (in_progress);
}
