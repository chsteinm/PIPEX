#include "pipex.h"

int	check_access(char **argv)
{
	if (access(argv[1], R_OK))
	{
		ft_printf("Access to \"%s\": %s\n", argv[1], strerror(errno));
		return (0);
	}
	if (access(argv[4], W_OK))
		if (errno != 2)
			ft_printf("Access to \"%s\": %s\n", argv[4], strerror(errno));
	return (errno == 0 || errno == 2);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;

	if (argc == 1)
		return (ft_printf("%s have no parameters\n", argv[0]) && 1);
	else if (argc < 5)
		return (ft_printf("%s have not all parameters\n", argv[0]) && 1);
	if (!check_access(argv))
		return (1);
	fd_in = open(argv[1], O_RDONLY);
	if (dup2(fd_in, 0) == -1)
		ft_printf("dup2 error : %s\n", strerror(errno));
	fd_out = open(argv[4], O_WRONLY | O_CREAT);
	if (dup2(fd_out, 1) == -1)
		ft_printf("dup2 error : %s\n", strerror(errno));
	if (fd_out == -1)
		ft_printf("open error : %s\n", strerror(errno));
	if (close(fd_in) == -1)
		ft_printf("close error : %s\n", strerror(errno));
	if (execve("/bin/cat", argv + 4, env) == -1)
		ft_printf("execve error : %s\n", strerror(errno));;
	if (close(0) == -1)
		ft_printf("close error : %s\n", strerror(errno));
	if (close(1) == -1)
		ft_printf("close error : %s\n", strerror(errno));
	if (close(fd_out) == -1)
		ft_printf("close error : %s\n", strerror(errno));
	return (0);
}
