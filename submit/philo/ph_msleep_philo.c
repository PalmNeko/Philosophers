/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_msleep_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:39:15 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/16 16:39:15 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <sys/time.h>

int	ph_msleep_philo(unsigned int msec, t_philosopher *philo)
{
	struct timeval	msec_tv;
	struct timeval	die_time;
	struct timeval	after_time;
	struct timeval	now;

	if (philo->is_eating == true)
		return (ph_msleep(msec, philo));
	msec_tv = ph_msectotimeval(msec);
	gettimeofday(&now, NULL);
	timeradd(&philo->last_eat, &philo->manager->config->die_tv, &die_time);
	timeradd(&now, &msec_tv, &after_time);
	if (timercmp(&die_time, &after_time, <))
		return (ph_tvsleep_until(&die_time, philo));
	else
		return (ph_tvsleep_until(&after_time, philo));
	return (0);
}
