#ifndef __Z_KINEMATICS__
#define __Z_KINEMATICS__
typedef struct {
	float L0;
	float L1;
	float L2;
	float L3;
	
	float servo_angle[6];	//0�ŵ�4�Ŷ���ĽǶ�
	float servo_range[6];		//����Ƕȷ�Χ
	float servo_pwm[6];		//0�ŵ�4�Ŷ���ĽǶ�
}kinematics_t;

void setup_kinematics(float L0, float L1, float L2, float L3, kinematics_t *kinematics);
int kinematics_analysis(float x, float y, float z, float Alpha, kinematics_t *kinematics);

#endif


