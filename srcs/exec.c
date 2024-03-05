#include "../includes/pipex.h"

int	exec_second(t_data *data, char **env)
{
	if (data->fd_out != -1)
	{
		if (data->fd_in != -1)
			close(data->fd_in);
		close(data->fildes[1]);
		if (dup2(data->fildes[0], STDIN_FILENO))
			return (perror("dup2"), close_n_exit(data, 1));
		close(data->fildes[0]);
		if (dup2(data->fd_out, STDOUT_FILENO) == -1)
			return (perror("dup2"), close_n_exit(data, 1));
		close(data->fd_out);
		char *args[] = {"/bin/wc", "-l", NULL};
		execve(*args, args, env);
		ft_printf("execve : %s\n", strerror(errno));
		return (close_n_exit(data, 1));
	}
	else
		return (close_n_exit(data, 0));
}

int	exec_first(t_data *data, char **env)
{
	if (data->fd_in != -1)
	{
		close(data->fd_out);
		close(data->fildes[0]);
		if (dup2(data->fd_in, STDIN_FILENO) == -1)
			return (perror("dup2"), close_n_exit(data, 1));
		close(data->fd_in);
		if (dup2(data->fildes[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), close_n_exit(data, 1));
		close(data->fildes[1]);
		char *args[] = {"/bin/cat", "-e", NULL};
		execve("/bin/cat", args, env);
		ft_printf("execve : %s\n", strerror(errno));
		return (close_n_exit(data, 1));
	}
	else
		return (close_n_exit(data, 0));
}