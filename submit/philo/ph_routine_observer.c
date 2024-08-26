/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_observer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:29:18 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/26 15:29:18 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>

void	ph_close_philos(t_manager *manager);
bool	ph_is_alive(t_philosopher *philo, struct timeval *now);

void	*ph_routine_observer(t_manager *manager)
{
	int				index;
	t_philosopher	*philo;
	struct timeval	now;

	while (1)
	{
		index = 0;
		while (index < manager->config->philo_cnt)
		{
			philo = &manager->philos[index];
			pthread_mutex_lock(&philo->lock);
			gettimeofday(&now, NULL);
			if (ph_is_alive(philo, &now) == false)
			{
				philo->in_process = false;
				pthread_mutex_lock(&manager->lock);
				if (manager->in_process == true)
					ph_print_log(&manager->start, &(t_log_info){
						.action = PH_DIE, .no = philo->no, .tv = now});
				manager->in_process = false;
				pthread_mutex_unlock(&manager->lock);
				pthread_mutex_unlock(&philo->lock);
				ph_close_philos(manager);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->lock);
			index++;
		}
	}
	return (NULL);
}

void	ph_close_philos(t_manager *manager)
{
	int				index;
	t_philosopher	*philo;

	index = 0;
	while (index < manager->config->philo_cnt)
	{
		philo = &manager->philos[index];
		pthread_mutex_lock(&philo->lock);
		philo->in_process = false;
		pthread_mutex_unlock(&philo->lock);
		index++;
	}
	return ;
}

bool	ph_is_alive(t_philosopher *philo, struct timeval *now)
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
