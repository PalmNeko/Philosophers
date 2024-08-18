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

bool	ph_is_alive2(t_philosopher *philo, struct timeval *now);
void	ph_print_log_with_mutex(t_philosopher *philo, t_philo_action action);

void	ph_print_action(t_philosopher *philo, t_philo_action action)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	struct timeval			now;
	t_manager				*manager;

	manager = philo->manager;
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->manager->lock);
	gettimeofday(&now, NULL);
	if (manager->in_process && ph_is_alive2(philo, &now) == false)
	{
		ph_print_log(&philo->manager->start, &(t_log_info){.action = PH_DIE, .no = philo->no, .tv = now});
		manager->in_process = false;
	}
	if (manager->in_process == true)
		ph_print_log(&philo->manager->start, &(t_log_info){.action = action, .no = philo->no, .tv = now});
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->manager->lock);
}

bool	ph_is_alive2(t_philosopher *philo, struct timeval *now)
{
	struct timeval	added_tv;
	t_manager		*manager;

	manager = philo->manager;
	if (philo->in_process == true)
	{
		timeradd(&philo->last_eat, &manager->config->die_tv, &added_tv);
		gettimeofday(now, NULL);
		if (timercmp(&added_tv, now, <))
			return (false);
	}
	else
		return (false);
	return (true);
}
