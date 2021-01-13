#ifndef __COMMON_LOG_H__
#define __COMMON_LOG_H__

#include <stdio.h>

typedef enum
{
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_OFF
}log_level_t;
    
#define   LOG_COLOR_RED        "\033[0;31m"
#define   LOG_COLOR_GRE        "\033[0;32m"
#define   LOG_COLOR_YEL        "\033[0;33m"
#define   LOG_COLOR_OFF        "\033[0m"

#define   osa_print     printf

extern log_level_t g_log_level;

void log_print_begin(const char *color); 
void log_print_end(const char *color);

#define LOG_PRINT_DEBUG(_fmt_, ...) \
        if(g_log_level <= LOG_LEVEL_DEBUG){\
            log_print_begin(LOG_COLOR_OFF);\
            osa_print(" [D] "_fmt_, ##__VA_ARGS__);\
            log_print_end(LOG_COLOR_OFF);\
        }

#define LOG_PRINT_INFO(_fmt_, ...) \
        if(g_log_level <= LOG_LEVEL_INFO){\
            log_print_begin(LOG_COLOR_GRE);\
            osa_print(" [I] "_fmt_, ##__VA_ARGS__);\
            log_print_end(LOG_COLOR_OFF);\
        }

#define LOG_PRINT_WARN(_fmt_, ...) \
        if(g_log_level <= LOG_LEVEL_WARNING){\
            log_print_begin(LOG_COLOR_YEL);\
            osa_print(" [W] "_fmt_, ##__VA_ARGS__);\
            log_print_end(LOG_COLOR_OFF);\
        }

#define LOG_PRINT_ERROR(_fmt_, ...) \
        if(g_log_level <= LOG_LEVEL_ERROR){\
            log_print_begin(LOG_COLOR_RED);\
            osa_print(" [E] "_fmt_, ##__VA_ARGS__);\
            log_print_end(LOG_COLOR_OFF);\
        }


#endif