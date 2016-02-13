#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void exec_del_right(t_sh *shell, t_term *term)
{
	t_term	*next_link;

	(void)shell;
	term = get_current_cursor(term);
	if (term->next)
	{
		next_link = term->next;
		if (term->prev)
			term->prev->next = next_link;
		next_link->prev = term->prev;
		free(term);
		next_link->cursor = 1;
		ft_putstr(tgetstr("dc", NULL));
	}
}

void exec_del_and_move_left(t_sh *shell, t_term *term)
{
	t_term	*prev_link;

	(void)shell;
	term = get_current_cursor(term);
	if (term->prev)
	{
		prev_link = term->prev;
		if (prev_link->prev)
			prev_link->prev->next = term;
		term->prev = prev_link->prev;
		free(prev_link);
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
}
