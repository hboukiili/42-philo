/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:00:21 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/05 23:14:31 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo2(char **av, t_philo *t)
{
	t->time_to_sleep = ft_atoi(av[4]);
	if (t->time_to_sleep == -1)
	{
		write(2, "error\n", 6);
		return (0);
	}
	if (av[5] != '\0')
	{
		t->time_ph_to_eat = ft_atoi(av[5]);
		if (t->time_ph_to_eat == -1)
		{
			write(2, "error\n", 6);
			return (0);
		}
	}
	if (av[5] == '\0')
		t->time_ph_to_eat = -1;
	t->eating = 1;
	t->lock = 1;
	return (t);
}

t_philo	*init_philo(char **av, t_philo *t)
{
	t->n_philo = ft_atoi(av[1]);
	if (t->n_philo == 0 || t->n_philo == -1)
	{
		write(2, "error\n", 6);
		return (0);
	}
	t->time_to_die = ft_atoi(av[2]);
	if (t->time_to_die == -1)
	{
		write(2, "error\n", 6);
		return (0);
	}
	t->time_to_eat = ft_atoi(av[3]);
	if (t->time_to_eat == -1)
	{
		write(2, "error\n", 6);
		return (0);
	}
	t = init_philo2(av, t);
	if (t == NULL)
		return (NULL);
	return (t);
}

void	creation_of_threads(t_list *philo)
{
	int	i;

	i = 0;
	while (i < philo->t->n_philo)
	{
		pthread_mutex_init(&philo->fork, NULL);
		philo = philo->next;
		i++;
	}
	i = 0;
	pthread_mutex_init(&philo->t->print, NULL);
	while (i < philo->t->n_philo)
	{
		philo->end = philo->t->time_to_die;
		philo->n = 0;
		philo->t->time = ft_time();
		pthread_create(&philo->thread, NULL, &philo_function, (void *)philo);
		if (philo->t->n_philo > 10)
			usleep(20);
		usleep(50);
		philo = philo->next;
		i++;
	}
}

void	death_checker(t_list *philo)
{
	while (1)
	{
		while (philo)
		{
			if (philo->end <= ft_time() - philo->t->time && philo->t->lock)
			{
				philo->t->lock = 0;
				usleep(100);
				killing_threads(philo);
				return ;
			}
			if (!philo->is_alive || philo->t->eating == 0)
			{
				destroy_mutex(philo);
				return ;
			}
			philo = philo->next;
		}
	}
}

int	main(int ac, char **av)
{
	t_philo	*t;
	t_list	*philo;
	t_list	*tmp;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		write (2, "Error\n", 6);
		return (0);
	}
	philo = NULL;
	t = malloc(sizeof(t_philo));
	t = init_philo(av, t);
	if (t == NULL)
		return (0);
	while (i < t->n_philo)
	{
		tmp = creation_list(i, t, t->n_philo);
		add_last(tmp, &philo, i);
		i++;
	}
	creation_of_threads(philo);
	death_checker(philo);
}
