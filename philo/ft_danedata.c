/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_danedata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:16:52 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/29 02:56:43 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ft_check_arg(t_data *data, int ac, char **av)
{
	if (ac == 6 && (ft_atoi(av[5]) <= 0 || ft_atoi(av[5]) > INT_MAX))
		return (ft_putstr("you should give nbr_rop > 0  && < INT_MAX "), NULL);
	if (data->time_die < 60 || data->time_die > INT_MAX)
		return (ft_putstr("you should give time_to_die > 60  && < INT_MAX "),
			NULL);
	if (data->tmie_eat < 60 || data->tmie_eat > INT_MAX)
		return (ft_putstr("you should give time_to_eat > 60  && < INT_MAX "),
			NULL);
	if (data->tmie_sleep < 60 || data->tmie_sleep > INT_MAX)
		return (ft_putstr("you should give time_to_sleep > 60  && < INT_MAX "),
			NULL);
	return (data);
}

t_data	*ft_danedata(t_data *data, int ac, char **av)
{
	data->flag_die = 0;
	data->nbr_philo = ft_atoi(av[1]);
	if (data->nbr_philo > 200 || data->nbr_philo <= 0)
		return (ft_putstr("you should give number philo ]0,200] "), NULL);
	data->time_die = ft_atoi(av[2]);
	data->tmie_eat = ft_atoi(av[3]);
	data->tmie_sleep = ft_atoi(av[4]);
	data->nbr_rop_eat_all_philo = 0;
	data->all_philo_eat = 0;
	data->nbr_rop = -1;
	if (ac == 6)
		data->nbr_rop = ft_atoi(av[5]);
	data->fork = malloc(data->nbr_philo * sizeof(pthread_mutex_t));
	if (!data->fork)
		return (NULL);
	if (!ft_check_arg(data, ac, av))
	{
		free(data->fork);
		free(data);
		return (NULL);
	}
	return (ft_check_arg(data, ac, av));
}

void	ft_putmessenger(char *str, t_philo *philo)
{
	int	id;

	id = philo->id + 1;
	pthread_mutex_lock(&philo->data->printf);
	pthread_mutex_lock(&philo->data->race);
	if (philo->data->flag_die == 1)
	{
		pthread_mutex_unlock(&philo->data->race);
		pthread_mutex_unlock(&philo->data->printf);
		return ;
	}
	pthread_mutex_unlock(&philo->data->race);
	printf("%lu	%d	%s\n", get_current_time() - philo->data->time_start, id, \
				str);
	pthread_mutex_unlock(&philo->data->printf);
}

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->race, NULL);
	pthread_mutex_init(&data->printf, NULL);
	pthread_mutex_init(&data->race1, NULL);
	pthread_mutex_init(&data->race2, NULL);
	pthread_mutex_init(&data->race3, NULL);
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

void	ft_mutex_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->id]);
	ft_putmessenger("has taken a fork", philo);
	if ((philo->id + 1) % philo->data->nbr_philo != philo->id)
	{
		pthread_mutex_lock(&philo->data->fork[(philo->id + 1)
			% philo->data->nbr_philo]);
		ft_putmessenger("has taken a fork", philo);
	}
}
