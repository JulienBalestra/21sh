#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


/*void restore_last(t_sh *shell, t_term *term)
{
	t_term *last;
	t_term *link;

	if (shell->last == NULL)
		return ;
	last = shell->last;
	while (term->next)
		term = term->next;
	while (last->next)
		last = last->next;
	term->cursor = last->cursor;
	last = last->prev;
	while (last->prev)
	{
		link = create_link();
		term->prev = link;
		link->next = term;
		link->c = last->c;
		link->cursor = last->cursor;
		last = last->prev;
		term = link;
	}

	while (term->cursor == 0)
	{
		ft_putchar('.');
		ft_putchar((char)term->c);
		ft_putnbr(term->cursor);
		term = term->prev;
	}

	display_term_line(shell, term);
}*/

void term_dup(t_sh *shell, t_term *term)
{
	t_term *link;
	t_term *prev;

	if (term == NULL)
		return ;
	if (shell->last)
		safe_free_term(shell->last);
	while (term->next)
		term = term->next;
	prev = NULL;
	link = NULL;
	term = term->prev;
	while (term)
	{
		link = create_link();
		if (prev)
		{
			link->next = prev;
			prev->prev = link;
		}
		link->c = term->c;
		link->cursor = term->cursor;
		term = term->prev;
		prev = link;
	}
	shell->last = link;
}