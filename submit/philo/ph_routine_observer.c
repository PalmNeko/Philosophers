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
void	ph_check_all_philo(t_manager *manager);

void	*ph_routine_observer(t_manager *manager)
{
	bool			in_process;

	while (1)
	{
		ph_check_all_philo(manager);
		pthread_mutex_lock(&manager->lock);
		in_process = manager->in_process;
		pthread_mutex_unlock(&manager->lock);
		if (in_process == false)
			break ;
	}
	return (NULL);
}

void	ph_check_all_philo(t_manager *manager)
{
	int				index;
	t_philosopher	*philo;
	struct timeval	now;

	index = 0;
	while (index < manager->config->philo_cnt)
	{
		philo = &manager->philos[index++];
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
			return ;
		}
		pthread_mutex_unlock(&philo->lock);
	}
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
	timeradd(&philo->last_eat, &manager->config->die_tv, &added_tv);
	gettimeofday(now, NULL);
	if (timercmp(&added_tv, now, <))
		return (false);
	return (true);
}
