#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "common_cmd_parse.h"

static int mcmd_unescape(const char *in, size_t in_len, char* out, size_t out_len)
{
	size_t decode_len = 0;

	for(int i=0; i<in_len; i++){
		if(in[i] == '\\' && (i+1) < in_len){
			switch(in[++i]){
			case 'u' :
				if(  ((i+4) < in_len)
				   &&(in[i+1] == '0')
				   &&(in[i+2] == '0')
				   &&(in[i+3] == '2')
				   &&(in[i+4] == '0')){
					if(out && decode_len < out_len){
						out[decode_len] = ' ';
					}
					i += 4;
				}
				else{
					if(out && decode_len < out_len){
						out[decode_len] = in[i-1];
					}
					decode_len++;
					if(out && decode_len < out_len){
						out[decode_len] = in[i];
					}
				}
				break;
			default:
				if(out && decode_len < out_len){
					out[decode_len] = in[i-1];
				}
				decode_len++;
				if(out && decode_len < out_len){
					out[decode_len] = in[i];
				}
				break;
			}
		}
		else{
			if(out && decode_len < out_len){
				out[decode_len] = in[i];
			}
		}
		decode_len++;
	}

	return decode_len;
}


static bool is_divider(char c, const char *dividers, int dividers_len)
{
	for(int i = 0; i < dividers_len; i++){
		if(c == dividers[i]){
			return true;
		}
	}
	return false;
}
/**
 * @brief  Parse params to argv
 *
 * @param  cmd
 * @param  argv     array for argv
 * @param  argvs  	array length
 * @param  dividers  string of divider, length must less than 127
 *
 * @return
 *     - count of argv (>=0)
 */
int mcmd_parse_params(char *params, char *argv[], int argvs, const char *dividers)
{
	if(NULL == params || NULL == argv || 0 == argvs){
		return 0;
	}

	int dividers_len = 0;
	if(NULL == dividers){
		dividers = " ";
		dividers_len = sizeof(" ") - 1;
	}
	else{
		dividers_len = strnlen(dividers, 127);
	}

	int argc = 0;

	bool in_arg = false;
	bool in_str = false;
	bool no_escape = true;
	for(int i=0; argc < argvs; i++){
		if('\0' == params[i]){
			if(in_str){
				break;
			}
			if (in_arg) {
				in_arg = false;
				argc++;
			}
			break;
		}
		else if(is_divider(params[i], dividers, dividers_len)){
			if(in_str){
				continue;
			}
			if (in_arg) {
				in_arg = false;
				argc++;
				params[i] = '\0';
			}
		}
		else{
			if(!in_arg){
				in_arg = true;
				argv[argc] = &params[i];
				if('"' == params[i]){
					//if arg's first c is ", arg is a str
					in_str = true;
					no_escape = true;
				}
			}
			else if(in_str){
				if('"' == params[i]){
					if(no_escape){
						in_str = false;
					}
				}
				else if('\\' == params[i]){
					no_escape = !no_escape;
				}
				else{
					no_escape = true;
				}
			}
		}
	}

	for(int i=0; i < argc; i++){
		//decode
		int arg_len = strlen(argv[i]);
		arg_len = mcmd_unescape(argv[i], arg_len, argv[i], arg_len);
		argv[i][arg_len] = '\0';
	}

	return argc;
}