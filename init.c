/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:36:01 by tbae              #+#    #+#             */
/*   Updated: 2023/09/20 13:11:21 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_info *info)
{
	int		idx;

	idx = 0;
	info->philo = calloc(sizeof(t_philo), info->nb_philo);
	if (info->philo == NULL)
		return (printf("Error : fail to malloc\n"), exit (EXIT_FAILURE));
	while (idx < info->nb_philo)
	{
		pthread_mutex_init(&info->philo[idx].fork, NULL);
		info->philo[idx].fork_left = &info->philo[idx].fork;
		pthread_mutex_init(&info->philo[idx].finished_mutex, NULL);
		idx++;
	}
	idx = 0;
	while (idx < info->nb_philo)
	{
		info->philo[idx].last_meal = info->time_start;
		if (idx == info->nb_philo - 1)
			info->philo[idx].fork_right = &info->philo[0].fork;
		else
			info->philo[idx].fork_right = &info->philo[idx + 1].fork;
		idx++;
	}
	return ;
}

int	ft_check_val(char *str, int val)
{
	int	dig;

	dig = 0;
	if (val < 0)
		dig++;
	if (val == 0 && ft_strncmp(str, "0", 1) != 0)
		return (0);
	if (val == 0)
		dig = 1;
	while (val != 0)
	{
		dig++;
		val /= 10;
	}
	if (dig == (int) ft_strlen(str))
		return (1);
	return (0);
}

int	check_arg(char **av, int ac, t_info *info)
{
	if (info->nb_philo <= 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep <= 0)
		return (1);
	if (!ft_check_val(av[1], info->nb_philo))
		return (1);
	if (!ft_check_val(av[2], info->time_to_die))
		return (1);
	if (!ft_check_val(av[3], info->time_to_eat))
		return (1);
	if (!ft_check_val(av[4], info->time_to_sleep))
		return (1);
	if (ac == 6 && !ft_check_val(av[5], info->max_eat))
		return (1);
	return (0);
}

void	init_info(t_info *info, char **av, int ac)
{
	info->nb_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		info->max_eat = atoi(av[5]);
		if (info->max_eat <= 0)
			return (printf("Error : Wrong number\n"), exit(EXIT_FAILURE));
	}
	else
		info->max_eat = -1;
	if (check_arg(av, ac, info))
		return (printf("Error : Wrong number\n"), exit(EXIT_FAILURE));
	info->dead = 0;
	info->time_start = gettime();
	info->id = 0;
	pthread_mutex_init(&info->dead_mutex, NULL);
	pthread_mutex_init(&info->id_mutex, NULL);
	pthread_mutex_init(&info->eat_mutex, NULL);
	pthread_mutex_init(&info->print, NULL);
	init_philo (info);
	return ;
}
