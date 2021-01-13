#ifndef __COMMON_CMD_PARSE_H__
#define __COMMON_CMD_PARSE_H__

#ifdef __cplusplus
extern "C" {
#endif

int mcmd_parse_params(char *params, char *argv[], int argvs, const char *dividers);

#ifdef __cplusplus
}
#endif

#endif