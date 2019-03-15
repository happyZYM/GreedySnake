/*
 * Greedy Snake
 * 源码来源：未知 
 * 注释: 星辰
 * 加工：庄裕旻 
 * v1.10版
 *     1.修正了新开一局后时间显示的问题
 *     2.修改了菜单
 *     3.更新了菜单及输入法 
 *     4.修正了生命值显示的bug 
 * v1.20版
 *     1.全面检查了注释
 *     2.优化了程序 
 */ 
#include<iostream>
#include<Windows.h>
#include<ctime>
#include<cstdlib>
#include"conio.h"//非标准输入输出库函数 
using namespace std;


const int UP=72;//上
const int DOWN=80;//下
const int LEFT=75;//左
const int RIGHT=77;//右

int n=4;//n用来记录蛇身长度,初始为2节
int guan;//用来记录关卡
int T;//用来给记录蛇的移动速度
int t1,t2,t3=0;//用来记录以用时间
int HP=5;//记录蛇的生命值,初始化为6
int food=0;//用来记录所吃到的食物数
int x=12,y=12;//记录食物所在地

struct snake
{
    int x;//蛇身所在横坐标
    int y;//蛇身所在纵坐标
    int direction;//行走方向
}p[81];


struct map
{
    int food;//此map[x][y]处是否有食物有的话food为1
    int star;//此map[x][y]处是否有星星的话值为1
    int barrier;//此map[x][y]处是否有障碍物有的话值为1
}map[26][22];

inline void c(int k)//改变输出字体的颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

inline int time()//用来计时
{
    return clock()/CLOCKS_PER_SEC;
}

inline void gotoxy(int x,int y) //移动坐标
{
    static COORD coord; 
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

inline int random()//用来输出随机值
{
    srand(t1+rand());//将随机数种子初始化
    return rand();//返回随机数
}

void ycgb();//隐藏光标
void start();//绘制启动画面以及隔墙
void guanka();//用来选择关卡并根据关卡设置蛇的移动速度
void data();//用来记录游戏的各种状态数据
int game();//游戏运行
void show();//用来随机产生障碍物以及食物和生命药水以及用来判断游戏的各种参数（小星星是否吃到，是否撞墙）
void key();//处理用户操作
void qp();//清除屏幕


inline void SetTitle(char *str)
{
	SetConsoleTitle(str);
}
int main()
{
	SetTitle("贪吃蛇"); 
    ycgb();//隐藏光标
    start();//绘制启动画面以及隔墙
    while(1)
    {
       guanka();//用来选择关卡并根据关卡设置蛇的移动速度
       if(!game()) break;//游戏运行
    }
}

inline void ycgb()//隐藏光标
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=0;//赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut,&cci);
}

inline void SetScreenSize(int x,int y)
{
	char str[50];
	sprintf(str,"mode con cols=%d lines=%d",x,y);
	system(str);
}

inline void start()//绘制墙/绘制启动画面以及隔墙
{
	SetScreenSize(100,36); 
    int i,j,z;
    for(i=0;i<25;i++)
    {
        cout<<"                                                                                ";
    }
    c(14);//调成黄色
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
    cout<<"     Greedy-- ▉▉▉▉  ▉▉     ▉       ▉       ▉     ▉    ▉▉▉▉▉           V1.20版"<<endl;
    cout<<"              ▉    ▉  ▉ ▉    ▉      ▉▉      ▉    ▉     ▉        "<<endl;
    cout<<"              ▉        ▉  ▉   ▉     ▉  ▉     ▉  ▉       ▉        "<<endl;
    cout<<"              ▉▉▉▉  ▉   ▉  ▉    ▉    ▉    ▉▉         ▉▉▉▉▉"<<endl;
    cout<<"                    ▉  ▉    ▉ ▉    ▉▉▉▉    ▉  ▉       ▉        "<<endl;
    cout<<"              ▉    ▉  ▉     ▉▉   ▉      ▉   ▉    ▉     ▉        "<<endl;
    cout<<"              ▉▉▉▉  ▉       ▉  ▉        ▉  ▉     ▉▉  ▉▉▉▉▉"<<endl;//贪吃蛇
    Sleep(2000);
    system("cls");
    c(0);//调成黑底色
    gotoxy(0,0);
    for(i=0;i<25;i++)
    {
        cout<<"                                                                                ";
    }
    c(252);//调整输出颜色 
    for(i=0,j=60;i<60;i++,j--)//if是为了异步输出 
    {
       if(j>20)
       {              
           gotoxy(2*(j-21),0);
           cout<<"▉";//输出第一行
       }                                            
       if(i<40)
       {
           gotoxy(2*i,23);
           cout<<"▉";// 输出最下面一行 
       }  
       if(j>22&&j<45)
       {
           gotoxy(78,j-22);
           cout<<"▇";//输出最右边列
       }    
       if(j>22&&j<45)
       {
           gotoxy(0,i-15);
           cout<<"▇";//输出第一列
       }
       if(i>37&&i<60)
       {
           gotoxy(54,i-37);
           Sleep(10);
           cout<<"▇";//输出中间那列
       } 
       Sleep(30);
     }
    gotoxy(56,11);
    cout<<"▉▉▉▉▉▉▉▉▉▉▉";                                            //56 
    gotoxy(19,0);    
    c(14);//调整输出颜色 
    cout<<"| | |贪 吃 蛇| | |";//输出标题 
    
    gotoxy(56,2);
    cout<<"已用时间：";
    gotoxy(75,2);
    cout<<"秒";
    gotoxy(56,4);
    cout<<"生命值：";
    gotoxy(56,6);
    cout<<"当前长度：";
    gotoxy(56,8);
    cout<<"已吃食物：";
    gotoxy(56,10);
    cout<<"第             关";
    gotoxy(64,12);
    cout<<"提示：";
    gotoxy(56,13);
    cout<<"向上：↑   向上：←"; 
    gotoxy(56,14);
    cout<<"向下：↓   向右：→";
    gotoxy(56,15);
    cout<<"暂停/开始：确定键 ";
    gotoxy(56,16);
    cout<<"重新选关 ：Esc键";
    gotoxy(64,18);
    cout<<"注意！";
    gotoxy(56,19);
    cout<<"1:撞到障碍物或者墙生命";
    gotoxy(56,20);
    cout<<"  值减一 ";
    gotoxy(56,21);
    cout<<"2:吃到小星星生命值加一";  
}
inline void guanka()//用来选择关卡并根据关卡设置蛇的移动速度
{
	qp();
    n=4;//n用来记录蛇身长度,初始为3节
    HP=6;//记录蛇的生命值,初始化为6
    p[0].x=6;                    //
    p[0].y=10;                   //
    p[0].direction=RIGHT;        //
    p[1].x=4;                   //
    p[1].y=10;                  //     初始化蛇所在位置和移动方向   
    p[1].direction=RIGHT;       //
    p[2].x=2;                   //
    p[2].y=10;                  //
    p[2].direction=RIGHT;      //
    p[3].x=4;////////////////
    p[3].y=4;///////////////记录蛇尾的信息
    p[3].direction=RIGHT;////
    static char t; 
    while(1)
    {
        gotoxy(15,3);
        c(14);
        cout<<"请输入关数(1-6)： ";
        t=getch();
        guan=t-'0';
        if(guan==0)     //判断是否作弊
        {
            gotoxy(15,3);
            c(12);//变成红色
            cout<<"  作弊有害智商，需谨慎";
            Sleep(500);
            gotoxy(15,3);
            cout<<"                      ";
            HP=-1;
            continue;//返回选关处
        }
        if(guan<7&&guan>0) break;//判断关数是否溢出
        gotoxy(15,5);
        cout<<"输入错误！";
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
        case 3:{T=200;break;}//    根据关数来设定蛇的移动速度
        case 4:{T=150;break;}//
        case 5:{T=100;break;}//
        case 6:{T=60;break;}//
    }
    qp();//清除屏幕
}
inline void data()//用来记录和判断游戏的各种状态数据
{
    gotoxy(66,2);
    cout<<"        "; 
    gotoxy(66,2);
    c(12);//调成红色
    cout<<t1;//程序已用时间
    switch (guan)
    {
    case 1:
        gotoxy(59,10);
        c(12);//调成红色
        cout<<"1";
        c(14);//调成黄色
        cout<<" 2 3 4 5 6";
        break;
    case 2:
        gotoxy(59,10);
        c(14);//调成黄色
        cout<<"1 ";
        c(12);//调成红色
        cout<<"2";
        c(14);//调成黄色
        cout<<" 3 4 5 6 ";
        break;
    case 3:
        gotoxy(59,10);
        c(14);//调成黄色
        cout<<"1 2 ";
        c(12);//调成红色
        cout<<"3";
        c(14);//调成黄色
        cout<<" 4 5 6 ";
        break;
    case 4:
        gotoxy(59,10);
        c(14);//调成黄色
        cout<<"1 2 3 ";
        c(12);//调成红色
        cout<<"4";
        c(14);//调成黄色
        cout<<" 5 6 ";
        break;
    case 5:
        gotoxy(59,10);
        c(14);//调成黄色
        cout<<"1 2 3 4 ";
        c(12);//调成红色
        cout<<"5";
        c(14);//调成黄色
        cout<<" 6 ";
        break;
    case 6:
        gotoxy(59,10);
        c(14);//调成黄色
        cout<<"1 2 3 4 5 ";
        c(12);//调成红色
        cout<<"6";
        break;
    }
    switch (HP)
    {
	    case 1:
	        gotoxy(65,4);
	        c(10);//调成绿色
	        cout<<"▁"; 
	        c(12);//调成红色
	        cout<<"▂▃▅▆▇";
	        break;
	    case 2:
	        gotoxy(65,4);
	        c(10);//调成绿色
	        cout<<"▁▂"; 
	        c(12);//调成红色
	        cout<<"▃▅▆▇";
	        break;
	    case 3:
	        gotoxy(65,4);
	        c(10);//调成绿色
	        cout<<"▁▂▃";
	        c(12);//调成红色
	        cout<<"▅▆▇";
	        break;
	    case 4:
	        gotoxy(65,4);
	        c(10);//调成绿色
	        cout<<"▁▂▃▅";
	        c(12);//调成红色
	        cout<<"▆▇";
	        break;
	    case 5:
	        gotoxy(65,4);
	        c(10);//调成绿色
	        cout<<"▁▂▃▅▆";
	        c(12);//调成红色
	        cout<<"▇";
	        break;
	    case 6:
	        gotoxy(65,4);
	        c(10);//调成绿色
	        cout<<"▁▂▃▅▆▇";
	        break;
	    default:
	        gotoxy(65,4);
	        c(10);//调成红色
	        cout<<"！超级模式 ！";
	        break;
    }
    gotoxy(66,6);
    c(12);//调成红色
    cout<<n-1;//输出蛇的当前长度
    gotoxy(66,8);
    cout<<food;//输出蛇当前已经吃到食物
}
inline void qp()//用来清除屏幕
{
	static int i;
    for(i=1;i<23;i++)
    {
       gotoxy(2,i);
       cout<<"                                                    ";
    } 
    map[x][y].food=0;//将食物清空
    map[x][y].barrier=0;//将障碍物清除
    map[x][y].star=0;//将星星清除 
}

inline void show()//用来随机产生障碍物以及食物和生命药水以及用来判断游戏的各种参数
{
    static int a,b,e,f,i; //a，b用来表示小星星的坐标   c，d代表障碍物坐标
    if(map[x][y].food==0)//判断食物是不是被吃掉
    { 
        while(1)
        {                                                                                                  
            x=random()%26;//产生随机横坐标
            y=random()%22;//产生随机纵坐标
            if(map[x][y].barrier==0&&map[x][y].star==0) break;//当此处无其他元素是才生效 
        }
        map[x][y].food=1;//随机出现食物
        gotoxy(2*(x+1),y+1);//定位到食物出现的位置
        c(11);//调成黄色
        cout<<"●";//打印出食物
    }
    if(t1/20>0&&t1%12==0&&t1>t3&&map[(p[0].x-1)/2][p[0].y-1].food==0&&map[(p[0].x-1)/2][p[0].y-1].star==0)
    {
        while(1)
        {                                                                                                  
            e=random()%26;//产生随机横坐标
            f=random()%22;//产生随机纵坐标
            if(map[e][f].food==0&&map[e][f].star==0) break;//当此处无其他元素是才生效 
        }
        gotoxy(2*(e+1),f+1);//定位到障碍物出现的位置
        map[e][f].barrier=1;//随机出现障碍物
        c(12);//调成黄色
        cout<<"▇";//打印出障碍物
        t3=t1;//以免产生多个障碍物
        if(HP<7)
        {
          gotoxy(18,24);
          c(15);//调成白色
          cout<<"温馨提示：在选关的时候输入0可以开启作弊模式";
        }
    }
    if(t1/25>0&&t1%15==0&&t1>t3&&map[(p[0].x-1)/2][p[0].y-1].food==0&&map[(p[0].x-1)/2][p[0].y-1].barrier==0)//减少星星出现的几率 
    {
        while(1)
        {                                                                                                  
            a=random()%26;//产生随机横坐标
            b=random()%22;//产生随机纵坐标
            if(map[a][b].barrier==0&&map[a][b].food==0) break;//当此处无其他元素是才生效 
        }
        map[a][b].star=1;//随机出现小星星（吃到星星长度减1）
        gotoxy(2*(a+1),b+1);//定位到星星出现的位置（吃到星星长度减1）
        c(14);//调成黄色
        cout<<"☆";//打印出星星（吃到星星长度减1）
        t3=t1;//以免产生多个障碍物
        if(HP<7)
        {
           gotoxy(18,24);
           cout<<"                                            ";
        }
    }
    for(i=0;i<n;i++)
    {
        if(map[(p[i].x-1)/2][p[i].y-1].food==1)//判断蛇是否吃到食物
        {
            ++n;//让蛇长度加1
            food++;//将食物数加1
            map[(p[i].x-1)/2][p[i].y-1].food=0;//让食物标示归零
            break;
        }
    }
    if(map[(p[0].x-1)/2][p[0].y-1].star==1)//判断蛇是否吃到星星
    {
        map[(p[0].x-1)/2][p[0].y-1].star=0;//让星星标示归零
        if(HP<6)
           ++HP;//将生命值加1
    }
    t1=time()-t2;//刷新游戏运行时间
}
inline void key()//处理用户操作
{
	static int ch;
    if(kbhit())//判断是否按键
    {              
        ch=getch();
        if(ch==224)//判断按的是不是方向键
        {
           ch=getch();               
           if((ch==72||ch==75||ch==80||ch==77)&&(ch+p[0].direction!=152)&&ch!=p[0].direction)  //判断按键是否是方向键，并且是不是蛇移动方向的反方向
                  p[0].direction=ch;//如果不是就改变蛇头方向
           else rewind(stdin); 
        }
        else if(ch==13)//判断用户是否暂停
        {
            static clock_t a,b;
            a=time();//记录当前程序已用时间
            gotoxy(20,1);
            c(15);//调成白色
            cout<<"已暂停,按确定键开始";
            while(1)
            {
                if(kbhit()&&getch()==13)////判断是否按键且是否解除暂停
                {
                    gotoxy(20,1);
                    cout<<"                     ";//清除"已暂停,按确定键开始"这行字                     
                    break;
                } 
            }
            b=time();//记录当前程序已用时间
            t2+=(b-a);//将暂停加到t2上供t1减去
        }
        else if(ch==27)//判断是否重新选关
        {
            guanka();//用来选择关卡并根据关卡设置蛇的移动速度
            game();//开始游戏        
        }
        else rewind(stdin); 
    }    
}
inline int game()
{
    static int i,ch;
    ch=RIGHT;//向右
    t2=time();//记录当前程序已用时间
    while(1)
    {
        t1=time()-t2;//刷新游戏运行时间
        data();//用来记录游戏的各种状态数据
        gotoxy(p[0].x,p[0].y);//转到蛇头位置
        c(12);//改成红色
        cout<<"◆";//打印蛇头
        for(i=1;i<n-1;i++)
        {
            gotoxy(p[i].x,p[i].y);//转到当前蛇身位置
            c(14);//改成黄色
            cout<<"●";//打印蛇身
        }
        gotoxy(p[n-2].x,p[n-2].y);//转到当前蛇尾位置
        c(12);//改成红色
        cout<<"●";//打印蛇尾
        Sleep(T);//控制蛇的移动速度
        t1=time()-t2;//刷新游戏运行时间
        gotoxy(p[n-2].x,p[n-2].y);//移到蛇尾所在地
        cout<<" ";//清除上个循环的蛇尾
        for(i=n-1;i>0;i--) p[i]=p[i-1];//移动蛇
        key();//用户是否操作键盘
        switch (p[0].direction)
        {
            case UP:{p[0].y-=1;break;}//改变蛇头坐标，移动蛇头
            case DOWN:{p[0].y+=1;break;}//改变蛇头坐标，移动蛇头
            case LEFT:{p[0].x-=2;break;}//改变蛇头坐标，移动蛇头
            case RIGHT:{p[0].x+=2;break;}//改变蛇头坐标，移动蛇头
        }
        if(p[0].x==0)//当蛇撞到左墙时
        {
            cout<<"\a";
            --HP;//将生命值减一
            p[0].x=52;//将其穿墙
        }
        if(p[0].x==54)//当蛇撞到右墙时
        {
            cout<<"\a";
            --HP;//将生命值减一
            p[0].x=2;//将其穿墙
        }
        if(p[0].y==0)//当蛇撞到上墙时
        {
            cout<<"\a";
            --HP;//将生命值减一
            p[0].y=22;//将其穿墙
        }
        if(p[0].y==23)//当蛇撞到下墙时
        {
            cout<<"\a";
            --HP;//将生命值减一
            p[0].y=1;//将其穿墙
        }
        for(i=1;i<n-1;i++)
        {
           if(p[0].x==p[i].x&&p[0].y==p[i].y) i=n+1;//判断蛇是否撞到自
        }
        if(i>=n)//当蛇撞到自己
        {
            cout<<"\a";
            HP=0;//将蛇死亡  
        }
        if(map[(p[0].x-1)/2][p[0].y-1].barrier==1)//当蛇障碍物时
        {
            cout<<"\a";
            --HP;//将生命值减一
            map[(p[0].x-1)/2][p[0].y-1].barrier=0;
        }
        if(HP==0)
        {
        	gotoxy(65,4);
	    	c(12);//调成红色
	    	cout<<"▁▂▃▅▆▇";//刷新生命值 
            gotoxy(23,3);
        	c(9);
        	cout<<"▉▉▉▉▉▉▉▉▉▉▉▉";
        	gotoxy(23,4);
        	c(9);
        	cout<<"▉";
        	c(11);
        	cout<<"▉▉▉▉▉▉▉▉▉▉";
        	c(9);
        	cout<<"▉";
            gotoxy(23,5);
            c(9);cout<<"▉";c(11);cout<<"▉";
            c(12);cout<<"△"; 
            c(15);//调成白色 
            cout<<"游戏结束！！！";
            c(11);cout<<"▉";c(9);cout<<"▉";
            gotoxy(23,6);
        	c(9);
        	cout<<"▉";
        	c(11);
        	cout<<"▉▉▉▉▉▉▉▉▉▉";
        	c(9);
        	cout<<"▉";
        	gotoxy(23,7);
        	c(9);
        	cout<<"▉▉▉▉▉▉▉▉▉▉▉▉";
            Sleep(3000);//延时
            gotoxy(25,5);
            return 1;
            break;
        }
        if(n==50)
        {
        	gotoxy(23,3);
        	c(9);
        	cout<<"▉▉▉▉▉▉▉▉▉▉▉▉";
        	gotoxy(23,4);
        	c(9);
        	cout<<"▉";
        	c(11);
        	cout<<"▉▉▉▉▉▉▉▉▉▉";
        	c(9);
        	cout<<"▉";
            gotoxy(23,5);
            c(9);cout<<"▉";c(11);cout<<"▉";
            c(15);//调成白色
            cout<<"恭喜你过关！！！";
            c(11);cout<<"▉";c(9);cout<<"▉";
            gotoxy(23,6);
        	c(9);
        	cout<<"▉";
        	c(11);
        	cout<<"▉▉▉▉▉▉▉▉▉▉";
        	c(9);
        	cout<<"▉";
        	gotoxy(23,7);
        	c(9);
        	cout<<"▉▉▉▉▉▉▉▉▉▉▉▉";
            Sleep(3000);//延时
            gotoxy(25,5);
            return 1;
            break;
        }
        show();//用来随机产生障碍物以及食物和生命药水以及用来判断游戏的各种参数（小星星是否吃到，是否撞墙)
    }
    return 0;
}
