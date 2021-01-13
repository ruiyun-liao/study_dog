#include "common_log.h"
#include <time.h>

log_level_t g_log_level = LOG_LEVEL_DEBUG;

int get_time_local_string(char *time_str, size_t buf_len)
{
    time_t t;
    struct tm *tp;
    if((0 < time(&t)) && (NULL != (tp = localtime(&t))))
    {
        snprintf(time_str, buf_len, "%d/%02d/%02d %02d:%02d:%02d", 
            tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
    else
    {
        return -1;
    }
    return 0;
}

void log_print_begin(const char *color)
{
    char time_str[30] = {0};
    get_time_local_string(time_str, sizeof(time_str));

    if(color)
    {
        osa_print("%s%s ["__FILE__" %d]", color, time_str, __LINE__);
    }
    else
    {
        osa_print("%s", time_str);
    }
}

void log_print_end(const char *color)
{
    if(color)
    {
        osa_print("%s\r\n", color);
    }
    else
    {
        osa_print("\r\n");
    }
}



