#include "z_global.h"
#include "stm32f10x_conf.h"


duoji_t duoji_doing[DJ_NUM];
u8 cmd_return[CMD_RETURN_SIZE];
u8 uart_receive_buf[UART_BUF_SIZE], uart1_get_ok, uart1_mode;
eeprom_info_t eeprom_info;
u8 AI_mode = 255;
u8 group_do_ok = 1;


void tb_global_init(void) {
	u8 i;
	//舵机控制初始化
	for(i=0;i<DJ_NUM;i++) {
		duoji_doing[i].aim = 1500;
		duoji_doing[i].cur = 1500;
		duoji_doing[i].inc = 0;
	}
	return;
}


uint16_t str_contain_str(unsigned char *str, unsigned char *str2) {
	unsigned char *str_temp, *str_temp2;
	str_temp = str;
	str_temp2 = str2;
	while(*str_temp) {
		if(*str_temp == *str_temp2) {
			while(*str_temp2) {
				if(*str_temp++ != *str_temp2++) {
					str_temp = str_temp - (str_temp2-str2) + 1;
					str_temp2 = str2;
					break;
				}	
			}
			if(!*str_temp2) {
				return (str_temp-str);
			}
			
		} else {
			str_temp++;
		}
	}
	return 0;
}

void selection_sort(int *a, int len) {
    int i,j,mi,t;
    for(i=0;i<len-1;i++) {
        mi = i;
        for(j=i+1;j<len;j++) {
            if(a[mi] > a[j]) {
                mi = j;    
            }    
        }    
		
        if(mi != i) {
            t = a[mi];
            a[mi] = a[i];
            a[i] = t;    
        }
    }
}

//int型 取绝对值函数
int abs_int(int int1) {
	if(int1 > 0)return int1;
	return (-int1);
}

