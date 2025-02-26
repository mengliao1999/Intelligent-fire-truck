#ifndef __HJ-2WD_H__
#define __HJ-2WD_H__

	/*电机驱动IO定义*/
	sbit IN1=P1^0;
	sbit IN2=P1^1;
	sbit IN3=P1^2;
	sbit IN4=P1^3;
	sbit EN1=P1^4;
	sbit EN2=P1^5;
sbit Left_cg = P3^6;//左寻迹信号 为0 没有识别到黑线 为1识别到黑线
sbit Right_cg = P3^5;//右寻迹信号	为0 没有识别到黑线 为1识别到黑线
sbit Left_be = P3^7;//左避障信号 为0 识别障碍物 为1没有识别到障碍物
sbit Right_be = P3^4;//右避障信号	为0 识别障碍物 为1没有识别到障碍物



/*按键定义*/
sbit key_s1 = P2^4;
sbit key_s2 = P2^5;
sbit key_s3 = P2^6;
sbit key_s4 = P2^7;
sbit beep = P2^6;//蜂鸣器

#define left_motor_en		EN1 = 1	//左电机使能
#define right_motor_en		EN2 = 1	//右电机使能

//灭火IO口定义
sbit 	DJ=P1^6;	 //风扇电机输出控制
#define M_0_led           P1^7	 // 火焰传感器  


#define left_motor_stops	IN1 = 0, IN2 = 0//左电机停止
#define right_motor_stops	IN3 = 0, IN4 = 0//右电机停止

#define left_motor_go		IN1 = 0, IN2 = 1//左电机正传
#define left_motor_back		IN1 = 1, IN2 = 0//左电机反转
#define right_motor_go		IN3 = 1, IN4 = 0//右电机正传
#define right_motor_back	IN3 = 0, IN4 = 1//右电机反转

#endif