/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:33:08 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/29 02:54:29 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_next_parss_arg(int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			ft_putstr("negative number, you should give positive number\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_next1_parss_arg(int i, int j, char **av)
{
	while (av[i][j])
	{
		if (av[i][j] < '0' || av[i][j] > '9')
		{
			ft_putstr("your agr not correct\n");
			return (-1);
		}
		j++;
	}
	return (0);
}

int	ft_parss_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ft_next_parss_arg(ac, av) == -1)
		return (-1);
	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] == '+')
		{
			j++;
			if (av[i][j] == '\0')
			{
				ft_putstr("your agr not correct\n");
				return (-1);
			}
		}
		if (ft_next1_parss_arg(i, j, av) == -1)
			return (-1);
	}
	return (0);
}

void	ft_next_main(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_join(data->philo[i]->philo, NULL);
	pthread_mutex_lock(&data->race);
	data->flag_die = 1;
	pthread_mutex_unlock(&data->race);
	pthread_join(data->moni, NULL);
	pthread_mutex_destroy(&data->race1);
	pthread_mutex_destroy(&data->race2);
	pthread_mutex_destroy(&data->race3);
	pthread_mutex_destroy(&data->lock_moni);
	pthread_mutex_destroy(&data->printf);
	pthread_mutex_destroy(&data->race);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = NULL;
	if (ac != 5 && ac != 6)
	{
		ft_putstr("you should give 5 or 6 arg number_of_philosophers time_to_die \
time_to_eat time_to_sleep or \n");
		return (0);
	}
	if (ft_parss_arg(ac, av) == -1)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data = ft_danedata(data, ac, av);
	if (!data)
		return (0);
	ft_execution(data);
	i = 0;
	free(data->fork);
	free(data);
	return (0);
}
