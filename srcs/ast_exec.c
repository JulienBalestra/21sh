/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:11:07 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:11:10 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void		exec_with_recurse(t_ast *ast, t_sh *shell)
{
	if (ast->op == -1)
	{
		manage_interpretor(ast->cmd, shell);
		change_fd(ast);
		if (manage_builtins(ast->cmd, shell))
			exit(0);
		else if (make_exploitable(ast->cmd, shell->l_env))
		{
			if (start_exec((const char **)ast->cmd, shell, NULL, 0) == 0)
				exit(1);
		}
		else
			display_command_not_found(ast->cmd[0]);
		exit(2);
	}
	else if (ast->op == 1)
		manage_pipe(ast, shell);
	else if (ast->op == 2 || ast->op == 3)
		manage_write(ast, shell);
	else if (ast->op == 4)
		manage_double_read(ast, shell);
	else if (ast->op == 5)
		manage_simple_read(ast, shell);
}

int			dont_fork(char **command, t_sh *shell)
{
	if (ft_strcmp(command[0], "unsetenv") == 0)
	{
		builtin_unsetenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "cd") == 0)
	{
		builtin_cd(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "setenv") == 0)
	{
		builtin_setenv(command, shell);
		return (1);
	}
	else if (ft_strcmp(command[0], "exit") == 0)
	{
		builtin_exit(command, shell);
		return (1);
	}
	return (0);
}

int			ast_exec(t_ast *ast, t_sh *shell)
{
	pid_t	pid;
	int		status;

	if (ast->op == -1 && dont_fork(ast->cmd, shell))
	{
		if (shell->exit == 1)
			return (0);
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		exec_with_recurse(ast, shell);
		return (0);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->l_ret = WEXITSTATUS(status);
		return (1);
	}
}
