#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define ERR_CNF "%s: command not found\n"

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	int		nb_cmd;
	int		**fildes;
	pid_t	*pid;
	int		status;
	char	**args;
	char	**argv_ptr;
	char	**env_ptr;
	char	**path;
	int		is_env;
	int		is_path;
	int		is_here_doc;
	int		i;
}					t_data;

int		close_n_exit(t_data *data, int ret);
void	close_free_exit(t_data *data, int ret);
void	close_fds(t_data *data);
void	exec_cmd(t_data *data);

#endif
