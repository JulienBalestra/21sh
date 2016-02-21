#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>


void 	erase_line(size_t len)
{
	char *le;
	char *dc;

	while(len)
	{
		le = tgetstr("le", NULL);
		dc = tgetstr("dc", NULL);
		if (! le || ! dc)
			return;
		ft_putstr_fd(le, 1);
		ft_putstr_fd(dc, 1);
		len--;
	}
}

void 	erase_all_lines(t_sh *shell)
{
	//DEBUG
		ft_putstr_fd("CONSOLE->cur_line=", DEBUG_FD);
		ft_putlong_fd((long) CONSOLE->line_position, DEBUG_FD);
		ft_putstr_fd("\nCONSOLE->total_lines=", DEBUG_FD);
		ft_putlong_fd((long) CONSOLE->total_lines, DEBUG_FD);
		ft_putchar_fd('\n', DEBUG_FD);
	//DEBUG

	// go to the last line
	while (CONSOLE->line_position < CONSOLE->total_lines)
	{
		//DEBUG
			ft_putstr_fd("CONSOLE->cur_line=", DEBUG_FD);
			ft_putlong_fd((long) CONSOLE->line_position, DEBUG_FD);
			ft_putstr_fd("\nCONSOLE->total_lines=", DEBUG_FD);
			ft_putlong_fd((long) CONSOLE->total_lines, DEBUG_FD);
			ft_putchar_fd('\n', DEBUG_FD);
			ft_putstr_fd("{D}\n", DEBUG_FD);
		//DEBUG

		ft_putstr(tgetstr("do", NULL));
		CONSOLE->line_position++;
	}

	// erase all lines from the last to the second line
	while (CONSOLE->line_position > 1)
	{
		//DEBUG
			ft_putstr_fd("{U}\n", DEBUG_FD);
		//DEBUG

		erase_line(get_columns());
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->line_position--;
	}
	// erase first line
	erase_line(get_columns());
}

void 	display_term_characters(t_sh *shell, t_term *term)
{
	CONSOLE->total_lines = 1;
	/*//DEBUG
		ft_putstr_fd("columns=", DEBUG_FD);
		ft_putlong_fd((long)get_columns() - 1, DEBUG_FD);
		ft_putstr_fd("\n", DEBUG_FD);
	//DEBUG*/
	while (term->next)
	{
		//DEBUG
			ft_putstr_fd("char_position=", DEBUG_FD);
			ft_putlong_fd((long) CONSOLE->char_position, DEBUG_FD);
			ft_putstr_fd("\n", DEBUG_FD);
		//DEBUG

		if (CONSOLE->char_position == get_columns())
		{
			//DEBUG
				ft_putstr_fd("ENDLINE\n", DEBUG_FD);
			//DEBUG

			ft_putchar('\n');
			erase_line(get_columns());
			CONSOLE->char_position = 0;
			CONSOLE->total_lines++;
			CONSOLE->line_position++;
		}
		//DEBUG
			ft_putchar_fd('[', DEBUG_FD);
			ft_putchar_fd((char)term->c, DEBUG_FD);
			ft_putchar_fd(']', DEBUG_FD);
		//DEBUG

		ft_putchar((char)term->c);
		term = term->next;
		CONSOLE->char_position++;
	}
	//DEBUG
		ft_putstr_fd("CONSOLE->total_lines=", DEBUG_FD);
		ft_putlong_fd((long) CONSOLE->total_lines, DEBUG_FD);
		ft_putchar_fd('\n', DEBUG_FD);
	//DEBUG
}

void 	cursor_position(t_sh *shell, t_term *term)
{
	size_t end;

	while (term->next)
		term = term->next;
	while (term->cursor == 0)
	{
		if (CONSOLE->char_position == 0 && term->prev)
		{
			//DEBUG
				ft_putstr_fd("U", DEBUG_FD);
				ft_putnbr_fd((int)CONSOLE->char_position, DEBUG_FD);
				ft_putstr_fd("[", DEBUG_FD);
				ft_putchar_fd((char)term->c, DEBUG_FD);
				ft_putstr_fd("]\n", DEBUG_FD);
			//DEBUG

			ft_putstr(tgetstr("up", NULL));
			CONSOLE->line_position--;
			CONSOLE->char_position = get_columns() - 1;
			end = CONSOLE->char_position;
			while (end)
			{
				ft_putstr(tgetstr("nd", NULL));
				end--;
			}
			term = term->prev;
			continue;
		}
		//DEBUG
			ft_putstr_fd("<", DEBUG_FD);
			ft_putnbr_fd((int)CONSOLE->char_position, DEBUG_FD);
			ft_putstr_fd("[", DEBUG_FD);
			ft_putchar_fd((char)term->c, DEBUG_FD);
			ft_putstr_fd("]\n", DEBUG_FD);
		//DEBUG

		ft_putstr(tgetstr("le", NULL));
		term = term->prev;
		CONSOLE->char_position--;
	}
}

void 	display_term_line(t_sh *shell, t_term *term)
{
	erase_all_lines(shell);
	display_prompt(shell, 0);
	while (term->prev)
		term = term->prev;
	CONSOLE->char_position = shell->len_ps1;
	display_term_characters(shell, term);
	cursor_position(shell, term);
}

void 	get_top_and_left(t_sh *shell)
{
	while (CONSOLE->char_position > 1)
	{
		ft_putstr(tgetstr("le", NULL));
		CONSOLE->char_position--;
	}
	while (CONSOLE->line_position > 1)
	{
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->line_position--;
	}
}

int 	end_of_transmission(t_sh *shell, t_term *term)
{
	char *exit;
	char *ptr;

	while (term->next)
		term = term->next;
	if (term->prev)
		return (1);
	exit = ft_strdup("exit");
	ptr = exit;
	while (*exit)
	{
		tc_continue_process_key(shell, term, (long)*exit);
		exit++;
	}
	ft_strdel(&ptr);
	return (0);
}

int 	tc_continue_process_key(t_sh *shell, t_term *term, long key)
{
	if (key == '\n' || (char)key == '\n')
	{
		get_top_and_left(shell);
		return (0);
	}
	else if (key == KEY_CTRL_D)
	{
		return (end_of_transmission(shell, term));
	}
	else if (tc_action_keys(shell, term, key) == 0 && ft_isprint((char)key))
	{
		while (term->cursor == 0)
			term = term->prev;
		insert_link_before(term);
		term->prev->c = key;
	}
	display_term_line(shell, term);
	//term_dup(shell, term); TODO undo
	return (1);
}
