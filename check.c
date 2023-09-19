/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:56:39 by tbae              #+#    #+#             */
/*   Updated: 2023/09/19 22:01:54 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_info *info, int idx_philo)
{
	long	time;

	time = gettime() - info->time_start;
	pthread_mutex_lock(&info->print);
	printf("%ld %d %s", time,
		idx_philo + 1, "has died\n");
	pthread_mutex_unlock(&info->print);
}

int	check_death(t_info *info, int idx_philo)
{
	long	eating;

	while (idx_philo < info->nb_philo)
	{
		pthread_mutex_lock(&info->eat_mutex);
		eating = gettime() - info->philo[idx_philo].last_meal;
		pthread_mutex_unlock(&info->eat_mutex);
		if (eating > info->time_to_die && info->philo[idx_philo].finished != 1)
		{
			pthread_mutex_lock(&info->dead_mutex);
			info->dead = 1;
			pthread_mutex_unlock(&info->dead_mutex);
			print_dead(info, idx_philo);
			return (1);
		}
		idx_philo++;
	}
	return (0);
}

int	check_max_eat(t_info *info, int idx_philo)
{
	while (idx_philo < info->nb_philo)
	{
		pthread_mutex_lock(&info->philo[idx_philo].finished_mutex);
		if (info->philo[idx_philo].finished != 1)
		{
			pthread_mutex_unlock(&info->philo[idx_philo].finished_mutex);
			return (0);
		}
		pthread_mutex_unlock(&info->philo[idx_philo].finished_mutex);
		idx_philo++;
	}
	return (1);
}

void	check_end(t_info *info)
{
	int		idx_philo;

	idx_philo = 0;
	while (1)
	{
		if (check_max_eat(info, idx_philo) == 1)
			return ;
		if (check_death(info, idx_philo) == 1)
			return ;
		usleep(100);
	}
	return ;
}
