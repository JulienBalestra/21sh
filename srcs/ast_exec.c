#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include "../includes/minishell.h"

void exec_with_recurse(t_ast *ast, t_sh *shell)
{
	if (ast->op == -1)
	{
		// TODO check if too many forks
		manage_interpretor(ast->cmd, shell);
		if (manage_builtins(ast->cmd, shell))
			exit(0);
		else if (make_exploitable(ast->cmd, shell->l_env))
		{
			if (do_fork((const char **)ast->cmd, shell, NULL, 0) == 0)
				exit(1);
		}
		else
			display_command_not_found(ast->cmd[0]);
		exit(2);
	}
	else if (ast->op == 1)
	{
		manage_pipe(ast, shell);
	}
	else if (ast->op == 2 || ast->op == 3)
	{
		manage_write(ast, shell);
	}
	else if (ast->op == 4)
	{
		manage_double_read(ast, shell);
	}
	else if (ast->op == 5)
	{
		manage_simple_read(ast, shell);
	}
}

int ast_exec(t_ast *ast, t_sh *shell)
{
	pid_t	pid;
	int		status;

	pid = 0;
	if (ast->op == 1 || ast->op == 4 || ast->op == -1)
		pid = fork();

	if (pid == 0)
	{
		exec_with_recurse(ast, shell);
		return (0);
	}
	else
	{
		waitpid(-1, &status, 0);
		// TODO manage exit code
		return (1);
	}
}

