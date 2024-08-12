/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:09:23 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 21:09:23 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

t_philosopher	*ph_generate_philosophers(
					t_philosopher *template,
					int philo_cnt,
					t_ph_common *common);
void			*ph_philo_routine(t_philosopher *philo);
int				ph_create_philo_threads(
					pthread_t *threads, t_philosopher *philos, int cnt);
void			ph_destroy_philosophers(t_philosopher *philos, int cnt);

int	ph_main(int philo_cnt, t_philosopher *template)
{
	t_philosopher	*philos;
	pthread_t		*threads;
	t_ph_common		common;
	int				index;
	int				error;

	philos = ph_generate_philosophers(template, philo_cnt, &common);
	if (philos == NULL)
		return (ENOMEM);
	gettimeofday(&common.start, NULL);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * philo_cnt);
	if (threads == NULL)
		return (ph_destroy_philosophers(philos, philo_cnt), ENOMEM);
	error = 0;
	error = ph_create_philo_threads(threads, philos, philo_cnt);
	if (error != 0)
		return (ph_destroy_philosophers(philos, philo_cnt), free(threads), error);
	index = 0;
	while (index < philo_cnt)
	{
		if (error == 0)
			error = pthread_join(threads[index], NULL);
		else
			error = pthread_detach(threads[index]);
		index++;
	}
	return (ph_destroy_philosophers(philos, philo_cnt), free(threads), error);
}

t_philosopher	*ph_generate_philosophers(
					t_philosopher *template,
					int philo_cnt,
					t_ph_common *common)
{
	t_philosopher	*philos;
	int				index;

	philos = (t_philosopher *)malloc(sizeof(t_philosopher) * philo_cnt);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, sizeof(t_philosopher *) * philo_cnt);
	index = 0;
	while (index < philo_cnt)
	{
		philos[index] = (t_philosopher){
			.time_to_die = template->time_to_die,
			.time_to_eat = template->time_to_eat,
			.time_to_sleep = template->time_to_sleep,
			.must_eat_times = template->time_to_sleep,
			.common = common,
			.no = index + 1,
		};
		pthread_mutex_init(&philos[index].fork, NULL);
		index++;
	}
	return (philos);
}

void	ph_destroy_philosophers(t_philosopher *philos, int cnt)
{
	int	index;

	index = 0;
	while (index < cnt)
	{
		pthread_mutex_destroy(&philos[index].fork);
		index++;
	}
	free(philos);
	return ;
}

int	ph_create_philo_threads(pthread_t *threads, t_philosopher *philos, int cnt)
{
	int	index;
	int	error;

	index = 0;
	while (index < cnt)
	{
		error = 0;
		error = pthread_create(&threads[index],
				NULL,
				(void *(*)(void *))ph_philo_routine,
				&philos[index]);
		if (error != 0)
		{
			index -= 1;
			while (index > 0)
				pthread_detach(threads[index--]);
			return (error);
		}
		index++;
	}
	return (0);
}

void	*ph_philo_routine(t_philosopher *philo)
{
	ph_logging(&philo->common->start, philo->no, PH_DIE);
	return (NULL);
}
