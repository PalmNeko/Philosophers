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

typedef struct s_philosopher
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;

}	t_philosopher;

#endif
