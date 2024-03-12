#include "../includes/pipex_bonus.h"

void	close_fds(t_data *data)
{
	int	i;

	if (data->fd_in != -1 && !data->is_here_doc)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	if (data->is_here_doc)
	{
		close(data->fildes_hd[0]);
		close(data->fildes_hd[1]);
	}
	i = -1;
	while (data->fildes && data->fildes[++i])
	{
		close(data->fildes[i][0]);
		close(data->fildes[i][1]);
		free(data->fildes[i]);
	}
}

void	close_free_exit(t_data *data, int ret)
{
	if (ret)
		close_fds(data);
	ft_free_strings(data->args);
	ft_free_strings(data->path);
	free(data->fildes);
	free(data->pid);
	if (ret != EXIT_SUCCESS)
		exit(ret);
}

void	check_argc(t_data *data, int argc, char **argv)
{
	if (argc == 1)
	{
		ft_dprintf(STDERR_FILENO, "%s have no parameters\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
	{
		data->is_here_doc = 1;
		data->limiter = argv[2];
	}
	if (argc < 5 + data->is_here_doc)
	{
		ft_dprintf(STDERR_FILENO, "%s have not all parameters\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	ft_bzero((char *)&data, sizeof(t_data));
	check_argc(&data, argc, argv);
	set(&data, argc, argv, env);
	while (data.i < data.nb_cmd)
		if (data.pid[data.i++] == 0 && (data.i - 1 || data.fd_in != -1) && \
		(data.i < data.nb_cmd || data.fd_out != -1))
			exec_cmd(&data);
	close_fds(&data);
	data.i = -1;
	while (++data.i < data.nb_cmd)
		waitpid(data.pid[data.i], &data.status, 0);
	close_free_exit(&data, 0);
	return (WEXITSTATUS(data.status));
}
