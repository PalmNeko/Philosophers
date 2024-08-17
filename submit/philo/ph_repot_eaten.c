/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_repot_eaten.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:51:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/17 17:51:13 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>

void	ph_report_eaten(t_philosopher *philo)
{
	t_manager *manager;

	manager = philo->manager;
	philo->eat_cnt += 1;
	pthread_mutex_lock(&manager->lock);
	manager->all_eat_times += 1;
	pthread_mutex_unlock(&manager->lock);
	return ;
}
