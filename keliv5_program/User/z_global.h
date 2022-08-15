#ifndef __TB_GLOBAL_H__
#define __TB_GLOBAL_H__

#include "stm32f10x_conf.h"


extern u8 AI_mode;
extern u8 group_do_ok;


#define DJ_NUM 8

typedef struct {
	uint8_t 	valid;//有效 TODO	
	uint16_t 	aim;	//执行目标
	uint16_t 	time;	//执行时间		
	float 		cur;	//当前值
	float 		inc;	//增量	
}duoji_t;


#define PRE_CMD_SIZE 128
typedef struct {
	u32 version;
	u32 dj_record_num;
	u8  pre_cmd[PRE_CMD_SIZE + 1];
	int dj_bias_pwm[DJ_NUM+1];
	u8 color_base_flag;
	int color_red_base;
	int color_grn_base;
	int color_blu_base;
}eeprom_info_t;



extern duoji_t duoji_doing[DJ_NUM];
extern uint8_t duoji_index1;
extern uint8_t tim2_stop;

#define CMD_RETURN_SIZE 1024
extern u8 cmd_return[CMD_RETURN_SIZE];
#define UART_BUF_SIZE 1024
extern u8 uart_receive_buf[UART_BUF_SIZE], uart1_get_ok, uart1_mode;
extern eeprom_info_t eeprom_info;

void tb_global_init(void);
uint16_t str_contain_str(unsigned char *str, unsigned char *str2);
int abs_int(int int1);
void selection_sort(int *a, int len);

#endif


