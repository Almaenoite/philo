/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:41:05 by tbae              #+#    #+#             */
/*   Updated: 2023/09/19 23:06:46 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				count_meal;
	long			last_meal;
	int				finished;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_t		thread;
}	t_philo;

typedef struct s_info
{
	t_philo			*philo;
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	long			time_start;
	int				dead;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print;
}	t_info;

long	gettime(void);

void	ft_usleep(t_info *info, long ms);
void	print(t_info *info, int idx_philo, char *str);

void	*routine(void *void_philo);
void	init_info(t_info *info, char **argv, int argc);

void	check_end(t_info *info);
void	ft_clean(t_info *info, int nb_philo);

int		ft_atoi(const char *theString);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

int		check_max_eat(t_info *info, int idx_philo);
int		check_dead(void *void_info);

#endif
