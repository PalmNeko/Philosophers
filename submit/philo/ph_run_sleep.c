/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:02:08 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/19 01:11:15 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	ph_run_sleep(t_philosopher *philo)
{
	ph_print_action(philo, PH_SLEEP);
	ph_msleep_philo((unsigned int)philo->manager->config->time_to_sleep, philo);
}
