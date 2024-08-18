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
#include "ph.h"
#include "ph_defs.h"

int	ph_msleep(unsigned int msec, t_philosopher *philo)
{
	struct timeval	start;
	struct timeval	diff;
	struct timeval	endtime;

	gettimeofday(&start, NULL);
	diff = ph_msectotimeval(msec);
	timeradd(&start, &diff, &endtime);
	return (ph_tvsleep_until(&endtime, philo));
}
