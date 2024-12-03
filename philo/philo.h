/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:31:24 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/29 02:53:52 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nbr_philo;
	pthread_t		moni;
	size_t			time_die;
	size_t			tmie_eat;
	size_t			tmie_sleep;
	int				nbr_rop;
	int				nbr_rop_eat_all_philo;
	int				all_philo_eat;
	size_t			time_start;
	int				flag_die;
	pthread_mutex_t	*fork;
	pthread_mutex_t	race;
	pthread_mutex_t	race1;
	pthread_mutex_t	race2;
	pthread_mutex_t	race3;
	pthread_mutex_t	printf;
	pthread_mutex_t	lock_moni;
	struct s_philo	**philo;
}					t_data;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	size_t			time_lst_eat;
	int				nbr_rop_eat_philo;
	t_data			*data;
}					t_philo;

int					ft_atoi(char *str);
void				ft_putstr(char *str);
t_data				*ft_danedata(t_data *data, int ac, char **av);
int					ft_usleep(size_t milliseconds, t_data *data);
void				ft_execution(t_data *data);
size_t				get_current_time(void);
void				ft_putmessenger(char *str, t_philo *philo);
void				ft_init_mutex(t_data *data);
void				ft_mutex_lock(t_philo *philo);
void				ft_init_philos(t_philo *philo, t_data *data, int i);
void				ft_eat(t_philo *philo);
void				ft_free(t_philo **philo, int i, t_data *data);
void				ft_next_main(t_data *data);
int					ft_next_check(int i, t_data *ddata, t_philo **philo);
void				*ft_check(void *data);
#endif