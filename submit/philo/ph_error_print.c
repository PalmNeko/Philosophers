/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:56:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 20:56:51 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ph_error_print(const char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
		size++;
	write(2, str, size);
	return ;
}
