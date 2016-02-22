#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void term_dup_to_current(t_sh *shell, t_term *term)
{
	t_term *link;
	t_term *prev;

	if (term == NULL || shell->current)
		return ;
	while (term->next)
		term = term->next;
	prev = NULL;
	link = NULL;
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
	while (link && link->next)
		link = link->next;
	shell->current = link;
	//DEBUG
		char *buf = tterm_to_str(link);
		ft_putstr_fd("current[", shell->debug_fd);
		ft_putstr_fd(buf, shell->debug_fd);
		ft_strdel(&buf);
		ft_putstr_fd("]\n", shell->debug_fd);
	//DEBUG
}