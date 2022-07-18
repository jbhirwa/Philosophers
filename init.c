 #include "philosophers.h"

 /*int initialise_collective(t_collective *c, int argc, char **argv)
 {
     if (argc < 5 || argc > 6)
         return(write_error("Arguments provided not within bounds."));
 	if (conv_assign(argv[1], &c->total) || c->total == 0
 		|| conv_assign(argv[2], &c->threshold) || c->threshold == 0
 		|| conv_assign(argv[3], &c->eat) || c->eat == 0
 		|| conv_assign(argv[4], &c->sleep) || c->sleep == 0)
         return(write_error("Invalid arguments provided."));
 	if (argc == 6 && (conv_assign(argv[5], &c->total_meals)
 		|| c->total_meals == 0))
         return(write_error("Invalid arguments provided."));
 	else if (argc == 5)
 		c->total_meals = -1;
    c->ate = 0;
    c->dead = 0;
    c->all_ate = 0;
     initialise_individual(c, argc, argv);
     return (0);
 }

 int initialise_individual(t_collective *c, int argc, char **argv)
 {
    t_brain brain;
    int     i;

    i = c->total;
    brain.c = c;
    brain.i = malloc(sizeof(t_individual) * brain.c->total);
    initialise_mutex(&brain);
    if (!brain.i)
        return(write_error("Could not allocate space."));
     while (--i >= 0)//< brain.c->total)
     {
        brain.i[i].Id = i;//+1;
        brain.i[i].f1 = i;
        brain.i[i].c = c;
        brain.i[i].f2 = (i + 1) % brain.c->total;
       // printf("id:%d %d\n",brain.i[i].Id, brain.i[i].f1);
     //   printf("id:%d %d\n",brain.i[i].Id, brain.i[i].f2);
       // i++;
     }
     i = 0;
     while (i < brain.c->total)
     {
        brain.c->start_time = timestamp();
        if (pthread_create(&brain.i[i].thread, NULL, &routine, (void *)&brain.i[i]))
            return(write_error(":/ ."));
        brain.i[i].recent_meal = timestamp();
        i++;
     }
     death_check(brain.i);
     //exit launch
     exit_plan(brain.i);
     return (0);
 }

//all good till here
 int initialise_mutex(t_brain *brain)
 {
    int i;
    
    i = 0;
    c->forks = malloc(sizeof(pthread_mutex_t) * c->total);
    if (!c->forks)
        return(write_error("Could not allocate space."));
    if (pthread_mutex_init(&c->meal_check, NULL))
		return (1);
    if (pthread_mutex_init(&c->declare, NULL))
        return (1);
    while (i < c->total)
    {
        if (pthread_mutex_init(&c->forks[i], NULL))
            return(write_error("Mutex could not be created"));
        i++;
    }
    return (0);
 }

 void exit_plan(t_individual *i)
 {
    int it;

    it = -1;
    while(++it < i->c->total)
        pthread_join(i[it].thread, NULL);
    it = -1;
    while(++it < i->c->total)
        pthread_mutex_destroy(&(i->c->forks[it]));
    pthread_mutex_destroy(&(i->c->declare));
 }*/

 int initialise_collective(t_collective *c, int argc, char **argv)
 {
     if (argc < 5 || argc > 6)
         return(write_error("Arguments provided not within bounds."));
 	if (conv_assign(argv[1], &c->total) || c->total == 0
 		|| conv_assign(argv[2], &c->threshold) || c->threshold == 0
 		|| conv_assign(argv[3], &c->eat) || c->eat == 0
 		|| conv_assign(argv[4], &c->sleep) || c->sleep == 0)
         return(write_error("Invalid arguments provided."));
 	if (argc == 6 && (conv_assign(argv[5], &c->total_meals)
 		|| c->total_meals == 0))
         return(write_error("Invalid arguments provided."));
 	else if (argc == 5)
 		c->total_meals = -1;
    c->ate = 0;
    c->dead = 0;
    c->all_ate = 0;
     return (0);
 }

 t_individual *initialise_individual(t_collective *c, t_individual *i, int argc, char **argv)
 {
    int it;

    it = c->total;
    i = malloc(sizeof(t_individual) * c->total);
    if (!i)
        return(write_error("Could not allocate space."));
     while (--it >= 0)//< c->total)
     {
        i[it].c = c;
        i[it].Id = it;//+1;
        i[it].f1 = it;
        i[it].f2 = (it + 1) % c->total;
        printf("p%d\n", i[it].Id);
     }
     return (i);
 }

 int initialise_mutex(t_collective *c, t_individual *i)
 {
    int it;
    
    it = 0;
    c->forks = malloc(sizeof(pthread_mutex_t) * c->total);
    if (!c->forks)
        return(write_error("Could not allocate space."));
    if (pthread_mutex_init(&c->meal_check, NULL))
		return (1);
    if (pthread_mutex_init(&c->declare, NULL))
        return (1);
    while (it < c->total)
    {
        if (pthread_mutex_init(&c->forks[it], NULL))
            return(write_error("Mutex could not be created"));
        //printf("%d\n", i[it].Id);
        it++;
    }
    //printf("here\n");
    return (0);
 }

 void exit_plan(t_individual *i)
 {
    int it;

    it = -1;
    while(++it < i->c->total)
        pthread_join(i[it].thread, NULL);
    it = -1;
    while(++it < i->c->total)
        pthread_mutex_destroy(&(i->c->forks[it]));
    pthread_mutex_destroy(&(i->c->declare));
 }