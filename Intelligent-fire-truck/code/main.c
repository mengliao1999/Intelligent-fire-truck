		            			    
**********************************************************************************/
#include <reg52.h> //51头文件
#include <HJ-2WD.h>//HJ-2WD智能小车配置文件
unsigned char pwm_left_val = 140;//左电机占空比值 取值范围0-170，0最快
unsigned char pwm_right_val = 150;//右电机占空比值取值范围0-170 ,0最快
unsigned char pwm_t;//周期
unsigned char control=0X01;//车运动控制全局变量，默认开机为停车状态
void delay(unsigned int z)//毫秒级延时
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}	
/*小车前进*/
void forward()
{
	left_motor_go; //左电机前进
	right_motor_go; //右电机前进
}
/*小车左转*/
void left_run()
{
	left_motor_stops; //左电机停止
	right_motor_go; //右电机前进	
}
/*小车右转*/
void right_run()
{
	right_motor_stops;//右电机停止
	left_motor_go;    //左电机前进
}

void left_d()
{
	left_motor_back; //左电机停止
	right_motor_go; //右电机前进	
}

void right_d()
{
	left_motor_go; //左电机停止
	right_motor_back; //右电机前进	
}


/*PWM控制使能 小车后退*/
void backward()
{
	left_motor_back; //左电机后退
	right_motor_back; //右电机后退	
}
void stop()
{
		left_motor_stops; //左电机后退
	right_motor_stops; //右电机后退	
}

//定时器0中断
void timer0() interrupt 1
{
	pwm_t++;//周期计时加
	if(pwm_t == 255)
		pwm_t = EN1 = EN2 = 0;
	if(pwm_left_val == pwm_t)//左电机占空比	
		EN1 = 1;		
	if(pwm_right_val == pwm_t)//右电机占空比
		EN2 = 1;			 
}
 /******************************************************************/
/* 串口中断程序*/
/******************************************************************/
void UART_SER () interrupt 4
{
	unsigned char n; 	//定义临时变量

	if(RI) 		//判断是接收中断产生
	{
		RI=0; 	//标志位清零
		n=SBUF; //读入缓冲区的值

		control=n;
		if((n >= 51) && (n <= 150))//左电机调速0~100个档位 手机端软件进行调节
			pwm_left_val = 170-((n-50)*1.7);	
		if((n >= 151) && (n <= 250))	  //右电机调速0~100个档位 手机端软件进行调节
			pwm_right_val = 170-((n-150)*1.7);
	}

}

void T0_init()
{
	TMOD |= 0x02;//8位自动重装模块
	TH0 = 220;
	TL0 = 220;//11.0592M晶振下占空比最大比值是256,输出100HZ
	TR0 = 1;//启动定时器0
	ET0 = 1;//允许定时器0中断
	EA	= 1;//总中断允许	
}

//蓝牙初始化
void boothint(void)
{
   
   	SCON = 0x50; 	// SCON: 模式1, 8-bit UART, 使能接收
	TMOD |= 0x20;
	TH1=0xfd; 		//波特率9600 初值
	TL1=0xfd;
	TR1= 1;
	EA = 1;	    //开总中断
	ES= 1; 			//打开串口中断


}
//小车自由行函数
void zuc(void)
	{
	forward();	 //调用前进函数
	delay(200);	
	right_d();	 //调用小车右转	函数
	delay(200);	
	backward();
	delay(200);	
	left_d();
	delay(200);	
	}
//小车循迹函数
void cz(void)
{
			//巡黑线 有信号为0 白线  没有信号为1 黑线

              if(Left_cg==0&&Right_cg==0)

			  forward();	 //调用前进函数

			  else
			 {		
			 	if(Left_cg==1&&Right_cg==1)

			  {
			  stop();   //调用停止函数
			  }
				      if(Left_cg==1&&Right_cg==0)	    //左边检测到黑线
			 	 
			  {	 	 
			 	  left_d();		  //调用小车左转  函数
			   }
			   
			   if(Right_cg==1&&Left_cg==0)		//右边检测到黑线
				  
			  {	        
				right_d();		   //调用小车右转	函数
			   }

			}
}

//小车红外避障函数
void pz(void)
{
			 //有信号为0 有障  没有信号为1 前面没有物体

              if(Left_be==1&&Right_be==1)  //前面没有物体小车前进

			  {
			  forward();   //调用前进函数
			  }

				  if(Left_be==0&&Right_be==0)	 //两个传感器同时检测到物体小车停车

			  {
			  //stop();   //调用停止函数
			  backward();//
			  delay(50);
              right_d();		   //调用小车右转	函数
			  delay(30);
			  }
			 			  
			  if(Left_be==0&&Right_be==1)	    //左边检测到物体
			 	 
			  {	 	 
			 	right_d();		   //调用小车右转	函数
			   }
			   
			   if(Right_be==0&&Left_be==1)		//右边检测到物体
				  
			  {	        
				left_d();		  //调用小车左转  函数
			   }
}
//小车循迹灭火函数
void mf(void)
{
             //巡黑线 有信号为0 白线  没有信号为1 黑线
   			 //有火焰信号=0   没有火焰信号=1 

              if(Left_cg==0&&Right_cg==0)

			  forward();	 //调用前进函数

			  else
			 {		
			 	if(Left_cg==1&&Right_cg==1)

			  {
			  stop();   //调用停止函数
			  }
				      if(Left_cg==1&&Right_cg==0)	    //左边检测到黑线
			 	 
			  {	 	 
			 	  left_d();		  //调用小车左转  函数
			   }
			   
			   if(Right_cg==1&&Left_cg==0)		//右边检测到黑线
				  
			  {	        
				right_d();		   //调用小车右转	函数
			   }
			    if(M_0_led==0)		//火焰传感器测到火
				  {	  
				    stop();		//调用电机停止函数
					DJ=0;	   //打开风扇灭火
					delay(200);		//
					DJ=1;	   //关掉gooo风扇
				    stop();		//调用电机停止函数
				    delay(100);		//？？毫秒
				  }

			}
}

//小车蓝牙函数
void bt(void)
{
if(control>0X07)//如果成立，则表示接收的命令不在运行命令内
	   {
	   	stop();	//  停车 
	   }
		switch(control)
		{
			case 0X02:	forward();	break;	//前进
			case 0X03:	backward();	break;	//后退
			case 0X04:	left_run();	break;	//左转
			case 0X05:	right_run();	break;//右转
			case 0X01:	stop();		break;//停车
			case 0X06:	left_d();	break;//左旋转
			case 0X07:	right_d();	break;//右旋转
			case 0X08:	beep = 0;	break;//鸣笛
			case 0X09:	beep = 1;	break;//停止鸣笛
		}
}

//小车WIFI函数	  需要在上位机控制端修改指令 原FF000000FF 改成 00 FF000100FF 改成01   FF000200FF  改成03 
// FF000400FF 改成04 FF000500FF 改成05  FF000600FF 改成06  FF000700FF 改成07
void wifi(void)
{
if(control>0X07)//如果成立，则表示接收的命令不在运行命令内
	   {
	   	stop();	//  停车 
	   }
		switch(control)
		{
			case 0X02:	forward();	break;	//前进
			case 0X03:	backward();	break;	//后退
			case 0X04:	left_run();	break;	//左转
			case 0X05:	right_run();	break;//右转
			case 0X01:	stop();		break;//停车
			case 0X06:	left_d();	break;//左旋转
			case 0X07:	right_d();	break;//右旋转
			case 0X08:	beep = 0;	break;//鸣笛
			case 0X09:	beep = 1;	break;//停止鸣笛
		}
}

void key()
{
	for(;;)	//死循环
	{
		if(key_s1 == 0)// 实时检测S1按键是否被按下
		{
			delay(5); //软件消抖
			if(key_s1 == 0)//再检测S1是否被按下
			{
				while(!key_s1);//松手检测
			   	while(1)
				{
				 zuc();	   //调用小车自由行函数
				}
				break;		//退出FOR死循环
			}
		}
				if(key_s2 == 0)// 实时检测S2按键是否被按下
		{
			delay(5); //软件消抖
			if(key_s2 == 0)//再检测S2是否被按下
			{
				while(!key_s2);//松手检测
                while(1)
				{				 
				 cz();	   //调用小车循迹函数
				}
				break;		//退出FOR死循环
			}
		}
			if(key_s3 == 0)// 实时检测S3按键是否被按下
		{
			delay(5); //软件消抖
			if(key_s3 == 0)//再检测S3是否被按下
			{
				while(!key_s3);//松手检测
                while(1)
				{	 
				 pz();	   //调用小车红外避障函数
				}
				break;		//退出FOR死循环
			}
		}
		if(key_s4 == 0)// 实时检测S4按键是否被按下
		{
			delay(5); //软件消抖
			if(key_s4 == 0)//再检测S4是否被按下
			{
				while(!key_s4);//松手检测
                while(1)
				{	 
				 mf();   //调用小车循迹灭火函数
				 //bt();	   //调用小车蓝牙函数
				}
				break;		//退出FOR死循环
			}
		}
	}	
}

void main()
{

	boothint();
	T0_init();//定时器0初始化，产生PWM信号
	while(1)
	{
	 //zuc();	   //调用小车自由行函数
	 //cz();	   //调用小车循迹函数
	 //pz();	   //调用小车红外避障函数
	 //mf();   //调用小车循迹灭火函数
	 //bt();	   //调用小车蓝牙函数
	 //wifi();
	   key();  //按下s1 启动小车自由行 按下s2启动小车循迹  	按下s3（蜂鸣器会响）启动红外避障  按下s4启动 循迹灭火
			   //每次转换程序时要按一下复位，再按启动按钮，如果需要停止请按一下复位。
	}
}