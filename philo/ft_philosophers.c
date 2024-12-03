/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:11:36 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/29 02:39:01 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_checkrop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->race2);
	if (philo->nbr_rop_eat_philo == philo->data->nbr_rop)
		philo->data->all_philo_eat = 1;
	pthread_mutex_unlock(&philo->data->race2);
}

int	ft_sleep(t_philo *philo)
{
	ft_eat(philo);
	pthread_mutex_unlock(&philo->data->fork[philo->id]);
	if ((philo->id + 1) % philo->data->nbr_philo != philo->id)
		pthread_mutex_unlock(&philo->data->fork[(philo->id + 1)
			% philo->data->nbr_philo]);
	if (philo->nbr_rop_eat_philo == philo->data->nbr_rop)
		return (-1);
	if (philo->data->nbr_philo != 1)
	{
		ft_putmessenger("is sleeping", philo);
		ft_usleep(philo->data->tmie_sleep, philo->data);
		ft_putmessenger("is thinking", philo);
		if ((get_current_time() - philo->time_lst_eat) >= philo->data->time_die)
			ft_usleep(philo->data->time_die / 2, philo->data);
	}
	return (0);
}

void	*ft_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 != 0)
		ft_usleep(60, philo->data);
	while (1)
	{
		pthread_mutex_lock(&philo->data->race);
		if (philo->data->flag_die == 1)
		{
			pthread_mutex_unlock(&philo->data->race);
			break ;
		}
		pthread_mutex_unlock(&philo->data->race);
		ft_mutex_lock(philo);
		if (philo->data->nbr_philo == 1)
		{
			ft_usleep(philo->data->time_die, philo->data);
			ft_putmessenger("died", philo);
			break ;
		}
		if (ft_sleep(philo) == -1)
			break ;
	}
	return (NULL);
}

void	ft_execution(t_data *data)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = malloc(data->nbr_philo * sizeof(t_philo *));
	if (!philo)
		return ;
	while (++i < data->nbr_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return ;
	}
	ft_init_mutex(data);
	i = -1;
	data->time_start = get_current_time();
	while (++i < data->nbr_philo)
	{
		ft_init_philos(philo[i], data, i);
		pthread_create(&philo[i]->philo, NULL, ft_routine, philo[i]);
	}
	data->philo = philo;
	pthread_create(&data->moni, NULL, ft_check, data);
	ft_next_main(data);
	ft_free(philo, i, data);
}
