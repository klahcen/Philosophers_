/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:52:41 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/29 02:54:12 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	rest;

	i = 0;
	rest = 0;
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			rest = rest * 10 + (str[i] - 48);
		if (rest > INT_MAX)
			return (-1);
		i++;
	}
	return (rest);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
}

void	ft_free(t_philo **philo, int i, t_data *data)
{
	i = 0;
	if (!philo)
		return ;
	while (i < data->nbr_philo)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	ft_init_philos(t_philo *philo, t_data *data, int i)
{
	philo->id = i;
	philo->data = data;
	philo->nbr_rop_eat_philo = 0;
	philo->time_lst_eat = data->time_start;
}
