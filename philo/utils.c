/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:07 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/05 19:42:09 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_time(void)
{
	long int			time;
	struct timeval		c_time;

	gettimeofday(&c_time, NULL);
	time = ((c_time.tv_sec * 1000) + (c_time.tv_usec / 1000));
	return (time);
}

void	ft_sleep(int time)
{
	int			c;
	long int	a;

	c = 0;
	a = ft_time();
	while (c < time)
	{	
		c = ft_time() - a;
		usleep(100);
	}
}

int	check_philo_eating(t_list *philo)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (i < philo->t->n_philo)
	{
		if (philo->n == philo->t->time_ph_to_eat)
			x++;
		i++;
		philo = philo->next;
	}
	if (x == philo->t->n_philo)
		return (1);
	else
		return (0);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!ft_is_digit(str))
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}
