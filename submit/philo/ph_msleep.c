/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_busy_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:41:55 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 22:41:55 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "ph_types.h"
#include "ph_defs.h"

unsigned int	ph_timertomsc(struct timeval *tvp);
struct timeval	ph_msectotimeval(unsigned int timesec);
int				ph_wait_once(struct timeval *nowtvp, struct timeval *endtvp);
unsigned int	ph_calc_wait_time(struct timeval *subtvp);

int	ph_msleep(unsigned int msec, t_manager *manager)
{
	struct timeval	start;
	struct timeval	now;
	struct timeval	diff;
	struct timeval	endtime;

	gettimeofday(&start, NULL);
	diff = ph_msectotimeval(msec);
	timeradd(&start, &diff, &endtime);
	now = start;
	gettimeofday(&now, NULL);
	while(timercmp(&now, &endtime, <) && manager->in_process)
	{
		if (ph_wait_once(&now, &endtime) == -1)
			return (-1);
		gettimeofday(&now, NULL);
	}
	return (0);
}

/**
 * the usleep has accuracy so `usleep(sleep_time_usec - TIMER_ACCURACY_USEC)`
 */

int ph_wait_once(struct timeval *nowtvp, struct timeval *endtvp)
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

struct timeval	ph_msectotimeval(unsigned int timesec)
{
	struct timeval	tv;

	tv.tv_sec = timesec / 1000;
	tv.tv_usec = (timesec % 1000) * 1000;
	return (tv);
}
