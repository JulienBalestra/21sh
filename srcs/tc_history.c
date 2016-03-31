/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:56:39 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/15 10:56:45 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

t_hist	*create_history(void)
{
	t_hist	*hist;

	if ((hist = (t_hist *)malloc(sizeof(t_hist))))
	{
		hist->down = NULL;
		hist->up = NULL;
		hist->line = NULL;
	}
	return (hist);
}

void	add_to_history(t_sh *shell, t_term *term)
{
	t_hist	*new_line;
	t_hist	*browse;

	if (term->prev && shell->hist)
	{
		browse = shell->hist;
		while (browse->down)
			browse = browse->down;
		if (compare_terms(browse->line, term) == 0)
		{
			new_line = create_history();
			new_line->line = term;
			browse->down = new_line;
			new_line->up = browse;
		}
		else
			safe_free_term(term);
	}
	else if (term->prev)
	{
		new_line = create_history();
		new_line->line = term;
		shell->hist = new_line;
	}
}

void	replace_body_from_tail(t_term *hist_term, t_term *term)
{
	t_term	*tmp;

	while (hist_term->next)
		hist_term = hist_term->next;
	while (term->next)
		term = term->next;
	if (term->prev)
	{
		clean_current_line(term);
	}
	term->cursor = 1;
	hist_term = hist_term->prev;
	while (hist_term)
	{
		tmp = create_term_link();
		tmp->c = hist_term->c;
		term->prev = tmp;
		tmp->next = term;
		term = term->prev;
		hist_term = hist_term->prev;
	}
}

void	nobody_from_tail(t_term *term)
{
	t_term	*tmp;
	t_term	*clean;

	while (term->next)
		term = term->next;
	term->cursor = 1;
	clean = term->prev;
	term->prev = NULL;
	while (clean)
	{
		tmp = clean;
		clean = clean->prev;
		tmp->c = 0;
		tmp->cursor = 0;
		free(tmp);
	}
}
