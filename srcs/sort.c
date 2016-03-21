/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 13:00:19 by jubalest          #+#    #+#             */
/*   Updated: 2015/05/13 13:01:11 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

#include "../includes/minishell.h"

static t_bin	*return_result(t_sort *merge)
{
	t_bin *result;

	result = merge->result;
	free(merge);
	return (result);
}

static void		find_halfway(t_sort *merge)
{
	while (merge->temp && merge->temp->next)
	{
		merge->last = merge->right;
		merge->right = merge->right->next;
		merge->temp = merge->temp->next->next;
	}
}

static void		end_merge(t_sort *merge)
{
	if (!merge->result)
		merge->result = merge->next;
	else
		merge->tail->next = merge->next;
	merge->next->prev = merge->tail;
	merge->tail = merge->next;
}

static void		do_merge(t_sort *merge, t_bin *list, t_sh *shell)
{
	while (list || merge->right)
	{
		if (!merge->right)
		{
			merge->next = list;
			list = list->next;
		}
		else if (!list)
		{
			merge->next = merge->right;
			merge->right = merge->right->next;
		}
		else if (shell->compare(list, merge->right))
		{
			merge->next = list;
			list = list->next;
		}
		else
		{
			merge->next = merge->right;
			merge->right = merge->right->next;
		}
		end_merge(merge);
	}
}

t_bin			*merge_sort_list_recursive(t_bin *list, t_sh *shell)
{
	t_sort *merge;

	if ((merge = (t_sort *)malloc(sizeof(t_sort))))
	{
		if (!(list) || !(list->next))
		{
			free(merge);
			return (list);
		}
		set_merge(merge, list);
		find_halfway(merge);
		merge->last->next = NULL;
		list = merge_sort_list_recursive(list, shell);
		merge->right = merge_sort_list_recursive(merge->right, shell);
		do_merge(merge, list, shell);
		return (return_result(merge));
	}
	return (list);
}
