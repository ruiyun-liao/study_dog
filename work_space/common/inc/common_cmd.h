#ifndef __COMMON_CMD_H__
#define __COMMON_CMD_H__

typedef void (*cmd_callback_t)(int, char **);
typedef struct 
{
    char *cmd_string;
    char *cmd_help;
    cmd_callback_t callback;
}cmd_info_item_t;

#ifdef __cplusplus
extern "C" {
#endif

void common_cmd_loop(void);
void common_cmd_register(cmd_info_item_t cmd_list);

#ifdef __cplusplus
}
#endif

#endif