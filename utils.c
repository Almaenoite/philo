/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 05:41:10 by tbae              #+#    #+#             */
/*   Updated: 2023/09/19 22:32:15 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(void *void_info)
{
	t_info	*info;

	info = (t_info *) void_info;
	pthread_mutex_lock(&info->dead_mutex);
	if (info->dead == 1)
	{
		pthread_mutex_unlock(&info->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->dead_mutex);
	return (0);
}

void	ft_clean(t_info *info, int nb_philo)
{
	int	idx;

	idx = 0;
	while (idx < nb_philo)
	{
		pthread_join(info->philo[idx].thread, NULL);
		idx++;
	}
	free(info->philo);
}

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_info *info, int idx_philo, char *str)
{
	long	time;

	time = gettime() - info->time_start;
	pthread_mutex_lock(&info->dead_mutex);
	if (info->dead == 1)
	{
		pthread_mutex_unlock(&info->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&info->dead_mutex);
	if (check_max_eat(info, 0) == 1)
		return ;
	pthread_mutex_lock(&info->print);
	printf("%ld %d %s", time, idx_philo + 1, str);
	pthread_mutex_unlock(&info->print);
}

void	ft_usleep(t_info *info, long ms)
{
	long	begin;

	begin = gettime();
	pthread_mutex_lock(&info->dead_mutex);
	while (gettime() - begin < ms && info->dead != 1
		&& check_max_eat(info, 0) == 0)
	{
		pthread_mutex_unlock(&info->dead_mutex);
		usleep(100);
		pthread_mutex_lock(&info->dead_mutex);
	}
	pthread_mutex_unlock(&info->dead_mutex);
}
