#include "philosophers.h"

/*int main(int argc, char **argv)
{
    t_collective    collective;

    if (initialise_collective(&collective, argc, argv))
        return (1);
    return(0);
}*/

int main(int argc, char **argv)
{
    t_collective    c;
    t_individual    *i;
    int             it;

    if (initialise_collective(&c, argc, argv))
        return (1);
    i = initialise_individual(&c, i, argc, argv);
    it = 0;
     if (initialise_mutex(&c, i))
        return (1);
    while (it < c.total)
    {
        c.start_time = timestamp();
        //routine//pthread_create could be the problem
        if (pthread_create(&i[it].thread, NULL, &routine, (void *)&i[it]))
            return(write_error(":/ ."));
        i[it].recent_meal = timestamp();
        printf("p%d\n", i[it].Id);
        it++;
    }
    death_check(i);
    exit_plan(i);
    return(0);
}