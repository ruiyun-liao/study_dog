#include <stdio.h>

#include "common_cmd.h"

static cmd_info_item_t g_common_cmd_list[] = {
    {"help",   NULL,    NULL},
};

static cmd_info_item_t *g_app_cmd_list = NULL;


void common_cmd_loop(void)
{
    
}

void common_cmd_register(cmd_info_item_t cmd_list)
{
    g_app_cmd_list = cmd_list;
}

