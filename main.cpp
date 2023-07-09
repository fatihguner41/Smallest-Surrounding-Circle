#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>

struct coords
    {
        int x;
        int y;
        float uzaklikp[30];
        float uzaklikm[30];
    };
    
struct coordsf
{
	float x;
	float y;
}  ;

 coordsf splinecoords(float t,struct coords noktalar[30])
	{
		int p0, p1, p2, p3;
	
	
			p1 = (int)t + 1;
			p2 = p1 +1;
			p3 = p2 +1;
			p0 = p1 - 1;
			
		
	
		
	
		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -ttt+2.0*tt-t;
		float q2 = 3.0*ttt-5.0*tt+2.0;
		float q3 = -3.0*ttt+4.0*tt+t;
		float q4 = ttt-tt;

		float tx = 0.5f* (noktalar[p0].x * q1 + noktalar[p1].x * q2 + noktalar[p2].x * q3 + noktalar[p3].x * q4);
		float ty = 0.5f* (noktalar[p0].y * q1 + noktalar[p1].y * q2 + noktalar[p2].y * q3 + noktalar[p3].y * q4);

    coordsf txty;
    txty.x=tx;
    txty.y=ty;
		return txty ;
	}

float uzaklikbul(float x1,float y1,float x2,float y2)
{
	float uzaklik;
	
	uzaklik=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	 return uzaklik;
}

  


int main()
{
	
	//text dosyasýndan noktalarý okuma ve bir dizide tutma
	
	
    FILE *dosya=fopen("test.txt","r");

    
    struct coords noktalar[30];
    int c=fgetc(dosya);


int i;
	for(i=0;i<30;i++)
   {
   	    	if(c !=EOF)
        	{
   			    fscanf(dosya,"%d,%d",&noktalar[i].x,&noktalar[i].y);
   	   	     	printf("\n %d. nokta={%d,%d}",i+1,noktalar[i].x,noktalar[i].y);
            } 
            else break;
		c=fgetc(dosya);
	}
       


	


    
    
    
   
    
//yeni ekran açma ve degiskenleri tanýmlama
    
    
int midx=500,midy=500,graphx,graphy; char graphxarray[5],graphyarray[5];
initwindow(1000,1000);


//noktalarý ekranda gösterme


//for(int j=0;j<i+1;j++)
//{
//	outtextxy(noktalar[j].x*20+midx,-(noktalar[j].y*20)+midy,"*");
//}


// grafiði çizdirme ve ölçekleme


setcolor(RED);
line(0,500,1000,500);
line(500,0,500,1000);


for(int l=0;l<=1000;l+=20)
{
	graphx=(l-midx)/20;
	graphy=(midy-l)/20;
	sprintf(graphxarray,"%d",graphx);
	sprintf(graphyarray,"%d",graphy);
	outtextxy(l,505,graphxarray);
	
	if(graphy !=0)
	outtextxy(505,l,graphyarray);
}

//noktalar arasý uzaklýklarý hesaplama

for(int h=0;h<i;h++)
{
	for(int j=h+1;j<i;j++)
	{
		noktalar[h].uzaklikp[j]=uzaklikbul(noktalar[h].x,noktalar[h].y,noktalar[j].x,noktalar[j].y);
	}
}
	
//birbirine en uzak noktalarý tespit etme	
	
	float temp=-5.0; int htut,jtut;
	
	for(int h=0;h<i;h++)
{
	for(int j=h+1;j<i;j++)
	{
		if(noktalar[h].uzaklikp[j]>temp)
		{
			temp=noktalar[h].uzaklikp[j];
			htut=h;
			jtut=j;
		}
	}
}

//birbirine en uzak noktalarýn merkezini bulma
	
float centerx,centery,tempc; int ktut;

centerx=(noktalar[htut].x+noktalar[jtut].x)/2.0;
centery=(noktalar[htut].y+noktalar[jtut].y)/2.0;


//buldugumuz merkeze en uzak noktayý tespit etme


for(int k=0;k<i;k++)
{
	if(uzaklikbul(noktalar[k].x,noktalar[k].y,centerx,centery)>tempc)
	{
	
		if(k!=htut && k!=jtut)
		{	
			tempc=uzaklikbul(noktalar[k].x,noktalar[k].y,centerx,centery);
			ktut=k;
		}
	}
}

//eðer merkeze en uzak noktanýn uzaklýðý merkezi oluþturan noktalarýn uzaklýgýndan büyük deðilse çemberi sadece merkezi oluþturan 2 nokta tanýmlar
//eðer büyük ise çemberi bu 3 nokta birlikte tanýmlar

int x1=noktalar[htut].x,x2=noktalar[jtut].x,x3=noktalar[ktut].x,y1=noktalar[htut].y,y2=noktalar[jtut].y,y3=noktalar[ktut].y;
if(temp/2.0>tempc)
{
	float r=temp/2.0;
	setcolor(BLUE);
	circle(centerx*20.0+midx,midy-centery*20,r*20.0+3);
	printf(" \n merkez(%f,%f)  yaricap=%f",centerx,centery,r);
   char circlecenter[5];
   sprintf(circlecenter,"M %f %f %f",centerx,centery,r);
   outtextxy(centerx*20+500,500-centery*20,circlecenter);
   printf("\n cemberi olusturan noktalar: (%d,%d) (%d,%d)",x1,y1,x2,y2);
}
else
{
    float x12 = x1 - x2; 
    float x13 = x1 - x3; 
  
    float y12 = y1 - y2; 
    float y13 = y1 - y3; 
  
    float y31 = y3 - y1; 
    float y21 = y2 - y1; 
  
    float x31 = x3 - x1; 
    float x21 = x2 - x1; 
  
    // x1^2 - x3^2 
    float sx13 = pow(x1, 2) - pow(x3, 2); 
  
    // y1^2 - y3^2 
    float sy13 = pow(y1, 2) - pow(y3, 2); 
  
    float sx21 = pow(x2, 2) - pow(x1, 2); 
    float sy21 = pow(y2, 2) - pow(y1, 2); 
  
    float f = ((sx13) * (x12) 
             + (sy13) * (x12) 
             + (sx21) * (x13) 
             + (sy21) * (x13)) 
            / (2 * ((y31) * (x12) - (y21) * (x13))); 
    float g = ((sx13) * (y12) 
             + (sy13) * (y12) 
             + (sx21) * (y13) 
             + (sy21) * (y13)) 
            / (2 * ((x31) * (y12) - (x21) * (y13))); 
  
   float c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1; 
  
    // kullandýgým cember denklemi x^2 + y^2 + 2*g*x + 2*f*y + c = 0 
    // merkez noktalarý (h = -g, k = -f) olur ve yarýcap=r dir
    // r^2 = h^2 + k^2 - c 
    float h = -g; 
    float k = -f; 
    float rkare = h * h + k * k - c; 
    float r = sqrt(rkare); 
  setcolor(YELLOW);
   circle(h*20+500,500-k*20,r*20.0+3);
  printf(" \n merkez(%f,%f)  yaricap=%f",h,k,r);
   char circlecenter[5];
   sprintf(circlecenter,"M %f %f %f",h,k,r);
   outtextxy(-g*20+500,500+f*20,circlecenter);
   printf("\n cemberi olusturan noktalar (%d,%d) (%d,%d) (%d,%d) ",x1,y1,x2,y2,x3,y3);
   
}


struct coordsf noktalar2[i];

for(int b=0;b<i+1;b++)
{
	noktalar2[b].x=noktalar[b].x*20.0+midx;
	noktalar2[b].y=midy-noktalar[b].y*20.0;
}
setcolor(GREEN);
for(int n=0;n<i;n++)
{
	circle(noktalar2[n].x,noktalar2[n].y,10);
}

for (float t = 0.0; t < i; t += 0.005f)
	{
			coordsf pos = splinecoords(t,&noktalar[0]);
			setcolor(WHITE);
			delay(10);
			circle(pos.x*20+midx, midy-20*pos.y,1);
			
    }

getch();
closegraph();  
fclose(dosya);


}


