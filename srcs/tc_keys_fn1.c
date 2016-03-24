#include "../includes/minishell.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>


void	erase_line(size_t len)
{
	char	*le;
	char	*dc;

	while (len)
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

void	erase_all_lines(t_sh *shell)
{
	/*//DEBUG
		ft_putstr_fd("CONSOLE->cur_line=", DEBUG_FD);
		ft_putlong_fd((long) CONSOLE->line_position, DEBUG_FD);
		ft_putstr_fd("\nCONSOLE->total_lines=", DEBUG_FD);
		ft_putlong_fd((long) CONSOLE->total_lines, DEBUG_FD);
		ft_putchar_fd('\n', DEBUG_FD);
	//DEBUG*/

	// go to the last line
	while (CONSOLE->line_position < CONSOLE->total_lines)
	{
		/*//DEBUG
			ft_putstr_fd("CONSOLE->cur_line=", DEBUG_FD);
			ft_putlong_fd((long) CONSOLE->line_position, DEBUG_FD);
			ft_putstr_fd("\nCONSOLE->total_lines=", DEBUG_FD);
			ft_putlong_fd((long) CONSOLE->total_lines, DEBUG_FD);
			ft_putchar_fd('\n', DEBUG_FD);
			ft_putstr_fd("{D}\n", DEBUG_FD);
		//DEBUG*/

		ft_putstr(tgetstr("do", NULL));
		CONSOLE->line_position++;
	}

	// erase all lines from the last to the second line
	while (CONSOLE->line_position > 1)
	{
		/*//DEBUG
			ft_putstr_fd("{U}\n", DEBUG_FD);
		//DEBUG*/

		erase_line(get_columns());
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->line_position--;
	}
	// erase first line
	erase_line(CONSOLE->char_position);
}

void	get_top_and_left(t_sh *shell)
{
	char	*le;

	while (CONSOLE->char_position > 1)
	{
		le = tgetstr("le", NULL);
		if (!le)
		{
			ft_putstr_fd("Env not loaded\n", 2);
			exit(2);
		}
		ft_putstr(le);
		CONSOLE->char_position--;
	}
	while (CONSOLE->line_position > 1)
	{
		ft_putstr(tgetstr("up", NULL));
		CONSOLE->line_position--;
	}
}
