/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:01:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 13:39:55 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	take_fork(t_philosopher *philo, t_philosopher *taken_philo);
void	untake_fork(t_philosopher *philo, t_philosopher *taken_philo);

void	ph_run_eat(t_philosopher *philo)
{
	int				right_no;
	t_philosopher	*right_philo;

	right_no = (philo->no) % philo->manager->philo_cnt;
	right_philo = &(philo->manager->philos)[right_no];
	if (philo->no == 1)
	{
		take_fork(philo, right_philo);
		take_fork(philo, philo);
		untake_fork(philo, philo);
		untake_fork(philo, right_philo);
	}
	else
	{
		take_fork(philo, philo);
		take_fork(philo, right_philo);
		ph_act_log(philo, PH_EAT);
		ph_msleep(philo->manager->time_to_eat);
		untake_fork(philo, right_philo);
		untake_fork(philo, philo);
	}
}

void	take_fork(t_philosopher *philo, t_philosopher *taken_philo)
{
	pthread_mutex_lock(&taken_philo->fork);
	ph_act_log(philo, PH_PICK_UP);
}

void	untake_fork(t_philosopher *philo, t_philosopher *taken_philo)
{
	(void)philo;
	pthread_mutex_unlock(&taken_philo->fork);
}
