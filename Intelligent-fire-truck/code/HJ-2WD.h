#ifndef __HJ-2WD_H__
#define __HJ-2WD_H__

	/*�������IO����*/
	sbit IN1=P1^0;
	sbit IN2=P1^1;
	sbit IN3=P1^2;
	sbit IN4=P1^3;
	sbit EN1=P1^4;
	sbit EN2=P1^5;
sbit Left_cg = P3^6;//��Ѱ���ź� Ϊ0 û��ʶ�𵽺��� Ϊ1ʶ�𵽺���
sbit Right_cg = P3^5;//��Ѱ���ź�	Ϊ0 û��ʶ�𵽺��� Ϊ1ʶ�𵽺���
sbit Left_be = P3^7;//������ź� Ϊ0 ʶ���ϰ��� Ϊ1û��ʶ���ϰ���
sbit Right_be = P3^4;//�ұ����ź�	Ϊ0 ʶ���ϰ��� Ϊ1û��ʶ���ϰ���



/*��������*/
sbit key_s1 = P2^4;
sbit key_s2 = P2^5;
sbit key_s3 = P2^6;
sbit key_s4 = P2^7;
sbit beep = P2^6;//������

#define left_motor_en		EN1 = 1	//����ʹ��
#define right_motor_en		EN2 = 1	//�ҵ��ʹ��

//���IO�ڶ���
sbit 	DJ=P1^6;	 //���ȵ���������
#define M_0_led           P1^7	 // ���洫����  


#define left_motor_stops	IN1 = 0, IN2 = 0//����ֹͣ
#define right_motor_stops	IN3 = 0, IN4 = 0//�ҵ��ֹͣ

#define left_motor_go		IN1 = 0, IN2 = 1//��������
#define left_motor_back		IN1 = 1, IN2 = 0//������ת
#define right_motor_go		IN3 = 1, IN4 = 0//�ҵ������
#define right_motor_back	IN3 = 0, IN4 = 1//�ҵ����ת

#endif