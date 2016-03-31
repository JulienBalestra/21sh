/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_keys_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:07:34 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:07:35 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_term	*get_current_cursor(t_term *term)
{
	while (term->next)
		term = term->next;
	while (term->cursor == 0)
		term = term->prev;
	return (term);
}

void	insert_link_before(t_term *term)
{
	t_term	*link;

	link = create_term_link();
	if (link)
	{
		link->next = term;
		if (term->prev)
		{
			link->prev = term->prev;
			term->prev->next = link;
		}
		term->prev = link;
	}
}
