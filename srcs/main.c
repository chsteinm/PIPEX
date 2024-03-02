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

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)env;
	check_argc(argc, argv);
	open_files(&data, argv);
	if (pipe(data.fildes) == -1)
		return (perror("pipe"), 1);
	if (dup2(data.fd_in, 0) == -1)
		ft_printf("dup2 error : %s\n", strerror(errno));
	if (dup2(data.fd_out, 1) == -1)
		ft_printf("dup2 error : %s\n", strerror(errno));
	// if (execve("/bin/cat", argv + 4, env) == -1)
	// 	ft_printf("execve error : %s\n", strerror(errno));
	// if (close(0) == -1)
	// 	ft_printf("close error : %s\n", strerror(errno));
	// if (close(1) == -1)
	// 	ft_printf("close error : %s\n", strerror(errno));
	// if (close(fd_out) == -1)
	// 	ft_printf("close error : %s\n", strerror(errno));
	return (0);
}
