/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:00:14 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/05 23:13:07 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_function(void *philo)
{
	t_list	*tmp;

	tmp = (t_list *)philo;
	while (tmp->is_alive)
	{
		if (tmp->n != tmp->t->time_ph_to_eat)
		{
			pthread_mutex_lock(&tmp->fork);
			ft_print(0, tmp);
			pthread_mutex_lock(&tmp->next->fork);
			ft_print(0, tmp);
			ft_print(1, tmp);
			ft_sleep(tmp->t->time_to_eat);
			tmp->end += ft_time() - tmp->t->time;
			pthread_mutex_unlock(&tmp->fork);
			pthread_mutex_unlock(&tmp->next->fork);
			tmp->n++;
			ft_print(2, tmp);
			ft_sleep(tmp->t->time_to_sleep);
			ft_print(3, tmp);
		}
		if (check_philo_eating(tmp))
			tmp->t->eating = 0;
	}
	return (0);
}

void	ft_print2(int a, t_list *tmp)
{
	if (a == 3 && tmp->t->lock)
	{
		pthread_mutex_lock(&tmp->t->print);
		printf("%ld %d is thinking\n",
			ft_time() - tmp->t->time, tmp->index);
		pthread_mutex_unlock(&tmp->t->print);
	}
}

void	ft_print(int a, t_list *tmp)
{
	if (a == 0 && tmp->t->lock)
	{
		pthread_mutex_lock(&tmp->t->print);
		printf("%ld %d has taken a fork\n",
			ft_time() - tmp->t->time, tmp->index);
		pthread_mutex_unlock(&tmp->t->print);
	}
	if (a == 1 && tmp->t->lock)
	{
		pthread_mutex_lock(&tmp->t->print);
		printf("%ld %d is eating\n",
			ft_time() - tmp->t->time, tmp->index);
		pthread_mutex_unlock(&tmp->t->print);
	}
	if (a == 2 && tmp->t->lock)
	{
		pthread_mutex_lock(&tmp->t->print);
		printf("%ld %d is sleeping\n",
			ft_time() - tmp->t->time, tmp->index);
		pthread_mutex_unlock(&tmp->t->print);
	}
	ft_print2(a, tmp);
}

void	killing_threads(t_list *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->t->print);
	if (philo->is_alive)
		printf("%ld %d died\n",
			ft_time() - philo->t->time, philo->index);
	pthread_mutex_unlock(&philo->t->print);
	while (i < philo->t->n_philo)
	{
		philo->is_alive = 0;
		philo = philo->next;
		i++;
	}
	destroy_mutex(philo);
}
