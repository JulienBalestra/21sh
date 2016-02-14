#include "../includes/minishell.h"
#include <fcntl.h>

int create_debug_file(void)
{
	int fd;

	fd = open("fd_debug",
		O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fd);
}