/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:01:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/18 12:33:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <unistd.h>

void			take_fork(t_philosopher *philo);
void			untake_fork(t_philosopher *philo);
t_philosopher	*get_take_first_fork_philo(t_philosopher *philo);
t_philosopher	*get_take_second_fork_philo(t_philosopher *philo);

void	ph_run_eat(t_philosopher *philo)
{
	ph_wait_until_eatable(philo);
	take_fork(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating_order = false;
	pthread_mutex_unlock(&philo->lock);
	ph_append_log(philo, PH_EAT);
	philo->is_eating = true;
	ph_msleep_philo(philo->manager->time_to_eat, philo);
	untake_fork(philo);
	philo->eat_cnt += 1;
	gettimeofday(&philo->last_eat, NULL);
	philo->is_eating = false;
	usleep(0);
}

t_philosopher	*get_take_first_fork_philo(t_philosopher *philo)
{
	int				right_no;
	t_philosopher	*first_take_philo;
	t_philosopher	*right_fork_philo;

	right_no = (philo->no) % philo->manager->philo_cnt;
	right_fork_philo = &(philo->manager->philos)[right_no];
	if (philo->no % 2 == 1)
		first_take_philo = right_fork_philo;
	else
		first_take_philo = philo;
	return (first_take_philo);
}

t_philosopher	*get_take_second_fork_philo(t_philosopher *philo)
{
	int				right_no;
	t_philosopher	*second_take_philo;
	t_philosopher	*right_fork_philo;

	right_no = (philo->no) % philo->manager->philo_cnt;
	right_fork_philo = &(philo->manager->philos)[right_no];
	if (philo->no % 2 == 1)
		second_take_philo = philo;
	else
		second_take_philo = right_fork_philo;
	return (second_take_philo);
}

void	take_fork(t_philosopher *philo)
{
	t_philosopher	*first_take_philo;
	t_philosopher	*second_take_philo;

	first_take_philo = get_take_first_fork_philo(philo);
	second_take_philo = get_take_second_fork_philo(philo);
	pthread_mutex_lock(&first_take_philo->fork);
	ph_append_log(philo, PH_PICK_UP);
	pthread_mutex_lock(&second_take_philo->fork);
	ph_append_log(philo, PH_PICK_UP);
}

void	untake_fork(t_philosopher *philo)
{
	t_philosopher	*first_take_philo;
	t_philosopher	*second_take_philo;

	first_take_philo = get_take_first_fork_philo(philo);
	second_take_philo = get_take_second_fork_philo(philo);
	pthread_mutex_unlock(&first_take_philo->fork);
	pthread_mutex_unlock(&second_take_philo->fork);
}
