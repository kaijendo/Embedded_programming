 #include<reg51.h>
sbit rs=P3^5;   //Register select (RS)
sbit rw=P3^7;   //Read write (RW) pin
sbit en=P3^6;   //Enable (EN) pin
char c[15]={"Lap Trinh Nhung"},command[]={0xCF,0xCE,0xCD,0xCC,0xCB,0xCA,0xC9,0xC8,0xC7,0xC6,0xC5,0xC4,0xC3,0xC2,0xC1,0xC0};

void delay(unsigned int time) {  
    unsigned int i,j;
    for(i=0;i<time;i++)
      for(j=0;j<5;j++);
}
// MARK: - Implement to LCD.
/// Function sending value to LCD
void lcdcmd(unsigned char value)  {
    P1=value;
    P3=0x40;
    delay(50);
    en=0;
    delay(50);
    return;
}
//Function sending value and register value to LCD.
void display(unsigned char value)  {
    P1=value;
    P3=0x60;
    delay(500);
    en=0;
    delay(50);
    return;
}
/// Function init LCD.
void lcdint(void)         
{
    P1=0x00;                 
    P3=0x00;
     delay(15000);
     display(0x30);
     delay(4500);
     display(0x30);
     delay(300);
     display(0x30);
     delay(650);
    lcdcmd(0x38);
    delay(50);
    lcdcmd(0x0C);
    delay(50);
    lcdcmd(0x01);
    delay(50);
    lcdcmd(0x06);
    delay(50);
    lcdcmd(0x80);
    delay(50);
}

/// Function Main.
void main()
{

char i,j;
char text[] ={"KTPM.K12B-Nhom 9"};
while(1){
int count=0,k=0,l=0,coun=0;
lcdint();
lcdcmd(0x01);
lcdcmd(0x80);
 while(text[count]!='\0')
 {
 display(text[count]);
 count++;
 }
delay(10000);
for(i=14;i>=0;i--)
{
  k=0;
  lcdcmd(command[coun]);
  for(j=i;j<=13;j++)
  {
  display(c[k]);
  delay(100);
  k++;
  if(i==0 && j==13)
  goto xyz;                  //IF string reaches the first matrix drop each character one by one                           //so it feels that the string is terminating

  }
  coun++;
}

xyz:

if(i==0 && j==13)
      {				
        while(k!=0)
           {
		   lcdcmd(0x01);
           lcdcmd(0xC0);   
	    for(i=k;i>=2;i--)
        {
        l=15-i;
        display(c[l]);
        delay(1000);
        }
          k--;
        }
	} 

}
}
