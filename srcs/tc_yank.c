#include "../includes/minishell.h"


void insert_yank(t_sh *shell, t_term *term)
{
	t_term *yank;

	yank = shell->yank;
	while (term->cursor == 0)
		term = term->prev;

	while (yank->prev)
		yank = yank->prev;

	while (yank)
	{
		insert_link_before(term);
		term->prev->c = yank->c;
		display_term_line(shell, term);
		yank = yank->next;
	}
}