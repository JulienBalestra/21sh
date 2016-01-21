/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_exec_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:12:59 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:13:01 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>

#include <fcntl.h>

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

void		manage_pipe(t_ast *ast, t_sh *shell)
{
	int		p[2];
	pid_t	pid;
	int		status;

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		dup2(p[1], ast->stdout);
		close(p[0]);
		exec_with_recurse(ast->left, shell);
	}
	else
	{
		dup2(p[0], ast->stdin);
		close(p[1]);
		waitpid(-1, &status, 0);
		exec_with_recurse(ast->right, shell);
	}
}

void		manage_double_read(t_ast *ast, t_sh *shell)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	**cmd;

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		cmd = ast->right->cmd;
		dup2(p[1], ast->stdout);
		close(p[0]);
		while (*cmd)
		{
			ft_putstr_fd(*cmd, ast->stdout);
			cmd++;
		}
		ast_clean(ast);
		exit(0);
	}
	else
	{
		dup2(p[0], ast->stdin);
		close(p[1]);
		waitpid(-1, &status, 0);
		exec_with_recurse(ast->left, shell);
	}
}

void		manage_write(t_ast *ast, t_sh *shell)
{
	int		fd;
	pid_t	pid;
	int		status;

	if (ast->op == 2)
		fd = open(ast->right->cmd[0], O_WRONLY | O_APPEND | O_CREAT,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(ast->right->cmd[0], O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, ast->stdout);
		exec_with_recurse(ast->left, shell);
	}
	else
	{
		close(fd);
		waitpid(-1, &status, 0);
	}
}

void		manage_simple_read(t_ast *ast, t_sh *shell)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = open(ast->right->cmd[0], O_RDONLY);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, ast->stdin);
		exec_with_recurse(ast->left, shell);
	}
	else
	{
		close(fd);
		waitpid(-1, &status, 0);
	}
}
