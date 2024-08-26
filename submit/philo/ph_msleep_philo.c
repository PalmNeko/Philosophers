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
	struct timeval	after_time;
	struct timeval	now;

	msec_tv = ph_msectotimeval(msec);
	gettimeofday(&now, NULL);
	timeradd(&now, &msec_tv, &after_time);
	return (ph_tvsleep_until(&after_time, philo));
}
