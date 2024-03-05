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
	if (access(argv[1], R_OK))
	{
		ft_printf("Access to \"%s\": %s\n", argv[1], strerror(errno));
		exit(1);
	}
	if (access(argv[4], W_OK))
		if (errno != 2)
			ft_printf("Access to \"%s\": %s\n", argv[4], strerror(errno));
	if (!(errno == 0 || errno == 2))
		exit(1);
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in == -1)
	{
		ft_printf("Open : \"%s\": %s\n", argv[1], strerror(errno));
		exit(1);
	}
	data->fd_out = open(argv[4], O_WRONLY | O_CREAT, 0666);
	if (data->fd_in == -1)
	{
		ft_printf("Open : \"%s\": %s\n", argv[4], strerror(errno));
		close(data->fd_in);
		exit(1);
	}
}

int close_n_exit(t_data *data, int ret)
{
	if (data->fd_in)
		close(data->fd_in);
	if (data->fd_out)
		close(data->fd_out);
	close(data->fildes[0]);
	close(data->fildes[1]);
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)env;
	check_argc(argc, argv);
	open_files(&data, argv);
	if (pipe(data.fildes) == -1)
		return (perror("pipe"), 1);
	data.pid = fork();
	if (data.pid == - 1)
		return (perror("fork"), close_n_exit(&data, 1));
	if (data.pid == 0)
	{
		close(data.fd_out);
		// if (dup2(data.fd_in, STDIN_FILENO) == -1)
		// 	return (perror("dup2"), close_n_exit(&data, 1));
		close(data.fd_in);
		close(data.fildes[0]);
		// if (dup2(data.fildes[1], STDOUT_FILENO) == -1)
		// 	return (perror("dup2"), close_n_exit(&data, 1));
		close(data.fildes[1]);
		char *args[] = {"/bin/cat", "-e", argv[1], NULL};
		if (execve("/bin/cat", args, env) == -1)
			ft_printf("execve error : %s\n", strerror(errno));
	}
	// if (dup2(data.fd_out, 1) == -1)
	// 	ft_printf("dup2 error : %s\n", strerror(errno));
	// if (close(0) == -1)
	// 	ft_printf("close error : %s\n", strerror(errno));
	// if (close(1) == -1)
	// 	ft_printf("close error : %s\n", strerror(errno));
	// if (close(fd_out) == -1)
	// 	ft_printf("close error : %s\n", strerror(errno));
	wait(&data.pid);
	close_n_exit(&data, 0);
	return (0);
}
