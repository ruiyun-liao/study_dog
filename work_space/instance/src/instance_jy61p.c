#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "instance_jy61p.h"
#include "arch_serial.h"
#include "common_log.h"

#define RECV_DATA_PACKET_LEN           11
#define RECV_DATA_START_CODE           0x55
#define PACKET_TYPE_ACCELERATED_SPEED  0x51
#define PACKET_TYPE_ANGULAR_SPEED      0x52
#define PACKET_TYPE_ANGLE              0x53

#define PACKET_INDEX_START  0
#define PACKET_INDEX_TYPE   1
#define PACKET_INDEX_XL     2
#define PACKET_INDEX_XH     3
#define PACKET_INDEX_YL     4
#define PACKET_INDEX_YH     5
#define PACKET_INDEX_ZL     6
#define PACKET_INDEX_ZH     7
#define PACKET_INDEX_TL     8
#define PACKET_INDEX_TH     9

static int  g_jy61p_serial_fd = -1;
static bool g_jy61p_serial_en = false;

static double g_temperature = 0;
static double g_angle_roll_x = 0;
static double g_angle_pitch_y = 0;
static double g_angle_yaw_z = 0;

static int data_packet_check(char *data_packet, int packet_len)
{
    int i = 0, sum = 0, ret;
    for(i = 0; i < packet_len - 1; i++)
    {
        sum += data_packet[i];
    }
    sum = sum % (1 << 8);
    if(sum == data_packet[i])
    {
        ret = ERROR_CODE_SUCCEED;
    }
    else
    {
        printf("packet error\r\n");
        ret = ERROR_CODE_FAIL;
    }

    return ret;
}

static void data_packet_deal(char *data_packet, int packet_len)
{
    if(ERROR_CODE_SUCCEED != data_packet_check(data_packet, packet_len)) return;
    if(PACKET_TYPE_ANGLE == data_packet[PACKET_INDEX_TYPE])
    {
        short temp;
        temp = (data_packet[PACKET_INDEX_TH] << 8) | data_packet[PACKET_INDEX_TL];
        g_temperature = temp / 340.0 + 36.53;

        temp = (data_packet[PACKET_INDEX_XH] << 8) | data_packet[PACKET_INDEX_XL];
        g_angle_roll_x = temp / 32768.0 * 180;

        temp = (data_packet[PACKET_INDEX_YH] << 8) | data_packet[PACKET_INDEX_YL];
        g_angle_pitch_y = temp / 32768.0 * 180;

        temp = (data_packet[PACKET_INDEX_ZH] << 8) | data_packet[PACKET_INDEX_ZL];
        g_angle_yaw_z = temp / 32768.0 * 180;

        LOG_PRINT_WARN("temp = [%f], roll_x = [%f], pitch_y = [%f], yaw_z = [%f]", 
                               g_temperature, g_angle_roll_x, g_angle_pitch_y, g_angle_yaw_z);
    }

}

void instance_jy61p_loop(void)
{
    char data_packet[RECV_DATA_PACKET_LEN] = {0};
    int packet_len = 0;
    if(g_jy61p_serial_en)
    {
        if(arch_serial_data_avail(g_jy61p_serial_fd) >= RECV_DATA_PACKET_LEN)
        {
            while((arch_serial_data_avail(g_jy61p_serial_fd) > 0) && RECV_DATA_START_CODE != arch_serial_getchar(g_jy61p_serial_fd));
            if(arch_serial_data_avail(g_jy61p_serial_fd) > 0)
            {
                data_packet[packet_len++] = RECV_DATA_START_CODE;
                for(;arch_serial_data_avail(g_jy61p_serial_fd) > 0 && RECV_DATA_PACKET_LEN > packet_len; packet_len++)
                {
                    data_packet[packet_len] = arch_serial_getchar(g_jy61p_serial_fd);
                }
                if(RECV_DATA_PACKET_LEN == packet_len)
                {
                    data_packet_deal(data_packet, packet_len);
                }
            }
            
        }
        
    }
}

int instance_jy61p_init(void)
{
    if ((g_jy61p_serial_fd = arch_serial_open("/dev/ttyAMA0", 115200)) < 0)
    {
        fprintf(stderr, "open serial device fail: %s\r\n", strerror(errno));
        return -1;
    }

    printf("jy61p init\r\n");

    g_jy61p_serial_en = true;
    return 0;
}

int instance_jy61p_deinit(void)
{
    if(arch_serial_close(g_jy61p_serial_fd) < 0)
    {
        fprintf(stderr, "close serial device fail\r\n");
        return -1;
    }
    printf("jy61p deinit\r\n");
   
    g_jy61p_serial_en = false;
    return 0;
}

