#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void term_dup_to_current(t_sh *shell, t_term *term)
{
	t_term *link;
	t_term *prev;

	if (term == NULL)
		return ;
	if (shell->current)
	{
		safe_free_term(shell->current);
		shell->current = NULL;
	}
	while (term->next)
		term = term->next;
	prev = NULL;
	link = NULL;
	term = term->prev;
	while (term)
	{
		link = create_term_link();
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
	shell->current = link;
}