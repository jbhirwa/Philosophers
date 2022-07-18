#include "philosophers.h"

int write_error(char *str)
{
    int len;

    len = 0;
    while(str[len])
        len++;
    write(2, "Error: ", 7);
    write(2, str, len);
    write(2, "\n", 1);
    return(1);
}

int conv_assign(char *str, int  *dest)
{
    int i;
    
    i = 0;
    //printf("%d\n", (int )dest);
    if (str[i] == '\0')
        return(1);
    *dest = 0;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        *dest = *dest * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
        return (1);
    return (0);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void declare(t_individual *i, char *message)
{
        pthread_mutex_lock(&i->c->declare);
        printf("%i ", i->Id);
        printf("%llims ", timestamp() - i->c->start_time);
        printf("%s\n", message);
        pthread_mutex_unlock(&i->c->declare);
}

void		smart_sleep(long long time, t_individual *i)
{
	long long it;

	it = timestamp();
	while (!(i->c->dead))
	{
		if ((it - timestamp()) >= time)
			break ;
		usleep(50);
	}
}

long long time_diff(long long past, long long pres)
{
    return (pres - past);
}