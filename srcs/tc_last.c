#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void term_dup(t_sh *shell, t_term *term)
{
	t_term *link;
	t_term *prev;

	if (term == NULL)
		return ;
	if (CONSOLE->undo)
		safe_free_term(CONSOLE->undo);
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
	CONSOLE->undo = link;
}