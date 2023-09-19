/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:21:23 by tbae              #+#    #+#             */
/*   Updated: 2023/09/19 22:39:57 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep_eat(t_info *info, int idx_philo, int *count)
{
	pthread_mutex_unlock(&info->dead_mutex);
	ft_usleep(info, info->time_to_eat);
	pthread_mutex_lock(&info->eat_mutex);
	info->philo[idx_philo].last_meal = gettime();
	pthread_mutex_unlock(&info->eat_mutex);
	(*count)++;
	if (*count == info->max_eat)
	{
		pthread_mutex_lock(&info->philo[idx_philo].finished_mutex);
		info->philo[idx_philo].finished = 1;
		pthread_mutex_unlock(&info->philo[idx_philo].finished_mutex);
	}
	pthread_mutex_lock(&info->dead_mutex);
}

void	ft_eat_sleep_think(t_info *info, int idx_philo, int *count)
{
	print(info, idx_philo, "is eating\n");
	pthread_mutex_lock(&info->dead_mutex);
	if (info->dead != 1)
		ft_sleep_eat(info, idx_philo, count);
	pthread_mutex_unlock(&info->dead_mutex);
	pthread_mutex_unlock(info->philo[idx_philo].fork_left);
	pthread_mutex_unlock(info->philo[idx_philo].fork_right);
	if (check_max_eat(info, 0) == 0)
	{
		print(info, idx_philo, "is sleeping\n");
		ft_usleep(info, info->time_to_sleep);
		usleep(100);
		print(info, idx_philo, "is thinking\n");
	}
}

void	nb_odd(t_info *info, int idx_philo)
{
	pthread_mutex_lock(info->philo[idx_philo].fork_left);
	print(info, idx_philo, "has taken a fork\n");
	pthread_mutex_lock(info->philo[idx_philo].fork_right);
	print(info, idx_philo, "has taken a fork\n");
}

int	nb_even(t_info *info, int idx_philo)
{
	pthread_mutex_lock(info->philo[idx_philo].fork_right);
	print (info, idx_philo, "has taken a fork\n");
	if (info->philo[idx_philo].fork_right == info->philo[idx_philo].fork_left)
	{
		pthread_mutex_unlock(info->philo[idx_philo].fork_right);
		return (1);
	}
	pthread_mutex_lock(info->philo[idx_philo].fork_left);
	print (info, idx_philo, "has taken a fork\n");
	return (0);
}

void	*routine(void *void_info)
{
	t_info	*info;
	int		count;
	int		idx_philo;

	info = void_info;
	count = 0;
	pthread_mutex_lock (&info->id_mutex);
	idx_philo = info->id++;
	pthread_mutex_unlock (&info->id_mutex);
	if (!(idx_philo % 2 == 0))
		ft_usleep(info, info->time_to_eat * 0.25);
	while (check_dead(void_info) == 0 && count != info->max_eat
		&& info->time_to_die != 0)
	{
		if (idx_philo % 2 == 0)
		{
			if (nb_even(info, idx_philo) == 1)
				return (0);
		}
		else
			nb_odd(info, idx_philo);
		ft_eat_sleep_think(info, idx_philo, &count);
		usleep(100);
	}
	return (0);
}
