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
#include <unistd.h>

void	ph_notify_to_manager(t_philosopher *philo, t_philo_action action);
bool	ph_is_alive2(t_philosopher *philo);

void	ph_append_log(t_philosopher *philo, t_philo_action action)
{
		t_action_queue	*queue;
	t_manager		*manager;

	queue = philo->manager->action_queue;
	manager = philo->manager;
	pthread_mutex_lock(&manager->lock);
	pthread_mutex_lock(&queue->lock);
	while ((queue->size >= queue->max_size - queue->max_size / 2)
		&& manager->in_process)
	{
		pthread_mutex_unlock(&queue->lock);
		pthread_mutex_unlock(&manager->lock);
		usleep(0);
		pthread_mutex_lock(&manager->lock);
		pthread_mutex_lock(&queue->lock);
	}
	if (manager->in_process)
	{
		if (ph_is_alive2(philo) == false)
		{
			manager->in_process = false;
			ph_enqueue(queue, philo->no, PH_DIE);
		}
		ph_enqueue(queue, philo->no, action);
	}
	pthread_mutex_unlock(&queue->lock);
	pthread_mutex_unlock(&manager->lock);
}

bool	ph_is_alive2(t_philosopher *philo)
{
	struct timeval	added_tv;
	struct timeval	now;
	t_manager		*manager;

	manager = philo->manager;
	if (philo->in_process == true)
	{
		timeradd(&philo->last_eat, &manager->config->die_tv, &added_tv);
		gettimeofday(&now, NULL);
		if (timercmp(&added_tv, &now, <))
			return (false);
	}
	else
		return (false);
	return (true);
}
