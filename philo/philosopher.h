#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define FORK		"has taken a fork\n"
# define EAT	"is eating\n"
# define SLEEP	  "is sleeping\n"
# define THINK	  "is thinking\n"
# define DEAD		"is dead\n"

/*          ROUTINE         */
void* routine();
/*          PARSING         */
int	check_arg(char **argv);


#endif