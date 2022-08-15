#ifndef __Z_KINEMATICS__
#define __Z_KINEMATICS__
typedef struct {
	float L0;
	float L1;
	float L2;
	float L3;
	
	float servo_angle[6];	//0号到4号舵机的角度
	float servo_range[6];		//舵机角度范围
	float servo_pwm[6];		//0号到4号舵机的角度
}kinematics_t;

void setup_kinematics(float L0, float L1, float L2, float L3, kinematics_t *kinematics);
int kinematics_analysis(float x, float y, float z, float Alpha, kinematics_t *kinematics);

#endif


