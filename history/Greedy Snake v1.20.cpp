/*
 * Greedy Snake
 * Դ����Դ��δ֪ 
 * ע��: �ǳ�
 * �ӹ���ׯԣ�F 
 * v1.10��
 *     1.�������¿�һ�ֺ�ʱ����ʾ������
 *     2.�޸��˲˵�
 *     3.�����˲˵������뷨 
 *     4.����������ֵ��ʾ��bug 
 * v1.20��
 *     1.ȫ������ע��
 *     2.�Ż��˳��� 
 */ 
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<cstdlib>
#include"conio.h"//�Ǳ�׼��������⺯�� 
using namespace std;


const int UP=72;//��
const int DOWN=80;//��
const int LEFT=75;//��
const int RIGHT=77;//��

int n=4;//n������¼������,��ʼΪ2��
int guan;//������¼�ؿ�
int T;//��������¼�ߵ��ƶ��ٶ�
int t1,t2,t3=0;//������¼����ʱ��
int HP=5;//��¼�ߵ�����ֵ,��ʼ��Ϊ6
int food=0;//������¼���Ե���ʳ����
int x=12,y=12;//��¼ʳ�����ڵ�

struct snake
{
    int x;//�������ں�����
    int y;//��������������
    int direction;//���߷���
}p[81];


struct map
{
    int food;//��map[x][y]���Ƿ���ʳ���еĻ�foodΪ1
    int star;//��map[x][y]���Ƿ������ǵĻ�ֵΪ1
    int barrier;//��map[x][y]���Ƿ����ϰ����еĻ�ֵΪ1
}map[26][22];

inline void c(int k)//�ı�����������ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

inline int time()//������ʱ
{
    return clock()/CLOCKS_PER_SEC;
}

inline void gotoxy(int x,int y) //�ƶ�����
{
    static COORD coord; 
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

inline int random()//����������ֵ
{
    srand(t1+rand());//����������ӳ�ʼ��
    return rand();//���������
}

void ycgb();//���ع��
void start();//�������������Լ���ǽ
void guanka();//����ѡ��ؿ������ݹؿ������ߵ��ƶ��ٶ�
void data();//������¼��Ϸ�ĸ���״̬����
int game();//��Ϸ����
void show();//������������ϰ����Լ�ʳ�������ҩˮ�Լ������ж���Ϸ�ĸ��ֲ�����С�����Ƿ�Ե����Ƿ�ײǽ��
void key();//�����û�����
void qp();//�����Ļ


inline void SetTitle(char *str)
{
	SetConsoleTitle(str);
}
int main()
{
	SetTitle("̰����"); 
    ycgb();//���ع��
    start();//�������������Լ���ǽ
    while(1)
    {
       guanka();//����ѡ��ؿ������ݹؿ������ߵ��ƶ��ٶ�
       if(!game()) break;//��Ϸ����
    }
}

inline void ycgb()//���ع��
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=0;//��1Ϊ��ʾ����0Ϊ����
    SetConsoleCursorInfo(hOut,&cci);
}

inline void SetScreenSize(int x,int y)
{
	char str[50];
	sprintf(str,"mode con cols=%d lines=%d",x,y);
	system(str);
}

inline void start()//����ǽ/�������������Լ���ǽ
{
	SetScreenSize(100,36); 
    int i,j,z;
    for(i=0;i<25;i++)
    {
        cout<<"                                                                                ";
    }
    c(14);//���ɻ�ɫ
    for(z=0;z<20;z++)
    {
        if(z>=0)
        {
            gotoxy(12,z);
            cout<<"              ~--______-~                ~-___-~\"       ";  
        }
        if(z>=1)
        {
            gotoxy(12,z-1);
            cout<<"            ~-_           _-~          ~-_       _-~    ";
        }
        if(z>=2)
        {
            gotoxy(12,z-2);
            cout<<"          \\     ~-____-~     _-~    ~-_    ~-_-~    / ";
        }
        if(z>=3)
        {
            gotoxy(12,z-3);
            cout<<"         (     (         _-~    _--_    ~-_    _/   |  ";
        }
        if(z>=4)
        {
            gotoxy(12,z-4);
            cout<<"          /    /            _-~      ~-_        |   |  "; 
        }
        if(z>=5)
        {
            gotoxy(12,z-5);
            cout<<"           /    /              _----_           \\  \\ ";
        }
        if(z>=6)
        {
            gotoxy(12,z-6);
            cout<<"             /    /                            \\ \\   ";
        }
        if(z>=7)
        {
            gotoxy(12,z-7);
            cout<<"              /    /                          \\\\     ";
        }
        if(z>=8)
        {
            gotoxy(12,z-8);
            cout<<"                /    /                      \\\\       ";
        }
        if(z>=9)
        {
            gotoxy(12,z-9);
            cout<<"                 /     /                   \\            ";
        }
        if(z>=10)
        {
            gotoxy(12,z-10);
            cout<<"                  |     |                \\                ";
        }
        if(z>=11)
        {
            gotoxy(12,z-11);
            cout<<"                 \\     \\                                 ";
        }
        if(z>=12)
        {
            gotoxy(12,z-12);
            cout<<"        \\_______      \\                                  ";
        }
        if(z>=13)
        {
            gotoxy(12,z-13);
            cout<<" \\____|__________/  \\                                    "; 
        }
        if(z>=14)
        {
            gotoxy(12,z-14);
            cout<<"\\/     /~     \\_/ \\                                     ";
        }
        if(z>=15)
        {
            gotoxy(12,z-15);
            cout<<"        _|__|  O|                                          ";
        }
        for(int k=15;k<z;k++)
        {
            gotoxy(12,k-15);
            cout<<"                                                           ";
        }
        Sleep(30);
    }
    gotoxy(0,25);
    cout<<"     Greedy-- ��������  ����     ��       ��       ��     ��    ����������           V1.20��"<<endl;
    cout<<"              ��    ��  �� ��    ��      ����      ��    ��     ��        "<<endl;
    cout<<"              ��        ��  ��   ��     ��  ��     ��  ��       ��        "<<endl;
    cout<<"              ��������  ��   ��  ��    ��    ��    ����         ����������"<<endl;
    cout<<"                    ��  ��    �� ��    ��������    ��  ��       ��        "<<endl;
    cout<<"              ��    ��  ��     ����   ��      ��   ��    ��     ��        "<<endl;
    cout<<"              ��������  ��       ��  ��        ��  ��     ����  ����������"<<endl;//̰����
    Sleep(2000);
    system("cls");
    c(0);//���ɺڵ�ɫ
    gotoxy(0,0);
    for(i=0;i<25;i++)
    {
        cout<<"                                                                                ";
    }
    c(252);//���������ɫ 
    for(i=0,j=60;i<60;i++,j--)//if��Ϊ���첽��� 
    {
       if(j>20)
       {              
           gotoxy(2*(j-21),0);
           cout<<"��";//�����һ��
       }                                            
       if(i<40)
       {
           gotoxy(2*i,23);
           cout<<"��";// ���������һ�� 
       }  
       if(j>22&&j<45)
       {
           gotoxy(78,j-22);
           cout<<"�~";//������ұ���
       }    
       if(j>22&&j<45)
       {
           gotoxy(0,i-15);
           cout<<"�~";//�����һ��
       }
       if(i>37&&i<60)
       {
           gotoxy(54,i-37);
           Sleep(10);
           cout<<"�~";//����м�����
       } 
       Sleep(30);
     }
    gotoxy(56,11);
    cout<<"����������������������";                                            //56 
    gotoxy(19,0);    
    c(14);//���������ɫ 
    cout<<"| | |̰ �� ��| | |";//������� 
    
    gotoxy(56,2);
    cout<<"����ʱ�䣺";
    gotoxy(75,2);
    cout<<"��";
    gotoxy(56,4);
    cout<<"����ֵ��";
    gotoxy(56,6);
    cout<<"��ǰ���ȣ�";
    gotoxy(56,8);
    cout<<"�ѳ�ʳ�";
    gotoxy(56,10);
    cout<<"��             ��";
    gotoxy(64,12);
    cout<<"��ʾ��";
    gotoxy(56,13);
    cout<<"���ϣ���   ���ϣ���"; 
    gotoxy(56,14);
    cout<<"���£���   ���ң���";
    gotoxy(56,15);
    cout<<"��ͣ/��ʼ��ȷ���� ";
    gotoxy(56,16);
    cout<<"����ѡ�� ��Esc��";
    gotoxy(64,18);
    cout<<"ע�⣡";
    gotoxy(56,19);
    cout<<"1:ײ���ϰ������ǽ����";
    gotoxy(56,20);
    cout<<"  ֵ��һ ";
    gotoxy(56,21);
    cout<<"2:�Ե�С��������ֵ��һ";  
}
inline void guanka()//����ѡ��ؿ������ݹؿ������ߵ��ƶ��ٶ�
{
	qp();
    n=4;//n������¼������,��ʼΪ3��
    HP=6;//��¼�ߵ�����ֵ,��ʼ��Ϊ6
    p[0].x=6;                    //
    p[0].y=10;                   //
    p[0].direction=RIGHT;        //
    p[1].x=4;                   //
    p[1].y=10;                  //     ��ʼ��������λ�ú��ƶ�����   
    p[1].direction=RIGHT;       //
    p[2].x=2;                   //
    p[2].y=10;                  //
    p[2].direction=RIGHT;      //
    p[3].x=4;////////////////
    p[3].y=4;///////////////��¼��β����Ϣ
    p[3].direction=RIGHT;////
    static char t; 
    while(1)
    {
        gotoxy(15,3);
        c(14);
        cout<<"���������(1-6)�� ";
        t=getch();
        guan=t-'0';
        if(guan==0)     //�ж��Ƿ�����
        {
            gotoxy(15,3);
            c(12);//��ɺ�ɫ
            cout<<"  �����к����̣������";
            Sleep(500);
            gotoxy(15,3);
            cout<<"                      ";
            HP=-1;
            continue;//����ѡ�ش�
        }
        if(guan<7&&guan>0) break;//�жϹ����Ƿ����
        gotoxy(15,5);
        cout<<"�������";
        Sleep(800);
        gotoxy(15,5);
        cout<<"          ";
    }
    gotoxy(15,3);
    cout<<"                   ";
    switch (guan)
    {
        case 1:{T=600;break;}//
        case 2:{T=400;break;}//
        case 3:{T=200;break;}//    ���ݹ������趨�ߵ��ƶ��ٶ�
        case 4:{T=150;break;}//
        case 5:{T=100;break;}//
        case 6:{T=60;break;}//
    }
    qp();//�����Ļ
}
inline void data()//������¼���ж���Ϸ�ĸ���״̬����
{
    gotoxy(66,2);
    cout<<"        "; 
    gotoxy(66,2);
    c(12);//���ɺ�ɫ
    cout<<t1;//��������ʱ��
    switch (guan)
    {
    case 1:
        gotoxy(59,10);
        c(12);//���ɺ�ɫ
        cout<<"1";
        c(14);//���ɻ�ɫ
        cout<<" 2 3 4 5 6";
        break;
    case 2:
        gotoxy(59,10);
        c(14);//���ɻ�ɫ
        cout<<"1 ";
        c(12);//���ɺ�ɫ
        cout<<"2";
        c(14);//���ɻ�ɫ
        cout<<" 3 4 5 6 ";
        break;
    case 3:
        gotoxy(59,10);
        c(14);//���ɻ�ɫ
        cout<<"1 2 ";
        c(12);//���ɺ�ɫ
        cout<<"3";
        c(14);//���ɻ�ɫ
        cout<<" 4 5 6 ";
        break;
    case 4:
        gotoxy(59,10);
        c(14);//���ɻ�ɫ
        cout<<"1 2 3 ";
        c(12);//���ɺ�ɫ
        cout<<"4";
        c(14);//���ɻ�ɫ
        cout<<" 5 6 ";
        break;
    case 5:
        gotoxy(59,10);
        c(14);//���ɻ�ɫ
        cout<<"1 2 3 4 ";
        c(12);//���ɺ�ɫ
        cout<<"5";
        c(14);//���ɻ�ɫ
        cout<<" 6 ";
        break;
    case 6:
        gotoxy(59,10);
        c(14);//���ɻ�ɫ
        cout<<"1 2 3 4 5 ";
        c(12);//���ɺ�ɫ
        cout<<"6";
        break;
    }
    switch (HP)
    {
	    case 1:
	        gotoxy(65,4);
	        c(10);//������ɫ
	        cout<<"�x"; 
	        c(12);//���ɺ�ɫ
	        cout<<"�y�z�|�}�~";
	        break;
	    case 2:
	        gotoxy(65,4);
	        c(10);//������ɫ
	        cout<<"�x�y"; 
	        c(12);//���ɺ�ɫ
	        cout<<"�z�|�}�~";
	        break;
	    case 3:
	        gotoxy(65,4);
	        c(10);//������ɫ
	        cout<<"�x�y�z";
	        c(12);//���ɺ�ɫ
	        cout<<"�|�}�~";
	        break;
	    case 4:
	        gotoxy(65,4);
	        c(10);//������ɫ
	        cout<<"�x�y�z�|";
	        c(12);//���ɺ�ɫ
	        cout<<"�}�~";
	        break;
	    case 5:
	        gotoxy(65,4);
	        c(10);//������ɫ
	        cout<<"�x�y�z�|�}";
	        c(12);//���ɺ�ɫ
	        cout<<"�~";
	        break;
	    case 6:
	        gotoxy(65,4);
	        c(10);//������ɫ
	        cout<<"�x�y�z�|�}�~";
	        break;
	    default:
	        gotoxy(65,4);
	        c(10);//���ɺ�ɫ
	        cout<<"������ģʽ ��";
	        break;
    }
    gotoxy(66,6);
    c(12);//���ɺ�ɫ
    cout<<n-1;//����ߵĵ�ǰ����
    gotoxy(66,8);
    cout<<food;//����ߵ�ǰ�Ѿ��Ե�ʳ��
}
inline void qp()//���������Ļ
{
	static int i;
    for(i=1;i<23;i++)
    {
       gotoxy(2,i);
       cout<<"                                                    ";
    } 
    map[x][y].food=0;//��ʳ�����
    map[x][y].barrier=0;//���ϰ������
    map[x][y].star=0;//��������� 
}

inline void show()//������������ϰ����Լ�ʳ�������ҩˮ�Լ������ж���Ϸ�ĸ��ֲ���
{
    static int a,b,e,f,i; //a��b������ʾС���ǵ�����   c��d�����ϰ�������
    if(map[x][y].food==0)//�ж�ʳ���ǲ��Ǳ��Ե�
    { 
        while(1)
        {                                                                                                  
            x=random()%26;//�������������
            y=random()%22;//�������������
            if(map[x][y].barrier==0&&map[x][y].star==0) break;//���˴�������Ԫ���ǲ���Ч 
        }
        map[x][y].food=1;//�������ʳ��
        gotoxy(2*(x+1),y+1);//��λ��ʳ����ֵ�λ��
        c(11);//���ɻ�ɫ
        cout<<"��";//��ӡ��ʳ��
    }
    if(t1/20>0&&t1%12==0&&t1>t3&&map[(p[0].x-1)/2][p[0].y-1].food==0&&map[(p[0].x-1)/2][p[0].y-1].star==0)
    {
        while(1)
        {                                                                                                  
            e=random()%26;//�������������
            f=random()%22;//�������������
            if(map[e][f].food==0&&map[e][f].star==0) break;//���˴�������Ԫ���ǲ���Ч 
        }
        gotoxy(2*(e+1),f+1);//��λ���ϰ�����ֵ�λ��
        map[e][f].barrier=1;//��������ϰ���
        c(12);//���ɻ�ɫ
        cout<<"�~";//��ӡ���ϰ���
        t3=t1;//�����������ϰ���
        if(HP<7)
        {
          gotoxy(18,24);
          c(15);//���ɰ�ɫ
          cout<<"��ܰ��ʾ����ѡ�ص�ʱ������0���Կ�������ģʽ";
        }
    }
    if(t1/25>0&&t1%15==0&&t1>t3&&map[(p[0].x-1)/2][p[0].y-1].food==0&&map[(p[0].x-1)/2][p[0].y-1].barrier==0)//�������ǳ��ֵļ��� 
    {
        while(1)
        {                                                                                                  
            a=random()%26;//�������������
            b=random()%22;//�������������
            if(map[a][b].barrier==0&&map[a][b].food==0) break;//���˴�������Ԫ���ǲ���Ч 
        }
        map[a][b].star=1;//�������С���ǣ��Ե����ǳ��ȼ�1��
        gotoxy(2*(a+1),b+1);//��λ�����ǳ��ֵ�λ�ã��Ե����ǳ��ȼ�1��
        c(14);//���ɻ�ɫ
        cout<<"��";//��ӡ�����ǣ��Ե����ǳ��ȼ�1��
        t3=t1;//�����������ϰ���
        if(HP<7)
        {
           gotoxy(18,24);
           cout<<"                                            ";
        }
    }
    for(i=0;i<n;i++)
    {
        if(map[(p[i].x-1)/2][p[i].y-1].food==1)//�ж����Ƿ�Ե�ʳ��
        {
            ++n;//���߳��ȼ�1
            food++;//��ʳ������1
            map[(p[i].x-1)/2][p[i].y-1].food=0;//��ʳ���ʾ����
            break;
        }
    }
    if(map[(p[0].x-1)/2][p[0].y-1].star==1)//�ж����Ƿ�Ե�����
    {
        map[(p[0].x-1)/2][p[0].y-1].star=0;//�����Ǳ�ʾ����
        if(HP<6)
           ++HP;//������ֵ��1
    }
    t1=time()-t2;//ˢ����Ϸ����ʱ��
}
inline void key()//�����û�����
{
	static int ch;
    if(kbhit())//�ж��Ƿ񰴼�
    {              
        ch=getch();
        if(ch==224)//�жϰ����ǲ��Ƿ����
        {
           ch=getch();               
           if((ch==72||ch==75||ch==80||ch==77)&&(ch+p[0].direction!=152)&&ch!=p[0].direction)  //�жϰ����Ƿ��Ƿ�����������ǲ������ƶ�����ķ�����
                  p[0].direction=ch;//������Ǿ͸ı���ͷ����
           else rewind(stdin); 
        }
        else if(ch==13)//�ж��û��Ƿ���ͣ
        {
            static clock_t a,b;
            a=time();//��¼��ǰ��������ʱ��
            gotoxy(20,1);
            c(15);//���ɰ�ɫ
            cout<<"����ͣ,��ȷ������ʼ";
            while(1)
            {
                if(kbhit()&&getch()==13)////�ж��Ƿ񰴼����Ƿ�����ͣ
                {
                    gotoxy(20,1);
                    cout<<"                     ";//���"����ͣ,��ȷ������ʼ"������                     
                    break;
                } 
            }
            b=time();//��¼��ǰ��������ʱ��
            t2+=(b-a);//����ͣ�ӵ�t2�Ϲ�t1��ȥ
        }
        else if(ch==27)//�ж��Ƿ�����ѡ��
        {
            guanka();//����ѡ��ؿ������ݹؿ������ߵ��ƶ��ٶ�
            game();//��ʼ��Ϸ        
        }
        else rewind(stdin); 
    }    
}
inline int game()
{
    static int i,ch;
    ch=RIGHT;//����
    t2=time();//��¼��ǰ��������ʱ��
    while(1)
    {
        t1=time()-t2;//ˢ����Ϸ����ʱ��
        data();//������¼��Ϸ�ĸ���״̬����
        gotoxy(p[0].x,p[0].y);//ת����ͷλ��
        c(12);//�ĳɺ�ɫ
        cout<<"��";//��ӡ��ͷ
        for(i=1;i<n-1;i++)
        {
            gotoxy(p[i].x,p[i].y);//ת����ǰ����λ��
            c(14);//�ĳɻ�ɫ
            cout<<"��";//��ӡ����
        }
        gotoxy(p[n-2].x,p[n-2].y);//ת����ǰ��βλ��
        c(12);//�ĳɺ�ɫ
        cout<<"��";//��ӡ��β
        Sleep(T);//�����ߵ��ƶ��ٶ�
        t1=time()-t2;//ˢ����Ϸ����ʱ��
        gotoxy(p[n-2].x,p[n-2].y);//�Ƶ���β���ڵ�
        cout<<" ";//����ϸ�ѭ������β
        for(i=n-1;i>0;i--) p[i]=p[i-1];//�ƶ���
        key();//�û��Ƿ��������
        switch (p[0].direction)
        {
            case UP:{p[0].y-=1;break;}//�ı���ͷ���꣬�ƶ���ͷ
            case DOWN:{p[0].y+=1;break;}//�ı���ͷ���꣬�ƶ���ͷ
            case LEFT:{p[0].x-=2;break;}//�ı���ͷ���꣬�ƶ���ͷ
            case RIGHT:{p[0].x+=2;break;}//�ı���ͷ���꣬�ƶ���ͷ
        }
        if(p[0].x==0)//����ײ����ǽʱ
        {
            cout<<"\a";
            --HP;//������ֵ��һ
            p[0].x=52;//���䴩ǽ
        }
        if(p[0].x==54)//����ײ����ǽʱ
        {
            cout<<"\a";
            --HP;//������ֵ��һ
            p[0].x=2;//���䴩ǽ
        }
        if(p[0].y==0)//����ײ����ǽʱ
        {
            cout<<"\a";
            --HP;//������ֵ��һ
            p[0].y=22;//���䴩ǽ
        }
        if(p[0].y==23)//����ײ����ǽʱ
        {
            cout<<"\a";
            --HP;//������ֵ��һ
            p[0].y=1;//���䴩ǽ
        }
        for(i=1;i<n-1;i++)
        {
           if(p[0].x==p[i].x&&p[0].y==p[i].y) i=n+1;//�ж����Ƿ�ײ����
        }
        if(i>=n)//����ײ���Լ�
        {
            cout<<"\a";
            HP=0;//��������  
        }
        if(map[(p[0].x-1)/2][p[0].y-1].barrier==1)//�����ϰ���ʱ
        {
            cout<<"\a";
            --HP;//������ֵ��һ
            map[(p[0].x-1)/2][p[0].y-1].barrier=0;
        }
        if(HP==0)
        {
        	gotoxy(65,4);
	    	c(12);//���ɺ�ɫ
	    	cout<<"�x�y�z�|�}�~";//ˢ������ֵ 
            gotoxy(23,3);
        	c(9);
        	cout<<"������������������������";
        	gotoxy(23,4);
        	c(9);
        	cout<<"��";
        	c(11);
        	cout<<"��������������������";
        	c(9);
        	cout<<"��";
            gotoxy(23,5);
            c(9);cout<<"��";c(11);cout<<"��";
            c(12);cout<<"��"; 
            c(15);//���ɰ�ɫ 
            cout<<"��Ϸ����������";
            c(11);cout<<"��";c(9);cout<<"��";
            gotoxy(23,6);
        	c(9);
        	cout<<"��";
        	c(11);
        	cout<<"��������������������";
        	c(9);
        	cout<<"��";
        	gotoxy(23,7);
        	c(9);
        	cout<<"������������������������";
            Sleep(3000);//��ʱ
            gotoxy(25,5);
            return 1;
            break;
        }
        if(n==50)
        {
        	gotoxy(23,3);
        	c(9);
        	cout<<"������������������������";
        	gotoxy(23,4);
        	c(9);
        	cout<<"��";
        	c(11);
        	cout<<"��������������������";
        	c(9);
        	cout<<"��";
            gotoxy(23,5);
            c(9);cout<<"��";c(11);cout<<"��";
            c(15);//���ɰ�ɫ
            cout<<"��ϲ����أ�����";
            c(11);cout<<"��";c(9);cout<<"��";
            gotoxy(23,6);
        	c(9);
        	cout<<"��";
        	c(11);
        	cout<<"��������������������";
        	c(9);
        	cout<<"��";
        	gotoxy(23,7);
        	c(9);
        	cout<<"������������������������";
            Sleep(3000);//��ʱ
            gotoxy(25,5);
            return 1;
            break;
        }
        show();//������������ϰ����Լ�ʳ�������ҩˮ�Լ������ж���Ϸ�ĸ��ֲ�����С�����Ƿ�Ե����Ƿ�ײǽ)
    }
    return 0;
}
