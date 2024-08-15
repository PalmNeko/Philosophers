/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:18:58 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 17:18:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	think(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	take_fork(t_philosopher *philo, t_philosopher *taken_philo);
void	untake_fork(t_philosopher *philo, t_philosopher *taken_philo);
void	sleep(t_philosopher *philo);

void	*ph_routine_philo(t_philosopher *philo)
{
	int	cnt;

	cnt = 0;
	while (cnt < 10)
	{
		think(philo);
		eat(philo);
		sleep(philo);
		cnt++;
	}
	return (NULL);
}

void	think(t_philosopher *philo)
{
	ph_act_log(philo, PH_THINK);
}

void	eat(t_philosopher *philo)
{
	if (philo->no == 1)
	{
		take_fork(philo, &(philo->manager->philos)[(philo->no) % philo->manager->philo_cnt]);
		take_fork(philo, philo);
	}
	else
	{
		take_fork(philo, philo);
		take_fork(philo, &(philo->manager->philos)[(philo->no) % philo->manager->philo_cnt]);
	}
	ph_act_log(philo, PH_EAT);
	ph_msleep(philo->manager->time_to_eat);
	if (philo->no == 1)
	{
		untake_fork(philo, philo);
		untake_fork(philo, &(philo->manager->philos)[(philo->no) % philo->manager->philo_cnt]);
	}
	else
	{
		untake_fork(philo, &(philo->manager->philos)[(philo->no) % philo->manager->philo_cnt]);
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

void	sleep(t_philosopher *philo)
{
	ph_act_log(philo, PH_SLEEP);
	ph_msleep((unsigned int)philo->manager->time_to_sleep);
}
