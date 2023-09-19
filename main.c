/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:37:01 by tbae              #+#    #+#             */
/*   Updated: 2023/09/19 13:51:15 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->nb_philo)
	{
		if (pthread_create(&info->philo[idx].thread, NULL,
				&routine, info) == 1)
			return (printf("Error : thread not create"),
				ft_clean(info, idx), exit(EXIT_SUCCESS));
		idx++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!(argc >= 5 && argc <= 6))
		return (printf("Error : Wrong number of arguments\n"));
	init_info(&info, argv, argc);
	start_philo(&info);
	check_end(&info);
	ft_clean (&info, info.nb_philo);
}
