		            			    
**********************************************************************************/
#include <reg52.h> //51ͷ�ļ�
#include <HJ-2WD.h>//HJ-2WD����С�������ļ�
unsigned char pwm_left_val = 140;//����ռ�ձ�ֵ ȡֵ��Χ0-170��0���
unsigned char pwm_right_val = 150;//�ҵ��ռ�ձ�ֵȡֵ��Χ0-170 ,0���
unsigned char pwm_t;//����
unsigned char control=0X01;//���˶�����ȫ�ֱ�����Ĭ�Ͽ���Ϊͣ��״̬
void delay(unsigned int z)//���뼶��ʱ
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}	
/*С��ǰ��*/
void forward()
{
	left_motor_go; //����ǰ��
	right_motor_go; //�ҵ��ǰ��
}
/*С����ת*/
void left_run()
{
	left_motor_stops; //����ֹͣ
	right_motor_go; //�ҵ��ǰ��	
}
/*С����ת*/
void right_run()
{
	right_motor_stops;//�ҵ��ֹͣ
	left_motor_go;    //����ǰ��
}

void left_d()
{
	left_motor_back; //����ֹͣ
	right_motor_go; //�ҵ��ǰ��	
}

void right_d()
{
	left_motor_go; //����ֹͣ
	right_motor_back; //�ҵ��ǰ��	
}


/*PWM����ʹ�� С������*/
void backward()
{
	left_motor_back; //��������
	right_motor_back; //�ҵ������	
}
void stop()
{
		left_motor_stops; //��������
	right_motor_stops; //�ҵ������	
}

//��ʱ��0�ж�
void timer0() interrupt 1
{
	pwm_t++;//���ڼ�ʱ��
	if(pwm_t == 255)
		pwm_t = EN1 = EN2 = 0;
	if(pwm_left_val == pwm_t)//����ռ�ձ�	
		EN1 = 1;		
	if(pwm_right_val == pwm_t)//�ҵ��ռ�ձ�
		EN2 = 1;			 
}
 /******************************************************************/
/* �����жϳ���*/
/******************************************************************/
void UART_SER () interrupt 4
{
	unsigned char n; 	//������ʱ����

	if(RI) 		//�ж��ǽ����жϲ���
	{
		RI=0; 	//��־λ����
		n=SBUF; //���뻺������ֵ

		control=n;
		if((n >= 51) && (n <= 150))//��������0~100����λ �ֻ���������е���
			pwm_left_val = 170-((n-50)*1.7);	
		if((n >= 151) && (n <= 250))	  //�ҵ������0~100����λ �ֻ���������е���
			pwm_right_val = 170-((n-150)*1.7);
	}

}

void T0_init()
{
	TMOD |= 0x02;//8λ�Զ���װģ��
	TH0 = 220;
	TL0 = 220;//11.0592M������ռ�ձ�����ֵ��256,���100HZ
	TR0 = 1;//������ʱ��0
	ET0 = 1;//����ʱ��0�ж�
	EA	= 1;//���ж�����	
}

//������ʼ��
void boothint(void)
{
   
   	SCON = 0x50; 	// SCON: ģʽ1, 8-bit UART, ʹ�ܽ���
	TMOD |= 0x20;
	TH1=0xfd; 		//������9600 ��ֵ
	TL1=0xfd;
	TR1= 1;
	EA = 1;	    //�����ж�
	ES= 1; 			//�򿪴����ж�


}
//С�������к���
void zuc(void)
	{
	forward();	 //����ǰ������
	delay(200);	
	right_d();	 //����С����ת	����
	delay(200);	
	backward();
	delay(200);	
	left_d();
	delay(200);	
	}
//С��ѭ������
void cz(void)
{
			//Ѳ���� ���ź�Ϊ0 ����  û���ź�Ϊ1 ����

              if(Left_cg==0&&Right_cg==0)

			  forward();	 //����ǰ������

			  else
			 {		
			 	if(Left_cg==1&&Right_cg==1)

			  {
			  stop();   //����ֹͣ����
			  }
				      if(Left_cg==1&&Right_cg==0)	    //��߼�⵽����
			 	 
			  {	 	 
			 	  left_d();		  //����С����ת  ����
			   }
			   
			   if(Right_cg==1&&Left_cg==0)		//�ұ߼�⵽����
				  
			  {	        
				right_d();		   //����С����ת	����
			   }

			}
}

//С��������Ϻ���
void pz(void)
{
			 //���ź�Ϊ0 ����  û���ź�Ϊ1 ǰ��û������

              if(Left_be==1&&Right_be==1)  //ǰ��û������С��ǰ��

			  {
			  forward();   //����ǰ������
			  }

				  if(Left_be==0&&Right_be==0)	 //����������ͬʱ��⵽����С��ͣ��

			  {
			  //stop();   //����ֹͣ����
			  backward();//
			  delay(50);
              right_d();		   //����С����ת	����
			  delay(30);
			  }
			 			  
			  if(Left_be==0&&Right_be==1)	    //��߼�⵽����
			 	 
			  {	 	 
			 	right_d();		   //����С����ת	����
			   }
			   
			   if(Right_be==0&&Left_be==1)		//�ұ߼�⵽����
				  
			  {	        
				left_d();		  //����С����ת  ����
			   }
}
//С��ѭ�������
void mf(void)
{
             //Ѳ���� ���ź�Ϊ0 ����  û���ź�Ϊ1 ����
   			 //�л����ź�=0   û�л����ź�=1 

              if(Left_cg==0&&Right_cg==0)

			  forward();	 //����ǰ������

			  else
			 {		
			 	if(Left_cg==1&&Right_cg==1)

			  {
			  stop();   //����ֹͣ����
			  }
				      if(Left_cg==1&&Right_cg==0)	    //��߼�⵽����
			 	 
			  {	 	 
			 	  left_d();		  //����С����ת  ����
			   }
			   
			   if(Right_cg==1&&Left_cg==0)		//�ұ߼�⵽����
				  
			  {	        
				right_d();		   //����С����ת	����
			   }
			    if(M_0_led==0)		//���洫�����⵽��
				  {	  
				    stop();		//���õ��ֹͣ����
					DJ=0;	   //�򿪷������
					delay(200);		//
					DJ=1;	   //�ص�gooo����
				    stop();		//���õ��ֹͣ����
				    delay(100);		//��������
				  }

			}
}

//С����������
void bt(void)
{
if(control>0X07)//������������ʾ���յ����������������
	   {
	   	stop();	//  ͣ�� 
	   }
		switch(control)
		{
			case 0X02:	forward();	break;	//ǰ��
			case 0X03:	backward();	break;	//����
			case 0X04:	left_run();	break;	//��ת
			case 0X05:	right_run();	break;//��ת
			case 0X01:	stop();		break;//ͣ��
			case 0X06:	left_d();	break;//����ת
			case 0X07:	right_d();	break;//����ת
			case 0X08:	beep = 0;	break;//����
			case 0X09:	beep = 1;	break;//ֹͣ����
		}
}

//С��WIFI����	  ��Ҫ����λ�����ƶ��޸�ָ�� ԭFF000000FF �ĳ� 00 FF000100FF �ĳ�01   FF000200FF  �ĳ�03 
// FF000400FF �ĳ�04 FF000500FF �ĳ�05  FF000600FF �ĳ�06  FF000700FF �ĳ�07
void wifi(void)
{
if(control>0X07)//������������ʾ���յ����������������
	   {
	   	stop();	//  ͣ�� 
	   }
		switch(control)
		{
			case 0X02:	forward();	break;	//ǰ��
			case 0X03:	backward();	break;	//����
			case 0X04:	left_run();	break;	//��ת
			case 0X05:	right_run();	break;//��ת
			case 0X01:	stop();		break;//ͣ��
			case 0X06:	left_d();	break;//����ת
			case 0X07:	right_d();	break;//����ת
			case 0X08:	beep = 0;	break;//����
			case 0X09:	beep = 1;	break;//ֹͣ����
		}
}

void key()
{
	for(;;)	//��ѭ��
	{
		if(key_s1 == 0)// ʵʱ���S1�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s1 == 0)//�ټ��S1�Ƿ񱻰���
			{
				while(!key_s1);//���ּ��
			   	while(1)
				{
				 zuc();	   //����С�������к���
				}
				break;		//�˳�FOR��ѭ��
			}
		}
				if(key_s2 == 0)// ʵʱ���S2�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s2 == 0)//�ټ��S2�Ƿ񱻰���
			{
				while(!key_s2);//���ּ��
                while(1)
				{				 
				 cz();	   //����С��ѭ������
				}
				break;		//�˳�FOR��ѭ��
			}
		}
			if(key_s3 == 0)// ʵʱ���S3�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s3 == 0)//�ټ��S3�Ƿ񱻰���
			{
				while(!key_s3);//���ּ��
                while(1)
				{	 
				 pz();	   //����С��������Ϻ���
				}
				break;		//�˳�FOR��ѭ��
			}
		}
		if(key_s4 == 0)// ʵʱ���S4�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s4 == 0)//�ټ��S4�Ƿ񱻰���
			{
				while(!key_s4);//���ּ��
                while(1)
				{	 
				 mf();   //����С��ѭ�������
				 //bt();	   //����С����������
				}
				break;		//�˳�FOR��ѭ��
			}
		}
	}	
}

void main()
{

	boothint();
	T0_init();//��ʱ��0��ʼ��������PWM�ź�
	while(1)
	{
	 //zuc();	   //����С�������к���
	 //cz();	   //����С��ѭ������
	 //pz();	   //����С��������Ϻ���
	 //mf();   //����С��ѭ�������
	 //bt();	   //����С����������
	 //wifi();
	   key();  //����s1 ����С�������� ����s2����С��ѭ��  	����s3�����������죩�����������  ����s4���� ѭ�����
			   //ÿ��ת������ʱҪ��һ�¸�λ���ٰ�������ť�������Ҫֹͣ�밴һ�¸�λ��
	}
}