#include "philosophers.h"

int main(int argc, char **argv)
{
    t_collective    collective;

    if (initialise_collective(&collective, argc, argv))
        return (1);
    return(0);
}