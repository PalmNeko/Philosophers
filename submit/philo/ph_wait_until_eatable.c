/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_wait_until_eatable.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:47:57 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/17 17:47:57 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>
#include <unistd.h>

void	ph_wait_until_eatable(t_philosopher *philo)
{
	t_manager	*manager;
	bool		is_eatable;
	bool		in_progress;

	manager = philo->manager;
	while (1)
	{
		pthread_mutex_lock(&manager->lock);
		is_eatable = philo->eat_cnt <= manager->all_eat_times / manager->philo_cnt;
		in_progress = manager->in_process;
		pthread_mutex_unlock(&manager->lock);
		if (is_eatable == true || in_progress == false)
			return ;
		usleep(0);
	}
}
