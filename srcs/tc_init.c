/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:44:41 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:44:43 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "../includes/minishell.h"
#include <unistd.h>

void	raw_terminal_mode(t_sh *shell)
{
	struct termios	tattr;
	char			*env_term;

	tcgetattr(STDIN_FILENO, &shell->default_termios);
	tcgetattr(STDIN_FILENO, &tattr);
	if ((env_term = get_env_value("TERM", shell->env)))
	{
		tattr.c_lflag &= ~(ECHO | ICANON);
		tattr.c_oflag &= (OPOST);
		tattr.c_cc[VMIN] = 1;
		tattr.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
		tgetent(NULL, env_term);
	}
}

void	default_terminal_mode(t_sh *shell)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->default_termios);
}
