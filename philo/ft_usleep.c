/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:56:56 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/28 00:08:04 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	check_death(t_data *data)
{
	int	b;

	pthread_mutex_lock(&data->race);
	b = data->flag_die != 1;
	pthread_mutex_unlock(&data->race);
	return (b);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && check_death(data))
		usleep(500);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (philo->data->nbr_philo != 1)
	{
		ft_putmessenger("is eating", philo);
		pthread_mutex_lock(&philo->data->race1);
		philo->time_lst_eat = get_current_time();
		pthread_mutex_unlock(&philo->data->race1);
		ft_usleep(philo->data->tmie_eat, philo->data);
		pthread_mutex_lock(&philo->data->race2);
		philo->nbr_rop_eat_philo++;
		pthread_mutex_unlock(&philo->data->race2);
	}
}
