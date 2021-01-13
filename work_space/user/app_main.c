#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "instance_jy61p.h"

int main(int argc, char **argv)
{ 
    instance_jy61p_init();
    while(1)
    {
        instance_jy61p_loop();
    }
    return 0;
}