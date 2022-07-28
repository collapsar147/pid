#include "stdio.h"
#include "stdlib.h"
#include "math.h"

struct _pid
{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_next;            //定义上一个偏差值
	float err_nexts;			//上一个偏差值临时输出值
    float err_last;            //定义最上前的偏差值
	float err_lasts;
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
	float increasement;			//当下计算周期增量
}pid;	//在最后的pid相当于_pid类型的变量pid

void PID_init()
{
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.err_next=0.0; 
    pid.Kp=0.2;
    pid.Ki=0.7;
    pid.Kd=0.2;
}

float PID_realize(float speed)
{
	float incrementSpeed=0;
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    incrementSpeed=pid.Kp*(pid.err-pid.err_next)+pid.Ki*pid.err+pid.Kd*(pid.err-2*pid.err_next+pid.err_last);
	pid.increasement=incrementSpeed;
    pid.ActualSpeed+=incrementSpeed;
	pid.err_lasts=pid.err_last;
    pid.err_last=pid.err_next;
	pid.err_nexts=pid.err_next;
    pid.err_next=pid.err;
    return pid.ActualSpeed;
}

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
        float speed=PID_realize(200);
        fprintf(fp,"actual speed[%d]=%f,set speed[%d]=%f,increasement[%d]=%f,err[%d]=%f,err_next[%d]=%f,err_last[%d]=%f\n",
			count,speed,count,pid.SetSpeed,count,pid.increasement,count,pid.err,count,pid.err_nexts,count,pid.err_lasts);
		//fprintf(fp,"%f,%f,%f,%f,%f,%f\n",speed,pid.SetSpeed,pid.increasement,pid.err,pid.err_nexts,pid.err_lasts);
        count++;
    }
	close(fp);	//close fp after using
	return 0;
}