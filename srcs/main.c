#include "../includes/pipex.h"

void	check_argc(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf("%s have no parameters\n", argv[0]);
		exit(1);
	}
	if (argc < 5)
	{
		ft_printf("%s have not all parameters\n", argv[0]);
		exit(1);
	}
}

void	open_files(t_data *data, char **argv)
{
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
	{
		ft_printf("Open : %s: %s\n", argv[1], strerror(errno));
	}
	data->fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_out == -1)
	{
		ft_printf("Open : %s: %s\n", argv[4], strerror(errno));
	}
}

int close_n_exit(t_data *data, int ret)
{
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	close(data->fildes[0]);
	close(data->fildes[1]);
	close(1);
	close(0);
	ft_free_strings(data->args_in);
	ft_free_strings(data->args_out);
	ft_free_strings(data->path);
	return (ret);
}

char	**ret_path(char **env)
{
	char	*line_ptr;
	size_t	i;

	i = -1;
	line_ptr = NULL;
	while (!line_ptr && env[++i])
		line_ptr = ft_strnstr(env[i], "PATH=", 6);
	return (ft_split(line_ptr, ':'));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	check_argc(argc, argv);
	ft_bzero((char *)&data, sizeof(t_data));
	open_files(&data, argv);
	data.argv_ptr = argv;
	data.path = ret_path(env);
	if (!data.path)
		return (ft_printf("Malloc failed\n"), close_n_exit(&data, 1));
	if (pipe(data.fildes) == -1)
		return (perror("pipe"), close_n_exit(&data, 1));
	data.pid = fork();
	if (data.pid == - 1)
		return (perror("fork"), close_n_exit(&data, 1));
	if (data.pid == 0)
		return (exec_first(&data, env));
	data.pid2 = fork();
	if (data.pid2 == - 1)
		return (perror("fork"), close_n_exit(&data, 2));
	if (data.pid2 == 0)
		return (exec_second(&data, env));
	close_n_exit(&data, 0);
	wait(&data.pid);
	wait(&data.pid2);
	return (0);
}
