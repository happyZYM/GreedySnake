#include<cstdio>
#include"screen.h"
int a[26][22];
/*
1 wall
2 food
3 star
*/
int main()
{
	int now=1,x,y;
	char add[30],str[30];
	a[0][10]=-1;
	a[1][10]=-1;
	a[2][10]=-1;
	scanf("%s",str);
	sprintf(add,"files/%s.txt",str);
	gotoxy(0,0); 
	printf("[Cursor Position] X: %2lu  Y: %2lu           \n", 0, 0);
	hm();
	while(1)
	{
		gotoxy(0,0);
		SetColor(15);
		printf("[Cursor Position] X: %2lu  Y: %2lu          \n",mpX(),mpY()-1);
		if(double_click())
		{
			if(mpY()==0) break;
			now++;
			if(now==4) now=1;
		}
		if(left_click())
		{
			x=mpX();y=mpY();
			if(x/2<0||x/2>=26||y-1<0||y-1>=22) goto end;
			if(a[x/2][y-1]==-1) goto end;
			a[x/2][y-1]=now;
			gotoxy(x/2*2,y);
			switch(now)
			{
				case 1:SetColor(12);printf("®Å");break;
				case 2:SetColor(11);printf("°Ò");break;
				case 3:SetColor(14);printf("°Ó");break;
			}
		}
		if(right_click())
		{
			x=mpX();y=mpY();
			if(x/2<0||x/2>=26||y-1<0||y-1>=22) goto end;
			a[x/2][y-1]=0;
			gotoxy(x/2*2,y);
			printf("  ");
		}
		end:;
	}
	FILE *f=fopen(add,"w");
	for(int i=0;i<22;i++)
	{
		for(int j=0;j<26;j++) fprintf(f,"%d ",a[j][i]);
		fprintf(f,"\n");
	}
	return 0;
}
