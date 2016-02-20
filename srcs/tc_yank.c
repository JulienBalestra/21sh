#include "../includes/minishell.h"
#include "../libft/includes/libft.h"


void insert_yank(t_sh *shell, t_term *term)
{
	t_term *yank;

	//ft_putstr_fd("goyank\n", DEBUG_FD);
	yank = CONSOLE->yank;
	while (term->cursor == 0)
		term = term->prev;

	while (yank->prev)
		yank = yank->prev;

	while (yank)
	{
		//ft_putstr_fd("yank\n", DEBUG_FD);
		insert_link_before(term);
		term->prev->c = yank->c;
		display_term_line(shell, term);
		yank = yank->next;
	}
}