#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void term_dup_left(t_sh *shell, t_term *term)
{
	t_term *link;
	t_term *prev;

	if (term == NULL)
		return ;
	safe_free_term(CONSOLE->yank);
	prev = NULL;
	link = NULL;
	term = get_current_cursor(term);
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
	CONSOLE->yank = link;
}

void term_dup_right(t_sh *shell, t_term *term)
{
	t_term *link;
	t_term *prev;

	if (term == NULL)
		return ;
	safe_free_term(CONSOLE->yank);
	prev = NULL;
	link = NULL;
	term = get_current_cursor(term);
	//term = term->up;
	while (term->next)
	{
		link = create_link();
		if (prev)
		{
			link->prev = prev;
			prev->next = link;
		}
		link->c = term->c;
		link->cursor = term->cursor;
		term = term->next;
		prev = link;
	}
	CONSOLE->yank = link;
}