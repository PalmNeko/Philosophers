/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:02:08 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 11:02:54 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	ph_sleep(t_philosopher *philo)
{
	ph_act_log(philo, PH_SLEEP);
	ph_msleep((unsigned int)philo->manager->time_to_sleep);
}
