#include "philosophers.h"

//one philosopher is sent at a time
void    *routine(void *voidP_brain)
{
  //  printf("done\n");
    t_individual *i;

    i = (t_individual *)voidP_brain;
    i->recent_meal = timestamp();
    if (i->Id % 2)
    {
        usleep(15);//i->c->eat);
        //printf("\t\tdone sleep %d", i->Id);
        //printf(" fork id%d\n", i->f1);
    }
    else
    {
        //printf("\t\tnever sleep %d", i->Id);
        //printf(" fork id %d\n", i->f1);
    }
    while(!(i->c->dead))
   //while(1)
    {
        time_to_eat(i);
        if (i->c->all_ate)
            break ;
        declare(i, "is sleeping");
        smart_sleep((long long)i->c->sleep, i);
        declare(i, "is thinking");
    }
    return(NULL);
}

void time_to_eat(t_individual *i)
{
    pthread_mutex_lock(&i->c->forks[i->f1]);
    pthread_mutex_lock(&i->c->forks[i->f2]);
    declare(i, "forks acquired");
    declare(i, "eating");

    i->recent_meal = timestamp();
    i->threshold = i->recent_meal + i->c->eat;
   // usleep(i->c->sleep);
    smart_sleep((long long)i->c->sleep, i);
    i->meal_count++;
    pthread_mutex_unlock(&i->c->forks[i->f1]);
    pthread_mutex_unlock(&i->c->forks[i->f2]);
    declare(i, "forks released");
}

void death_check(t_individual *i)
{
    int it;

    while (!(i->c->ate))
    {
        it = -1;
        while(it++ < i->c->total && !(i->c->dead))
        {
            //if ((i[it].threshold - i[it].recent_meal) > i->c->eat)
            if ((timestamp() - i[it].recent_meal) > i->c->threshold)
            {
                declare(&i[it], "dead");
                i->c->dead = 1;
            }
            else
                usleep(100);
        }
        if (i->c->dead)
            break ;
        it = 0;
        while (i->c->total_meals != -1 && it < i->c->total && i[it].meal_count >=  i->c->total_meals)
            it++;
        if (it == i->c->total)
            i->c->all_ate = 1;
    }

}