/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:53:10 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/05 19:35:16 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_last(t_list *tmp, t_list **philo, int i)
{
	t_list	*tmp1;
	int		x;

	if (*philo == NULL)
		*philo = tmp;
	else
	{
		x = 0;
		tmp1 = *philo;
		while (x < i - 1)
		{
			tmp1 = tmp1->next;
			x++;
		}
		tmp1->next = tmp;
		tmp->next = *philo;
	}
}

t_list	*creation_list(int index, t_philo *t, int x)
{
	t_list	*philo;

	philo = malloc(sizeof(t_list));
	philo->index = index + 1;
	philo->next = philo;
	philo->is_alive = 1;
	philo->n = x;
	philo->t = t;
	return (philo);
}

void	destroy_mutex(t_list *philo)
{
	int	i;

	i = 0;
	while (i < philo->t->n_philo)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		i++;
	}
	pthread_mutex_destroy(&philo->t->print);
}
