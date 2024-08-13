/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:40:42 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 19:40:42 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_TYPES_H
# define PH_TYPES_H

#include <sys/time.h>
#include <pthread.h>

typedef struct s_action_queue t_action_queue;

typedef struct	s_ph_common
{
	struct timeval	start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	t_action_queue	*action_queue;
}	t_manager;

typedef struct s_philosopher
{
	int				no;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	pthread_mutex_t fork;
	t_manager		*common;
}	t_philosopher;

typedef struct s_philo_thread_arg
{
	t_philosopher	*philos;

	int				no;
}	t_philo_thread_arg;

typedef enum e_philo_action
{
	PH_EAT,
	PH_PICK_UP,
	PH_SLEEP,
	PH_THINK,
	PH_DIE,
}	t_philo_action;

typedef struct s_log_info
{
	int				no;
	struct timeval	tv;
	t_philo_action	action;
}	t_log_info;

struct s_action_queue
{
	t_log_info		*infos;
	int				top;
	int				bottom;
	int				size;
	int				max_size;
	pthread_mutex_t	lock;
};

#endif
