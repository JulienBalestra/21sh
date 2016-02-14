#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>


void 	erase_all_lines(t_sh *shell)
{
	//DEBUG
	ft_putstr_fd("CONSOLE->cur_line=", DEBUG_FD);
	ft_putlong((long)CONSOLE->cur_line, DEBUG_FD);
	ft_putstr_fd("\nCONSOLE->nb_lines=", DEBUG_FD);
	ft_putlong((long)CONSOLE->nb_lines, DEBUG_FD);
	ft_putchar_fd('\n', DEBUG_FD);
	//DEBUG

	// go to the last line
	while (CONSOLE->cur_line < CONSOLE->nb_lines)
	{
		//DEBUG
		ft_putstr_fd("CONSOLE->cur_line=", DEBUG_FD);
		ft_putlong((long)CONSOLE->cur_line, DEBUG_FD);
		ft_putstr_fd("\nCONSOLE->nb_lines=", DEBUG_FD);
		ft_putlong((long)CONSOLE->nb_lines, DEBUG_FD);
		ft_putchar_fd('\n', DEBUG_FD);
		//DEBUG

		ft_putstr(tgetstr("do", NULL));
		CONSOLE->cur_line++;
	}

	// erase all lines from the last to the second line
	while (CONSOLE->nb_lines > 1)
	{
		erase_line(get_columns());
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->nb_lines--;
	}
	// erase first line
	erase_line(get_columns());
}

void 	display_term_characters(t_sh *shell, t_term *term, size_t cur_line_len)
{
	CONSOLE->nb_lines = 1;
	/*//DEBUG
		ft_putstr_fd("csize=", DEBUG_FD);
		ft_putlong((long)get_columns() - 1, DEBUG_FD);
		ft_putstr_fd("\n", DEBUG_FD);
	//DEBUG*/
	while (term->next)
	{
		//DEBUG
			ft_putstr_fd("cur_line_len=", DEBUG_FD);
			ft_putlong((long)cur_line_len, DEBUG_FD);
			ft_putstr_fd("\n", DEBUG_FD);
		//DEBUG

		if (cur_line_len == get_columns())
		{
			/*//DEBUG
				ft_putstr_fd("ENDLINE\n", DEBUG_FD);
			//DEBUG*/

			ft_putchar('\n');
			erase_line(get_columns());
			cur_line_len = 0;
			CONSOLE->nb_lines++;
			CONSOLE->cur_line++;
		}
		//DEBUG
			ft_putchar_fd('[', DEBUG_FD);
			ft_putchar_fd((char)term->c, DEBUG_FD);
			ft_putchar_fd(']', DEBUG_FD);
		//DEBUG

		ft_putchar((char)term->c);
		term = term->next;
		cur_line_len++;
	}
	//DEBUG
		ft_putstr_fd("CONSOLE->nb_lines=", DEBUG_FD);
		ft_putlong((long)CONSOLE->nb_lines, DEBUG_FD);
		ft_putchar_fd('\n', DEBUG_FD);
	//DEBUG
}

void 	display_term_line(t_sh *shell, t_term *term)
{
	erase_all_lines(shell);
	display_prompt(shell, 0);
	while (term->prev)
		term = term->prev;
	display_term_characters(shell, term, shell->len_ps1 + 2);
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
		return (0);
	else if (tc_action_keys(shell, term, key) == 0 && ft_isprint((char)key))
	{
		while (term->cursor == 0)
			term = term->prev;
		insert_link_before(term);
		term->prev->c = key;
		display_term_line(shell, term);
	}
	else if (key == KEY_CTRL_D)
	{
		return (end_of_transmission(shell, term));
	}
	term_dup(shell, term);
	return (1);
}
