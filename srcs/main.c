/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:56 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:57 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		run_each_cli(t_ast **command, t_sh *shell)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (command && command[i])
	{
		if (ret == 1)
			ret = ast_exec(command[i], shell);
		ast_clean(command[i]);
		i++;
	}
	return (ret ? 0 : 1);
}

int		process_cli(t_sh *shell)
{
	t_ast	**command;
	int		ret;

	if (existing_line(shell) && correct_syntax(shell) == 0)
	{
		command = build_command(shell);
		ret = run_each_cli(command, shell);
		free(command);
		return (ret);
	}
	return (0);
}

int		start_engine(t_sh *shell)
{
	while (42)
	{
		shell->stdin_buf = get_line(shell);
		if (process_cli(shell) == 1)
			return (1);
		if (shell->close_program == 1)
			return (0);
	}
}

int		main(void)
{
	int		ret;
	t_sh	*shell;

	if ((shell = create_shell_props()))
	{
		if (start_engine(shell) == 0)
		{
			ret = shell->l_ret;
			clean_program(shell);
			return (ret);
		}
		ret = shell->l_ret;
		clean_program(shell);
		return (ret);
	}
	return (3);
}
