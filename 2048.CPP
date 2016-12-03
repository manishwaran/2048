#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<ctype.h>

int matrix[10][10],choice=1,first=0,score=0,game=1,count=1;
int maxx,maxy,midx,midy;
char *msg;
void check();
void startpage();
void adder(int *);
void adder1();
void sort();
void sort1();
void init();
void show();
void loading();
void gen();
void setpage();
void process();
void drawline();
int get();

void main()
{
	clrscr();
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..\\bgi");
	maxx=getmaxx();
	maxy=getmaxy();
	midx=maxx/2;
	midy=maxy/2;
	init();
	startpage();
	loading();
	while(choice!=0)
	{
		gen();
		if(game==0)
			return;
		show();
		settextstyle(0,0,2);
		setcolor(13);
		outtextxy(midx+170,170,"0 - EXIT ! ");
		settextstyle(1,0,2);
		setcolor(WHITE);
		outtextxy(midx-35-textwidth("LEFT(4),RIGHT(6),DOWN(2),UP(8) : ")/2,maxy-100,"LEFT(4),RIGHT(6),DOWN(2),UP(8) : ");
		choice=get();
		process();
		show();
	}
	closegraph();
}

void loading()
{
  cleardevice();
  setcolor(13);
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,0);
  setusercharsize(2, 1, 1, 1);
  outtextxy(138,198,"LOADING");              //LOADING
  setcolor(13);
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,0);
  setusercharsize(2, 1, 1, 1);

setcolor(BLUE);
rectangle(119,199,421,231);
rectangle(118,198,422,232);
setcolor(10);
for(int ii=120;ii<=420;ii++)
{
line(ii,200,ii,230);
sound(ii+1500);
delay(10);
nosound();
}
}

void check()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(matrix[i][j]==matrix[i][j+1]&&count==0)
				count=2;
	for( j=0;j<4;j++)
		for(i=0;i<4;i++)
			if(matrix[i][j]==matrix[i+1][j]&&count==0)
				count=2;
}

void startpage()
{
	setpage();
	int gdriver = VGA, gmode = VGAHI, errorcode;
	struct palettetype pal;
	int i, ht, y, xmax;
	initgraph(&gdriver, &gmode, "..\\bgi");
	getpalette(&pal);
	for (i=0; i<pal.size; i++)
		setrgbpalette(i, i*4, i*4, i*4);
	ht = getmaxy() / 16;
	xmax = getmaxx();
	 y = 0;
	for (i=0; i<pal.size; i++)
	{
		setfillstyle(SOLID_FILL, i);
		bar(0, y, xmax, y+ht);
		y += ht;
	}
	settextstyle(0,0,3);
	outtextxy(80,150,"2 0 4 8");
	outtextxy(150,210," B Y ");
	outtextxy(200,265," M A N I S H");
	delay(3000);
	for(int h=0;h<500;h++)
	{
		 sound(h*9);
		 setfillstyle( random(12),random(15) );
		 bar3d(random(640),random(480),random(640),random(480),random(30),
		 random(18));
	}
	 for(int hh=0;hh<500;hh++)
	 {
		 sound(hh*9);
		 setfillstyle( random(12),random(15) );
		 bar3d(random(640),random(480),random(640),random(480),random(30),
		 random(18));
	 }
	cleardevice();
	return ;
}

int get()
{
	int tem,rescl;
	char *a;
	a[0]=getch();
	if(a[0]=='4'||a[0]=='6'||a[0]=='2'||a[0]=='8'||a[0]=='0')
		tem=atoi(a);
	else
	{
		setcolor(15);
		msg="INVALID ENTRY !";
		outtextxy(maxx-150,midy,msg);
		delay(500);
		rescl=getbkcolor();
		setcolor(2);
		setcolor(rescl);
		outtextxy(maxx-100,midy,msg);
		setcolor(rescl);
		tem=get();
	}
}

void init()
{
	for(int i=0;i<=10;i++)
		for(int j=0;j<=10;j++)
			matrix[i][j]==NULL;
}

void gen()
{
	randomize();
	int asn=0,i,j;
	count=0;
	for(i=0;i<=3;i++)
		for(j=0;j<=3;j++)
			if(matrix[i][j]==NULL)
				count=1;
	check();
	if(count==0)
	{
		cleardevice();
		setpage();
		settextstyle(3,0,4);
		setcolor(RED);
		outtextxy(midx-textwidth("GAME OVER !"),midy-textheight("GAME OVER !"),"GAME OVER !");
		delay(3000);
		cleardevice();
		setcolor(BLUE);
		sprintf(msg,"%d",score);
		outtextxy(midx-textwidth("SCORE = "),midy-textheight("SCORE = "),msg);
		getch();
		game=0;
		return;

	}
	if(count==2)
		return;

	while(!asn)
	{
		i=random(5)%4;
		j=random(5)%4;
		if(matrix[i][j]==NULL&&i>=0&&i<=3&&j>=0&&j<=3)
		{
			matrix[i][j]=2;
			asn=1;
			if(first==0)
			{
				asn=0;
				first++;
			}
		}
	}
}

void process()
{
	if(choice==6||choice==4)
	{
		for(int i=0;i<=3;i++)
		{
			adder(matrix[i]);
		}
	}
	else
	{
		adder1();
		sort1();
	}
}

void sort(int *sam)
{
	if(choice==6)
	{
		for(int i=3,j=i-1;j>=0;)
		{
			while(sam[i]==NULL&&j>=0)
			{
				sam[i]=sam[j];
				sam[j]=NULL;
				j--;
			}
			j=--i-1;
		}
	}
	else
		for(int i=0,j=i+1;j<=3;)
		{
			while(sam[i]==NULL&&j<=3)
			{
				sam[i]=sam[j];
				sam[j]=NULL;
				j++;
			}
			j=++i+1;
		}
}

void sort1()
{
	int row,move,next,col=0;
	if(choice==2)
		row=move=3;
	else
		move=0;
	for(;col<4;col++)
	{
		if(choice==2)
			move=3;
		else
			move=0;
		if(choice==2)
			next=move-1;
		else
			next=move+1;
		while(next>=0&&next<=3)
		{
			while(matrix[move][col]==NULL&&next<4&&next>=0)
			{
				matrix[move][col]=matrix[next][col];
				matrix[next][col]=NULL;
				if(choice==2)
					next--;
				else
					next++;
			}
			if(choice==2)
			{
				move-=1;
				next=move-1;
			}
			else
			{
				move+=1;
				next=move+1;
			}
		}
	}

}

void adder1()
{
	int move,next,col=0,row=3;
	if(choice==2)
	{
		move=3;
	}
	else
	{
		move=0;
	}
	for(;col<=3;col++)
	{
		if(choice==2)
			move=3;
		else
			move=0;
		if(choice==2)
			next=move-1;
		else
			next=move+1;
		while(next>=0&&next<=3)
		{
			if(matrix[move][col]==NULL)
			{
				move=next;
				if(choice==2)
				{
					next-=1;
					//rr-=1;
				}
				else
				{
					next=move+1;
					//rr+=1;
				}
			}
			if(matrix[next][col]==NULL)
			{
				while(matrix[next][col]==NULL&&(next>=0&&next<=3))
				{
					if(choice==2)
						next-=1;
					else
						next+=1;
				}
			}
			if(matrix[move][col]==matrix[next][col])
			{
				score+=matrix[move][col]=matrix[move][col]+matrix[next][col];
				matrix[next][col]=NULL;
			}
			if(choice==2)
			{
				move-=1;
				next-=1;
			}
			else
			{
				move+=1;
				next+=1;
			}
		}
	}
}

void adder(int *sam)
{
	int *tem=sam;
	int move,next;
	if(choice==6)
	{
		move=3;
		next=move-1;
	}
	else
	{
		move=0;
		next=move+1;
	}
	while(next>=0&&next<=3)
	{
		if(sam[move]==NULL)
		{
			if(choice==6)
			{
				move=next;
				next=move-1;
			}
			else
			{
				move=next;
				next=move+1;
			}
		}
		if(sam[next]==NULL)
		{
			while(tem[next]==NULL&&next>=0&&next<=3)
			{
				if(choice==6)
					next--;
				else
					next++;
			}
			if(next<0||next>3)
				break;
		}
		if(sam[move]==tem[next])
		{
			score+=sam[move]=sam[move]+tem[next];
			tem[next]=NULL;
		}
		if(choice==6)
		{
			move--;
			next--;
		}
		else
		{
			move++;
			next++;
		}
	}
	sort(sam);
}

void show()
{
	cleardevice();
	setpage();
	drawline();
	settextstyle(4,0,4);
	setcolor(10);
	sprintf(msg,"%d",score);
	outtextxy(maxx-textwidth("SCORE")-40,20,"SCORE");
	outtextxy(midx+170,70,msg);
	settextstyle(5,0,1);
}

void setpage()
{
	setbkcolor(BLACK);
	setcolor(WHITE);
	setlinestyle(0,0,1);
	rectangle(0,0,maxx,maxy);
	rectangle(3,3,maxx-3,maxy-3);
}

void drawline()
{
	int box=midx/4,box1=midy/4;
	int x1,x2,y1,y2,x,xx,w=319,h=239;
	x=x1=midx/2;
	y1=midy/2;
	x2=midx+midx/2;
	y2=midy+midy/2;
	setcolor(RED);
	setlinestyle(2,0,2);
	rectangle(x1-box,y1-box1,x2+60-box,y2+40-box1);
	xx=x2=box+15,y2=box1+15;
	for(int i=0;i<=3;i++)
	{
		for(int j=0;j<=3;j++)
		{
			if(matrix[i][j]==2)
				setfillstyle(1,22);
			else if(matrix[i][j]==4)
				setfillstyle(1,26);
			else if(matrix[i][j]==8)
				setfillstyle(1,28);
			else if(matrix[i][j]==16)
				setfillstyle(1,222);
			else if(matrix[i][j]==32)
				setfillstyle(1,18);
			else if(matrix[i][j]==64)
				setfillstyle(1,71);
			else if(matrix[i][j]==128)
				setfillstyle(1,44);
			else if(matrix[i][j]==256)
				setfillstyle(1,99);
			else if(matrix[i][j]==512)
				setfillstyle(1,110);
			else if(matrix[i][j]==1024)
				setfillstyle(1,211);
			else if(matrix[i][j]==2048)
				setfillstyle(1,122);
			else if(matrix[i][j]==4096)
				setfillstyle(1,138);
			else if(matrix[i][j]==8192)
				setfillstyle(1,140);
			else if(matrix[i][j]==NULL)
				setfillstyle(1,15);
			bar(x1,y1,x2,y2);
			setcolor(0);
			settextstyle(0,0,1);
			sprintf(msg,"%d",matrix[i][j]);
			outtextxy((x1+x2)/2-textwidth(msg)/2,(y1+y2)/2-textheight(msg)/2,msg);
			x1+=box+15;
			x2+=box+15;
		}
		y1+=box1+10;
		y2+=box1+10;
		x1=x;
		x2=xx;
	}
}
