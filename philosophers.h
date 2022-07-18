#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct  s_collective
{
    int             total;
    int             threshold;
    int             sleep;
    int             eat;
    long long             start_time;
    int            total_meals;//optional
    int            ate;
    int            dead;
    int            all_ate;
    pthread_mutex_t *forks;
    pthread_mutex_t declare;
    pthread_mutex_t meal_check;
}               t_collective;


typedef struct  s_individual
{
    int         Id;
    int         f1;
    int         f2;
    int         meal_count;
    pthread_t   thread;
    int         threshold;
    long long         recent_meal;
    t_collective *c;
    int         starvation;
}               t_individual;

typedef struct  s_brain
{
    t_individual *i;
    t_collective *c;
}               t_brain;
void    *routine(void *voidP_brain);
int initialise_collective(t_collective *c, int argc, char **argv);
int write_error(char *str);
int conv_assign(char *str, int  *dest);
int initialise_individual(t_collective *c, int argc, char **argv);
int initialise_mutex(t_brain *brain);
//size_t  get_time(void);
void	ft_usleep(int ms);
void time_to_eat(t_individual *i);
void declare(t_individual *i, char *message);
long long	timestamp(void);
void death_check(t_individual *i);
void		smart_sleep(long long time, t_individual *i);
#endif