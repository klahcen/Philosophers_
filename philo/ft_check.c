/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:36:41 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/29 02:36:59 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_next_check(int i, t_data *ddata, t_philo **philo)
{
	while (i < philo[0]->data->nbr_philo)
	{
		pthread_mutex_lock(&ddata->race1);
		if ((ddata->time_die + philo[i]->time_lst_eat) <= get_current_time())
		{
			pthread_mutex_lock(&ddata->printf);
			pthread_mutex_lock(&ddata->race);
			ddata->flag_die = 1;
			pthread_mutex_unlock(&ddata->race);
			printf("%lu	%d	%s\n", get_current_time() \
						- philo[i]->data->time_start, 1 + i, "died");
			pthread_mutex_unlock(&ddata->printf);
			pthread_mutex_unlock(&ddata->race1);
			return (-1);
		}
		pthread_mutex_unlock(&ddata->race1);
		i++;
	}
	return (0);
}

void	*ft_check(void *data)
{
	t_data	*ddata;
	t_philo	**philo;
	int		i;

	ddata = (t_data *)data;
	philo = ddata->philo;
	while (1)
	{
		pthread_mutex_lock(&ddata->race);
		if (ddata->flag_die == 1)
		{
			pthread_mutex_unlock(&ddata->race);
			break ;
		}
		pthread_mutex_unlock(&ddata->race);
		i = 0;
		if (ft_next_check(i, ddata, philo) == -1)
			break ;
	}
	return (NULL);
}
