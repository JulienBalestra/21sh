#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>

#include <fcntl.h>

#include "../libft/includes/libft.h"
#include "../includes/ast.h"



void exec_with_recurse(t_ast *ast)
{
	char	**ptr;

	if (ast->op == -1)
	{
		ptr = ast->cmd;
		execve(ast->cmd[0], ptr, NULL);
		ft_putstr_fd("error in execve\n", 2);
	}
	else if (ast->op == 1)
	{
		manage_pipe(ast);
	}
	else if (ast->op == 2 || ast->op == 3)
	{
		manage_write(ast);
	}
	else if (ast->op == 4)
	{
		manage_double_read(ast);
	}
	else if (ast->op == 5)
	{
		manage_simple_read(ast);
	}
}

int ast_exec(t_ast *ast)
{
	pid_t	pid;
	int		status;

	pid = 0;
	if (ast->op == 1 || ast->op == 4 || ast->op == -1)
		pid = fork();

	if (pid == 0)
	{
		exec_with_recurse(ast);
		return (0);
	}
	else
	{
		waitpid(-1, &status, 0);
		return (1);
	}
}

