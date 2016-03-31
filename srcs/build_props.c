/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_props.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:31:14 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:31:18 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	sub_part(t_sh *shell)
{
	shell->mock = NULL;
	shell->l_env = NULL;
	shell->l_env = override_last_environ(shell);
	shell->ps1 = ft_strdup(DEFAULT_PS1);
	shell->len_ps1 = ft_strlen(DEFAULT_PS1);
	update_ps1(shell);
	shell->l_ret = 0;
	shell->stdin_buf = NULL;
	shell->close_program = 0;
	shell->console = create_console();
	shell->hist = NULL;
	shell->debug_fd = create_debug_file();
	shell->yank = NULL;
	shell->undo = NULL;
	shell->current = NULL;
	shell->opened = create_opened();
	shell->ddl_eof = 0;
	shell->compare = compare_name;
	shell->map = NULL;
}

t_sh	*create_shell_from(char **environ_tab)
{
	t_sh	*shell;

	if ((shell = (t_sh *)malloc(sizeof(t_sh))))
	{
		shell->env = build_env_list(environ_tab);
		ensure_pwd(shell);
		sub_part(shell);
		build_map(shell);
		return (shell);
	}
	return (NULL);
}

t_sh	*create_shell_props(void)
{
	t_sh		*shell;
	extern char	**environ;

	if ((shell = create_shell_from(environ)))
	{
		return (shell);
	}
	return (NULL);
}
