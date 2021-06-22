#include<reg52.h>

sbit r0=P2^0;   //Rows Declared
sbit r1=P2^1;
sbit r2=P2^2;
sbit r3=P2^3;

sbit c0=P2^5;   //Coulombs declared
sbit c1=P2^6;
sbit c2=P2^7;

sbit en=P3^6;   //Lcd control pins declared
sbit rs=P3^5;
sbit rw=P3^7;


sbit motor_pin_1=P0^0;//for motor
sbit motor_pin_2=P0^1;



char t1[]="Enter Password";  //String displayed on 16x2 lcd screen
char t2[]="Access Denied";
char t3[]="Access Granted";

void delay(unsigned int no)   //Delay function generating variable delay
{
unsigned int i,j;
for(j=0;j<=no;j++){}
for(i=0;i<=1000;i++){}
}


void lcdcmd(unsigned int  command){  //Lcd command function
P1=command;
rw=0;
rs=0;
en=0;
delay(3000);
en=1;
delay(3000);
en=0;
}

void lcddata(char data1)     //Lcd data function
{
P1=data1;
rw=0;
rs=1;
en=0;
delay(3000);
en=1;
delay(3000);
en=0;
}

void lcdint()  // Lcd initializing function
{
lcdcmd(0x30);	delay(3000);	lcdcmd(0x30);	delay(3000);	lcdcmd(0x30);	delay(3000);
lcdcmd(0x30);	delay(3000);	lcdcmd(0x30);	delay(3000);	lcdcmd(0x38);	delay(3000);
lcdcmd(0x01);	delay(3000);	lcdcmd(0x0F);	delay(3000);	lcdcmd(0x80);	delay(3000);
}

int keypad()  //Lcd keypad scanning function
{
int state=0;
char c='a';
while(c!='s'){
r0=0;r1=1;r2=1;r3=1;
if(c0==0){lcddata('*');delay(20000);c='s';return state=1;}//1
 if(c1==0){lcddata('*');delay(20000);c='s';return state=2;}//2
 if(c2==0){lcddata('*');delay(20000);c='s';return state=3;}//3

r0=1;r1=0;r2=1;r3=1;
if(c0==0){lcddata('*');delay(20000);c='s';return state=4;}//4
 if(c1==0){lcddata('*');delay(20000);c='s';return state=5;}//5
 if(c2==0){lcddata('*');delay(20000);c='s';return state=6;}//6

r0=1;r1=1;r2=0;r3=1;
if(c0==0){lcddata('*');delay(20000);c='s';return state=7;}//7
 if(c1==0){lcddata('*');delay(20000);c='s';return state=8;}//8
 if(c2==0){lcddata('*');delay(20000);c='s';return state=9;}//9

r0=1;r1=1;r2=1;r3=0;
if(c0==0){lcddata('*');delay(20000);c='s';return state=10;}//*
 if(c1==0){lcddata('*');delay(20000);c='s';return state=11;}//0
 if(c2==0){lcddata('*');delay(20000);c='s';return state=12;}//#

}
}

void main() //Projecct main function
{
	unsigned int y=0;
	unsigned int x=0;
int j[4]=0;
unsigned int i=0;
int k[4]={1,2,3,4};
P1=0x00;
P2=0xF0;
P3=0x00;
P0=0xF0;	
lcdint();   //Initialize 16x2 Lcd
do{
	lcdcmd(0x01);// clear screen
	lcdcmd(0x80);//cursor at home position
i=0;
//lcdcmd(0x0C);// display on cursor off
while(t1[i]!='\0')  //Display well come message on 16x2 lcd sccreen
{
lcddata(t1[i]);
i++;
}


lcdcmd(0xC0);     //Control transfer to second row of lcd


for(i=0;i<4;i++)
{
j[i]=keypad();
	
}
lcdcmd(0x01);// clear screen
for(i=0;i<4;i++)
{
if (j[i] != k[i])
{
y=1;
}
}

if(y==0)
{
		i=0;
	motor_pin_1 = 1;
    motor_pin_2 = 0; //Rotates Motor Anti Clockwise
    delay(300000);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
    motor_pin_1 = 1;
    motor_pin_2 = 1; //Stops Motor
	while(t3[i]!='\0')  //Access Granted
{
lcddata(t3[i]);
i++;
}
		delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
  motor_pin_1 = 0;
    motor_pin_2 = 1; //Rotates Motor Clockwise
   delay(300000);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
	delay(999999);
    motor_pin_1 = 1;
    motor_pin_2 = 1; // Stops Motor


}
else
{ 
i=0;
while(t2[i]!='\0')  //Access Denied
{
lcddata(t2[i]);
i++;
}
}
  
} while(1);
}

