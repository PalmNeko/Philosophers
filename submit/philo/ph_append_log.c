/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_act_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:51:59 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/14 16:51:59 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdio.h>

void	ph_notify_to_manager(t_philosopher *philo, t_philo_action action);

void	ph_append_log(t_philosopher *philo, t_philo_action action)
{
	t_manager		*manager;
	struct timeval	added_tv;

	manager = philo->manager;
	pthread_mutex_lock(&manager->lock);
	if (manager->in_process == true)
	{
		timeradd(&philo->last_eat, &manager->die_tv, &added_tv);
		if (timercmp(&added_tv, &manager->now, <))
		{
			ph_notify_to_manager(philo, PH_DIE);
			manager->in_process = false;
		}
	}
	if (manager->in_process == true)
		ph_notify_to_manager(philo, action);
	pthread_mutex_unlock(&manager->lock);
}

void	ph_notify_to_manager(t_philosopher *philo, t_philo_action action)
{
	ph_enqueue_with_lock(philo->manager->action_queue, philo->no, action);
}
