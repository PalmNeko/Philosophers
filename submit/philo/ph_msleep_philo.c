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
#include "ph_defs.h"
#include <sys/time.h>
#include <unistd.h>

struct timeval	ph_msectotimeval(unsigned int timesec);
int				ph_tvsleep_until(struct timeval *endtime, t_philosopher *philo);
int				ph_wait_once(struct timeval *nowtvp, struct timeval *endtvp);
unsigned int	ph_calc_wait_time(struct timeval *subtvp);

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

int	ph_tvsleep_until(struct timeval *endtime, t_philosopher *philo)
{
	struct timeval	now;
	bool			in_progress;

	gettimeofday(&now, NULL);
	while (timercmp(&now, endtime, <))
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

/**
 * the usleep has accuracy so `usleep(sleep_time_usec - TIMER_ACCURACY_USEC)`
 */
int	ph_wait_once(struct timeval *nowtvp, struct timeval *endtvp)
{
	struct timeval	sub;
	unsigned int	sleep_time_usec;

	if (timercmp(nowtvp, endtvp, <))
	{
		timersub(endtvp, nowtvp, &sub);
		sleep_time_usec = ph_calc_wait_time(&sub);
		return (usleep(sleep_time_usec));
	}
	return (0);
}

/**
 * TODO: If remove sleep_time_usec variable more fast than no-remove one,
 * you should remove it.
 */
unsigned int	ph_calc_wait_time(struct timeval *subtvp)
{
	unsigned int	sleep_time_usec;

	if (subtvp->tv_sec >= 2)
		sleep_time_usec = 1000000 + TIMER_ACCURACY_USEC;
	else
		sleep_time_usec = subtvp->tv_sec * 1000000 + subtvp->tv_usec;
	if (sleep_time_usec > 1000000 + TIMER_ACCURACY_USEC)
		sleep_time_usec = 1000000;
	else if (sleep_time_usec > TIMER_ACCURACY_USEC)
		sleep_time_usec = sleep_time_usec - TIMER_ACCURACY_USEC;
	else
		sleep_time_usec = 0;
	return (sleep_time_usec);
}
