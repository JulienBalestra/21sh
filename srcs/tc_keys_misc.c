#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_term *get_current_cursor(t_term *term)
{
	while (term->next)
		term = term->next;
	while (term->cursor == 0)
		term = term->prev;
	return (term);
}

void 	insert_link_before(t_term *term)
{
	t_term *link;

	link = create_link();
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

void 	clear_line(int left, int len)
{
	char *le;
	char *dc;

	while(left)
	{
		le = tgetstr("le", NULL);
		if (! le )
		{
			return;
		}
		ft_putstr_fd(le, 1);
		left--;
	}
	while(len)
	{
		dc = tgetstr("dc", NULL);
		if (! dc)
		{
			return;
		}
		ft_putstr_fd(dc, 1);
		len--;
	}
}

int get_left_len(t_term *term)
{
	int len;

	len = 0;
	while(term->prev)
	{
		term = term->prev;
	}
	while (term->cursor == 0)
	{
		term = term->next;
		len++;
	}
	return (len);
}

int get_total_len(t_term *term)
{
	int len;

	len = 0;
	while (term->next)
	{
		term = term->next;
	}
	while (term->prev)
	{
		term = term->prev;
		len++;
	}
	return (len);
}