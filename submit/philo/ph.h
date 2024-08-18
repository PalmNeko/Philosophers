/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:45:49 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 20:45:49 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_H
# define PH_H

# include <sys/time.h>
# include "ph_types.h"

int				ph_to_int(const char *str, int *num);
void			ph_print_error(const char *str);
int				ph_putstr(int fd, const char *str);
int				ph_main(t_manager *manager);
int				ph_print_log(struct timeval *start_tvp, t_log_info *info);
void			*ph_routine_philo(t_philosopher *philo);
void			ph_destroy_philosophers(t_philosopher *philos, int cnt);
int				ph_create_philo_threads(
					pthread_t *threads, t_philosopher *philos, int cnt);
void			*ph_routine_philo(t_philosopher *philo);

void			ph_destroy_queue(t_action_queue *queue);
t_action_queue	*ph_new_queue(int init_size);
int				ph_enqueue(
					t_action_queue *queue, int no, t_philo_action action);
int				ph_dequeue(t_action_queue *queue, t_log_info *info);
int				ph_enqueue_with_lock(
					t_action_queue *queue, int no, t_philo_action action);
int				ph_dequeue_with_lock(t_action_queue *queue, t_log_info *info);
t_action_queue	*ph_clone_queue(t_action_queue *queue);
void			ph_print_log_all_queue(
					struct timeval *from_tv, t_action_queue *queue);
void			*ph_routine_print(t_manager *manager);
int				ph_msleep(unsigned int msec, t_philosopher *manager);
void			ph_append_log(t_philosopher *philo, t_philo_action action);
void			ph_run_think(t_philosopher *philo);
void			ph_run_eat(t_philosopher *philo);
void			ph_run_sleep(t_philosopher *philo);
void			*ph_routine_update_manager(t_manager *manager);
struct timeval	ph_msectotimeval(unsigned int timesec);
bool			ph_is_alive(t_philosopher *philo);
int				ph_wait_once(struct timeval *nowtvp, struct timeval *endtvp);
int				ph_tvsleep_until(struct timeval *endtime, t_philosopher *philo);
int				ph_msleep_philo(unsigned int msec, t_philosopher *philo);
void			ph_wait_until_eatable(t_philosopher *philo);

#endif
