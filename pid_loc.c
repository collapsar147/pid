#include "math.h"
#include "stdio.h"
#include "stdlib.h"

struct _pid
{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_last;            //定义上一个偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float voltage;          //定义电压值（控制执行器的变量）
    float integral;            //定义积分值
}pid;

float PID_realize(float speed);
void PID_init();

int main()
{
	int count=0;
	FILE* fp;
	fp=fopen("data.txt","w+");
	if(fp==NULL)
	{
		printf("File cannot open! " ); 
		exit(0);
	}
    fprintf(fp,"System begin \n");
    PID_init();
    while(count<1000)
    {
        float speed=PID_realize(200.0);
        fprintf(fp,"speed[%d]=%f,voltage[%d]=%f\n",count,speed,count,pid.voltage);
        count++;
    }
	return 0;
}

float PID_realize(float speed)
{
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    pid.integral+=pid.err;
    pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.2;
    return pid.ActualSpeed;
}

void PID_init()
{
    printf("PID_init begin \n");
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.2;
    pid.Ki=0.015;
    pid.Kd=0.2;
    printf("PID_init end \n");
}