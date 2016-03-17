/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:01:20 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:01:21 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void set_merge(t_sort *merge, t_bin *list)
{
	if (merge)
	{
		merge->right = list;
		merge->temp = list;
		merge->last = list;
		merge->result = NULL;
		merge->next = NULL;
		merge->tail = NULL;
	}
}

int		compare_name(t_bin *one, t_bin *two)
{
	int i;

	i = 0;
	while ((one->name[i] != '\0') && (two->name[i] != '\0') &&
		   (one->name[i] == two->name[i]))
		i++;
	if (one->name[i] - two->name[i] < 0)
		return (1);
	return (0);
}