/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_tvsleep_until.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:15:44 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/18 12:17:15 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <sys/time.h>

int	ph_philo_tvsleep_until(struct timeval *endtime, t_philosopher *philo)
{
	struct timeval	now;
	bool			in_progress;

	gettimeofday(&now, NULL);
	while(timercmp(&now, endtime, <))
	{
		pthread_mutex_lock(&philo->lock);
		in_progress = philo->in_process;
		pthread_mutex_unlock(&philo->lock);
		if (in_progress == false)
			return (0);
		if (ph_wait_once(&now, endtime) == -1)
			return (-1);
		gettimeofday(&now, NULL);
	}
	return (0);
}
