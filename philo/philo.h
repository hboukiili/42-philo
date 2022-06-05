/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:09:21 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/05 23:13:44 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct philo
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_ph_to_eat;
	long int		time;
	int				lock;
	int				eating;
	pthread_mutex_t	print;
}	t_philo;

typedef struct list
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				index;
	int				is_alive;
	long int		end;
	t_philo			*t;
	int				n;
	struct list		*next;
}	t_list;

int			check_philo_eating(t_list *philo);
long int	ft_time(void);
void		ft_sleep(int time);
void		add_last(t_list *tmp, t_list **philo, int i);
void		ft_print(int a, t_list *tmp);
void		ft_eat(t_list *tmp, int time);
int			ft_is_digit(char *str);
int			ft_atoi(char *str);
t_list		*creation_list(int index, t_philo *t, int x);
void		destroy_mutex(t_list *philo);
void		ft_print(int a, t_list *tmp);
void		*philo_function(void *philo);
void	killing_threads(t_list *philo);

#endif