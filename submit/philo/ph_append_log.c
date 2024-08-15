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

void	ph_append_log(t_philosopher *philo, t_philo_action action)
{
	t_manager	*manager;
	bool		in_progress;

	manager = philo->manager;
	pthread_mutex_lock(&manager->lock);
	in_progress = manager->in_process;
	pthread_mutex_unlock(&manager->lock);
	if (in_progress == false)
		return ;
	ph_enqueue_with_lock(philo->manager->action_queue, philo->no, action);
}
