/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:42:02 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:42:03 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	remove_link(t_env *link)
{
	if (link)
	{
		free(link->name);
		link->name = NULL;
		free(link->value);
		link->value = NULL;
		free(link);
	}
}

void	delete_list(t_env **env)
{
	t_env *current;

	while (*env)
	{
		current = (*env)->next;
		remove_link(*env);
		*env = current;
	}
}

void 	delete_console(t_sh *shell)
{
	close(shell->debug_fd);
	free(shell->console);
}

void 	delete_hist(t_sh *shell)
{
	t_hist *tmp;
	t_hist *down;
	t_hist *up;

	down = shell->hist->down;
	while (down)
	{
		tmp = down;
		down = down->down;
		safe_free_term(tmp->line);
		free(tmp);
	}
	up = shell->hist;
	while (up)
	{
		tmp = up;
		up = up->up;
		safe_free_term(tmp->line);
		free(tmp);
	}
}

void	clean_program(t_sh *shell)
{
	delete_list(&(shell->env));
	ft_str2del(shell->l_env);
	free(shell->env);
	free(shell->ps1);
	if (shell->mock)
		clean_program(shell->mock);
	if (shell->stdin_buf)
		free(shell->stdin_buf);
	if (shell->console)
		delete_console(shell);
	if (shell->hist)
		delete_hist(shell);
	safe_free_term(shell->yank);
	safe_free_term(shell->undo);
	safe_free_term(shell->current);
	free(shell);
}
