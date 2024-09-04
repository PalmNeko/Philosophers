/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_update_manager.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:14:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 17:14:13 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <sys/time.h>
#include <unistd.h>

void	ph_update_philo_eating(t_manager *manager, bool *eat_switch);
void	ph_exit_all_philo(t_manager *manager);

void	*ph_routine_update_manager(t_manager *manager)
{
	bool	in_progress;
	bool	eat_switch;

	eat_switch = false;
	manager->target_no = 0;
	while (1)
	{
		pthread_mutex_lock(&manager->lock);
		in_progress = manager->in_process;
		pthread_mutex_unlock(&manager->lock);
		if (in_progress == false)
			break ;
		ph_update_philo_eating(manager, &eat_switch);
		if (usleep(0) == -1)
		{
			pthread_mutex_lock(&manager->lock);
			manager->in_process = false;
			pthread_mutex_unlock(&manager->lock);
			break ;
		}
	}
	ph_exit_all_philo(manager);
	return (NULL);
}

void	ph_update_philo_eating(t_manager *manager, bool *eat_switch)
{
	t_philosopher	*target;

	target = &manager->philos[manager->target_no];
	pthread_mutex_lock(&target->lock);
	if (*eat_switch == false && target->eating_order == false)
	{
		target->eating_order = true;
		*eat_switch = true;
	}
	else if (*eat_switch == true && target->eating_order == false)
	{
		*eat_switch = false;
		manager->target_no += 2;
		if (manager->target_no >= manager->config->philo_cnt)
			manager->target_no = (manager->target_no + 1) % 2;
	}
	pthread_mutex_unlock(&target->lock);
}

void	ph_exit_all_philo(t_manager *manager)
{
	t_philosopher	*target;
	int				index;

	index = 0;
	while (index < manager->config->philo_cnt)
	{
		target = &manager->philos[index];
		pthread_mutex_lock(&target->lock);
		target->in_process = false;
		pthread_mutex_unlock(&target->lock);
		index++;
	}
}
