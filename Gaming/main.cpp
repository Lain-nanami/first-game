#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <errno.h>
#include <time.h>
#include<mmsystem.h>
#include<process.h>
/******************************************************************************************************************************/
/*��Ϸ˵��*/
//0.����Ϸ��ͼ����������������Ϸundertale������ͼ��ɫ����Ϊ͵��Ŷ~
//1.��ʼ���������Ϻ��ٵ����Ļ�ſɿ�ʼ��Ϸ
//2.��ͣ��ťʹ��˵������������Ͻ���ͣ��ť�󣬵��q/QΪquit�����˳���Ϸ�����浵�������c/CΪsave�����浵�����l/LΪload��������������ո��Ϊ������Ϸ
//3.�ǵ��޸����뷨
//4.��ʼ������l�����ɼ��ش浵
//5.���ظ�����ʱ���þ����߳������������ڿ�ʼ����ֱ�Ӷ�ȡ�浵
//6.Ѫƿ��ƿ�м��ʻ�ˢ��ͬһλ�ã�������ֳ�ʱ����Ѫƿˢ�£����Գ���ȥ��һ����ƿ

//�淨˵����
//1.�ܼ򵥣���ܵ�Ļ�Ե��߼��ɻ�ʤ�����߻��һ��ʱ��ˢ�£���
//2.�Ե���ɫѪƿ������Ѫ�������Ѫ��0��Ϊ��Ϸʤ�����Ե���ɫѪƿ������������,��������ʱ��Ϊ7s��
//  ��ɫѪƿ�ڹ�����Ѫʱ5sˢ�£�֮��ÿ��17sˢ�£���ɫѪƿ13sˢ��
//3.�����ʼ����ֵΪ3�������ʼ����ֵΪ5
//  �����ܵ��˺�����1.5s�޵�ʱ��    
    









/******************************************************************************************************************************/

//��Ϸ����(ȫ�ֱ�����
//1.������Ϣ����
//A.����
typedef struct hero {
	int position_x; //x������
	int position_y; //y������
	int speed; //���Ǻ����ٶ�
	int blood; //������
	int IsZhuang;
	int d;
	int c;
	int a;
	int b;
}HERO;
HERO hero;
IMAGE img_HeroBlood;
//B.����
typedef struct monster {
	int blood;
	int i;
	int Hit;
	int IsHit;
	int IsMR;
}MONSTER;
MONSTER monster;
//C.��Ļ
typedef struct danmu {
	int enemy_x1, enemy_y1;
	int enemy_x2, enemy_y2;
	int enemy_x3, enemy_y3;
	int enemy_x4, enemy_y4;
	int enemy_x5, enemy_y5;
	int enemy_x6, enemy_y6;
	int enemy_x11, enemy_y11;
	int enemy_x12, enemy_y12;
	int enemy_x13, enemy_y13;
	int enemy_x14, enemy_y14;
	int enemy_x15, enemy_y15;
	int enemy_x16, enemy_y16;
	int enemy_x21, enemy_y21;
	int enemy_x22, enemy_y22;
	int enemy_x23, enemy_y23;
	int enemy_x24, enemy_y24;
	int enemy_x25, enemy_y25;
	int enemy_x26, enemy_y26;
	int enemy_x31, enemy_y31;
	int enemy_x32, enemy_y32;
	int enemy_x33, enemy_y33;
	int enemy_x34, enemy_y34;
	int enemy_x35, enemy_y35;
	int enemy_x36, enemy_y36;
}DM;
DM dm;

//4.����1,����2
IMAGE img_red, img_blue, img_hero;
typedef struct prop
{
	int position_x;
	int position_y;
	int ncount ;//����ʱ��
	int FlushTime;
	int IsFlush;
	int Reach;
	int Reach2;
	int judge;
}PROP;
PROP prop/*��Ѫ����*/, prop1/*���ٵ���*/, prop2/*��Ѫ����*/;


//2.�浵��ȡ����ԭ��
errno_t err; 

//3.��ʼ��������С
#define Width 1300
#define High 750

//4.��ʼ�������
int timeflag = 0;  //����Click�����˸
int Menustep = 0;
IMAGE img_MenuTitle; //��������ͼƬ
IMAGE img_MenuTitleG1; //��������ͼƬ
IMAGE img_MenuTitleG2; //��������ͼƬ
IMAGE img_MenuTitleG3; //��������ͼƬ
IMAGE img_MenuTitleG4; //��������ͼƬ
IMAGE img_MenuTitleG5; //��������ͼƬ
IMAGE img_MenuTitleB1; //��������ͼƬ
IMAGE img_MenuTitleB2; //��������ͼƬ
IMAGE img_MenuTitleB3; //��������ͼƬ
IMAGE img_MenuTitleB4; //��������ͼƬ
IMAGE img_MenuTitleB5; //��������ͼƬ
IMAGE img_MenuTitleO1; //��������ͼƬ
IMAGE img_MenuTitleO2; //��������ͼƬ
IMAGE img_MenuTitleO3; //��������ͼƬ
IMAGE img_MenuTitleO4; //��������ͼƬ
IMAGE img_MenuTitleO5; //��������ͼƬ

int IsLeaveMenu; //�����Ƿ��ӡ��ʼ����
IMAGE img_Developer1;
IMAGE img_Developer2;

//5.������
MOUSEMSG mouse;		// ���������Ϣ	


//6.��ͣ,�˳����浵��������ť
IMAGE img_PauseButton;  //������ͣ��ťͼƬ
IMAGE img_Continue;
IMAGE img_Exit;
IMAGE img_Save;
IMAGE img_Load;
IMAGE img_Pause_Black;
int IsPauseButton; //�Ƿ��°�ť
int IsExit; //�Ƿ��˳�

//7.�������ǻ���
int IsLoadGamingFrame;
#define Frame_x_Begin 350
#define Frame_x_End 950
#define Frame_y_Begin 400
#define Frame_y_End 600

//8.���ֵ���
#pragma comment(lib,"Winmm.lib")

//9.ȫ������(need debug)
void full_screen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
	/* ���ô�����Ϣ ��� ȡ�����������߿� */
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

//10.�������
int IsLeavePlot;
int IsClean;
IMAGE Plot1;
IMAGE Plot2;
IMAGE Plot3;
IMAGE Plot4;
IMAGE Plot5;
IMAGE Plot6;
IMAGE Plot7;
IMAGE Plot8;
IMAGE Plot9;
IMAGE Plot10;
IMAGE Plot11;
IMAGE Plot12;
IMAGE Plot13;
IMAGE Plot14;
IMAGE Plot15;
IMAGE Plot16;
IMAGE Plot17;
IMAGE Plot18;
IMAGE Plot19;
IMAGE Plot20;
IMAGE Plot21;
IMAGE Plot22;
IMAGE Plot23;
IMAGE Plot24;
IMAGE Plot25;
IMAGE Plot26;
IMAGE Plot27;
IMAGE Plot28;
IMAGE Plot29;
IMAGE Plot30;
IMAGE Plot31;
IMAGE Plot32;
IMAGE Plot33;
IMAGE Plot34;
IMAGE Plot35;
IMAGE Plot36;
IMAGE Plot37;
IMAGE Plot38;
IMAGE Plot39;
IMAGE Plot40;
IMAGE Plot41;
IMAGE Plot42;
IMAGE Plot43;
IMAGE Plot44;
IMAGE Plot445;
IMAGE Plot45;
IMAGE Plot455;
IMAGE Plot46;
IMAGE Plot465;
IMAGE Plot47;
IMAGE Plot475;
IMAGE Plot48;
IMAGE Plot485;
IMAGE Plot49;

IMAGE black;
IMAGE Plot2_1;
IMAGE Plot2_2;
IMAGE Plot2_3;
IMAGE Plot2_4;
IMAGE Plot2_5;
IMAGE Plot2_6;
IMAGE Plot2_7;
IMAGE Plot2_8;
IMAGE Plot2_9;
IMAGE Plot2_10;
IMAGE Plot2_11;
IMAGE Plot2_12;
IMAGE Plot2_13;
IMAGE Plot2_14;
IMAGE Plot2_15;
IMAGE Plot2_16;
IMAGE Plot2_17;
IMAGE Plot2_18;
IMAGE Plot2_19;

IMAGE Plot3_1;
IMAGE Plot3_2;
IMAGE Plot3_3;
IMAGE Plot3_4;
IMAGE Plot3_5;
IMAGE Plot3_6;
IMAGE Plot3_7;
IMAGE Plot3_8;
IMAGE Plot3_9;
IMAGE Plot3_10;
IMAGE Plot3_11;
IMAGE Plot3_12;
IMAGE Plot3_13;
IMAGE Plot3_14;
IMAGE Plot3_15;
IMAGE Plot3_16;
IMAGE Plot3_17;
IMAGE Plot3_18;
IMAGE Plot3_19;
IMAGE Plot3_20;
IMAGE Plot3_21;
IMAGE Plot3_22;
IMAGE Plot3_23;
IMAGE Plot3_24;
IMAGE Plot3_25;
IMAGE Plot3_26;
IMAGE Plot3_27;
IMAGE Plot3_28;
IMAGE Plot3_29;
IMAGE Plot3_30;
IMAGE Plot3_31;
IMAGE Plot3_32;
IMAGE Plot3_33;
IMAGE Plot3_34;
IMAGE Plot3_35;
IMAGE Plot3_36;
IMAGE Plot3_37;
IMAGE Plot3_38;
IMAGE Plot3_39;

//11.��Ļ
IMAGE danmu1;
IMAGE danmu2;
IMAGE danmu3;
IMAGE danmu4;
IMAGE danmu5;
IMAGE danmu6;
IMAGE danmu11;
IMAGE danmu12;
IMAGE danmu13;
IMAGE danmu14;
IMAGE danmu15;
IMAGE danmu16;
IMAGE danmu21;
IMAGE danmu22;
IMAGE danmu23;
IMAGE danmu24;
IMAGE danmu25;
IMAGE danmu26;
IMAGE danmu31;
IMAGE danmu32;
IMAGE danmu33;
IMAGE danmu34;
IMAGE danmu35;
IMAGE danmu36;

//12.��������
IMAGE END;
int SelectEnd;  //0ΪGE��1ΪBE
int IsBreak;

//13.monster
IMAGE feichuan1, feichuan2, feichuan3, feichuan4, feichuan5, beida1, beida2, xuetiao1, xuetiao2, xuetiao3, xuetiao4, xuetiao5;

IMAGE image_baozha1, image_baozha2, image_baozha3, image_baozha4, image_baozha5, image_baozha6, image_baozha7, image_baozha8, image_baozha9, image_baozha10, image_baozha11, image_baozha12, image_baozha13, image_baozha14, image_baozha15, image_baozha16, image_baozha17, image_baozha18, image_baozha19, image_baozha20, image_baozha21, image_baozha22, image_baozha23, image_baozha24, image_baozha25, image_baozha26, image_baozha27, image_baozha28, image_baozha29, image_baozha30, image_baozha31, image_baozha32, image_baozha33, image_baozha34, image_baozha35, image_baozha36, image_baozha37, image_baozha38, image_baozha39, image_baozha40, image_baozha41, image_baozha42, image_baozha43, image_baozha44, image_baozha45, image_baozha46, image_baozha47, image_baozha48, image_baozha49, image_baozha50, image_baozha51, image_baozha52, image_baozha53, image_baozha54;

//14.others
//�ж��Ƿ���ͼ
int IsLoadD;
int IsP = 0;
/******************************************************************************************************************************/


//����part
//1.��ʼ��startup

//��Ļλ�ó�ʼ��
void dstart();



//��һ�׶κ��ҩƿˢ��ʱ��
void timer1(void*)
{
	Sleep(17000);
	hero.a = 1;
	prop.Reach = 0;
	_endthread();
}


//��һ�׶κ���ҩƿˢ��ʱ��
void timer2(void*)
{
	Sleep(13000);
	hero.b = 1;
	prop1.Reach = 0;
	_endthread();
}

//������ʧʱ��
void timer3(void*)
{
	Sleep(7000);
	hero.c = 1;
	_endthread();
}

//��һ�׶�ˢ��ʱ��
void timer4(void*)
{
	Sleep(5000);
	hero.d = 1;
	_endthread();
}

//�����޵��ж�
void timer5(void*)
{
	Sleep(1500);
	hero.IsZhuang = 0;
	_endthread();
}



//��һ�׶ζ�����ƿ
void timer8(void*)
{
	Sleep(5000);
	prop.position_x = rand() % (Frame_x_End - Frame_x_Begin - 60) + Frame_x_Begin + 30;
	prop.position_y = rand() % (Frame_y_End - Frame_y_Begin - 60) + Frame_y_Begin + 30;
	hero.d = 1;
	_endthread();
}

//��һ�׶ζ�����ƿ
void timer9(void*)
{
	Sleep(5000);
	prop1.position_x = rand() % (Frame_x_End - Frame_x_Begin - 60) + Frame_x_Begin + 30;
	prop1.position_y = rand() % (Frame_y_End - Frame_y_Begin - 60) + Frame_y_Begin + 30;
	hero.d = 1;
	_endthread();
}

//startup����
void startup()
{
	//��ʼ������
	//1.��ʼ����ɫ
	hero.position_x = Frame_x_Begin+2;
	hero.position_y = Frame_y_Begin+2;
	hero.speed = 1;
	hero.blood = 3;
	hero.IsZhuang = 0;
	hero.a = 0;
	hero.b = 0;
	hero.c = 1;

	//2.��ʼ������
	initgraph(Width, High);

	//3. ���ſ�ʼ�˵�����
	mciSendString("open ..\\data\\MenuMusic.mp3 alias Menubk", NULL, 0, NULL);
	mciSendString("play Menubk repeat", NULL, 0, NULL);

	//4.��Ļλ�ó�ʼ��
	dstart();
	//5.����λ�ó�ʼ��
	
	prop.position_x = rand() % (Frame_x_End - Frame_x_Begin - 60) + Frame_x_Begin + 30;
	prop.position_y = rand() % (Frame_y_End - Frame_y_Begin - 60) + Frame_y_Begin + 30;
	prop1.position_x = rand() % (Frame_x_End - Frame_x_Begin - 60) + Frame_x_Begin + 30;
	prop1.position_y = rand() % (Frame_y_End - Frame_y_Begin - 60) + Frame_y_Begin + 30;

	prop.FlushTime = 0;
	prop.IsFlush = 0;
	prop1.FlushTime = 0;
	prop1.IsFlush = 0;
	prop1.ncount = 2000;
	prop.Reach = 0;
	prop1.Reach = 0;
	prop.Reach2 = 0;
	prop.Reach2 = 0;

	//6.monster
	monster.IsHit = 5;//����monster.blood�Ƿ�ı䣬����ı����ӡ�������ͼ��
	monster.Hit = 0;
	monster.i = 0;
	monster.blood = 5;
	monster.IsMR = 0;

	//7.others
	IsLeaveMenu = 0;
	IsPauseButton=0; //�Ƿ��°�ť
	IsExit=0; //�Ƿ��˳�
    IsLoadGamingFrame = 0;
	IsLeavePlot = 0;
	IsClean = 0;
	SelectEnd = 0;  //0ΪGE��1ΪBE
	IsBreak = 0;
	
	prop.judge = 1;
	prop1.judge=1;
	IsLoadD = 0;

	//last.��ʼ��������
	BeginBatchDraw();
}

//��Ļλ�ó�ʼ��
void dstart() 
{
	dm.enemy_y1 = Frame_y_Begin-40;
	dm.enemy_x1 = rand() % (Frame_x_End/2- Frame_x_Begin/2-22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y2 = Frame_y_Begin - 800;
	dm.enemy_x2 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y3 = Frame_y_Begin -800 ;
	dm.enemy_x3 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y11 = Frame_y_Begin - 800;
	dm.enemy_x11 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y12 = Frame_y_Begin - 800;
	dm.enemy_x12 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y13 = Frame_y_Begin - 800;
	dm.enemy_x13 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y21 = Frame_y_Begin - 800;
	dm.enemy_x21 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y22 = Frame_y_Begin - 800;
	dm.enemy_x22 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y23 = Frame_y_Begin - 800;
	dm.enemy_x23 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y31 = Frame_y_Begin - 800;
	dm.enemy_x31 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y32 = Frame_y_Begin - 800;
	dm.enemy_x32 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y33 = Frame_y_Begin - 800;
	dm.enemy_x33 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	//����
	dm.enemy_y4 = Frame_y_End + 24;
	dm.enemy_x4 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y5 = Frame_y_End + 800;
	dm.enemy_x5 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y6 = Frame_y_End + 800;
	dm.enemy_x6 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y14 = Frame_y_End + 800;
	dm.enemy_x14 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y15 = Frame_y_End + 800;
	dm.enemy_x15 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y16 = Frame_y_End + 800;
	dm.enemy_x16 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y24 = Frame_y_End + 800;
	dm.enemy_x24 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y25 = Frame_y_End + 800;
	dm.enemy_x25 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y26 = Frame_y_End + 800;
	dm.enemy_x26 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y34 = Frame_y_End + 800;
	dm.enemy_x34 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y35 = Frame_y_End + 800;
	dm.enemy_x35 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	dm.enemy_y36 = Frame_y_End + 800;
	dm.enemy_x36 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 22) + Frame_y_Begin;//���λ��ˢ��
	//����
	
	srand((unsigned int)time(0));
}


/******************************************************************************************************************************/


//2.��ʾ����show

//�����ɫ
void SetRandColor();
//��ʼ�˵�
void StartupMenu();

//�������ǻ���
void LoadGamingFrame();
//�������� 
void Plot();
//��Ļ��ʾ
void dshow();


//show��������
void show()
{

	//1��չʾ��ʼ����
	if (IsLeaveMenu == 0) StartupMenu();

	//2)�������
	else if ((IsLeaveMenu == 1) && (IsLeavePlot == 0))
	{
		//�ص���ʼ�˵�����
		mciSendString("close Menubk", NULL, 0, NULL);

		Plot();


	}
	//3����Ϸ����
	else if ((IsLeaveMenu == 1) && (IsLeavePlot == 1))
		
	{
			//monster
			if (monster.blood != monster.IsHit)//���
			{
				
				if ((monster.Hit >= 0) && (monster.Hit < 50))
				{
					loadimage(&beida1, "..\\data\\GAME\\beida1~1.bmp");
					putimage(455, 95, &beida1);
					monster.Hit++;
				}
				else if ((monster.Hit >= 50) && (monster.Hit < 100))
				{
					loadimage(&beida2, "..\\data\\GAME\\beida2~1.bmp");
					putimage(455, 95, &beida2);
					monster.Hit++;
				}
				if (monster.Hit == 100) {
					monster.IsHit--;
					monster.Hit = 0;
				}
			}

			else
			{

				if ((monster.i >= 0) && (monster.i < 50))
				{
					loadimage(&feichuan1, "..\\data\\GAME\\1.bmp");
					putimage(455, 95, &feichuan1);
					monster.i++;
					Sleep(1);
				}
				else if ((monster.i >= 50) && (monster.i < 100))
				{
					loadimage(&feichuan2, "..\\data\\GAME\\2.bmp");
					putimage(455, 95, &feichuan2);
					monster.i++;
					Sleep(1);
				}
				else if ((monster.i >= 100) && (monster.i < 150))
				{
					loadimage(&feichuan3, "..\\data\\GAME\\3.bmp");
					putimage(455, 95, &feichuan3);
					monster.i++;
					Sleep(1);
				}
				else if ((monster.i >= 150) && (monster.i < 200))
				{
					loadimage(&feichuan4, "..\\data\\GAME\\4.bmp");
					putimage(455, 95, &feichuan4);
					monster.i++;
					Sleep(1);
				}
				else if ((monster.i >= 200) && (monster.i < 250))
				{
					loadimage(&feichuan5, "..\\data\\GAME\\5.bmp");
					putimage(455, 95, &feichuan5);
					Sleep(1);
					monster.i++;
					if (monster.i == 250) monster.i = 0;
				}
			}
		
		
			
			

		//�������ǻ���
        LoadGamingFrame();

		//���ع���Ѫ��
		if (monster.blood == 5)//count:Ѫ������
		{
			loadimage(&xuetiao1, "..\\data\\GAME\\xuetiao\\0.1xue.bmp");
			putimage(440, 15, &xuetiao1);//���Ѫ��Ѫ��
		}
		if (monster.blood == 4)
		{
			loadimage(&xuetiao2, "..\\data\\GAME\\xuetiao\\1.1xue.bmp");
			putimage(440, 15, &xuetiao2);//�ĵ�Ѫ��Ѫ��

		}
		if (monster.blood == 3)
		{
			loadimage(&xuetiao3, "..\\data\\GAME\\xuetiao\\2.1xue.bmp");
			putimage(440, 15, &xuetiao3);//����

		}
		if (monster.blood == 2)
		{
			loadimage(&xuetiao4, "..\\data\\GAME\\xuetiao\\3.1xue.bmp");
			putimage(440, 15, &xuetiao4);//����

		}
		if (monster.blood == 1)
		{
			loadimage(&xuetiao5, "..\\data\\GAME\\xuetiao\\4.1xue.bmp");
			putimage(440, 15, &xuetiao5);//һ��
		}
		
		if ((monster.IsMR==0) && (monster.blood == 1))
		{
			mciSendString("open ..\\data\\MonsterRage.mp3 alias MR", NULL, 0, NULL);
			mciSendString("play MR ", NULL, 0, NULL);
			monster.IsMR = 1;
		}

		//�������Ǽ���Ѫ��
		loadimage(&img_hero, "..\\data\\hero.PNG");
		putimage(hero.position_x, hero.position_y, &img_hero);

		if (hero.blood >= 3) 
		{
			loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero1.bmp");
			putimage(500, 670, &img_HeroBlood);
		}
		else if (hero.blood==2)
		{
			loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero2.bmp");
			putimage(500, 670, &img_HeroBlood);
		}
		else if (hero.blood == 1)
		{
			loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero3.bmp");
			putimage(500, 670, &img_HeroBlood);
		}
		else if (hero.blood == 0)
		{
			loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero4.bmp");
			putimage(500, 670, &img_HeroBlood);
			Sleep(500);
		}

		//���ص���
		loadimage(&img_red, "..\\data\\redpotion.png");
		loadimage(&img_blue, "..\\data\\bluepotion.png");
		if ((IsLoadD==0)&&(hero.d==0)) _beginthread(timer4, 0, NULL);
		
		if (hero.d == 1)
		{
			if (prop.judge== 1)
			putimage(prop.position_x, prop.position_y, &img_red);
			if (prop1.judge == 1)
			putimage(prop1.position_x, prop1.position_y, &img_blue);
		}

		

	    //��Ļ����
	    dshow();

	}
	FlushBatchDraw();
}



/******�ֺ�������******/

//��Ļ��ʾ
void dshow() 
{
	//����
	if (dm.enemy_x1 <= Frame_x_End && dm.enemy_x1 >= Frame_x_Begin && dm.enemy_y1 < Frame_y_End-23 && dm.enemy_y1 >= Frame_y_Begin)
	{
         loadimage(&danmu1, "..\\data\\danmu.jpg");
		 putimage(dm.enemy_x1, dm.enemy_y1, &danmu1);
	}
	
	if (dm.enemy_x2 <= Frame_x_End && dm.enemy_x2 >= Frame_x_Begin && dm.enemy_y2 < Frame_y_End - 23 && dm.enemy_y2 >= Frame_y_Begin)
	{
		loadimage(&danmu2, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x2, dm.enemy_y2, &danmu2);
	}
	
	if (dm.enemy_x3 <= Frame_x_End && dm.enemy_x3 >= Frame_x_Begin && dm.enemy_y3 < Frame_y_End - 23 && dm.enemy_y3 >= Frame_y_Begin)
	{
		loadimage(&danmu3, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x3, dm.enemy_y3, &danmu3);
	}
	
	if (dm.enemy_x11 <= Frame_x_End && dm.enemy_x11 >= Frame_x_Begin && dm.enemy_y11 < Frame_y_End - 23 && dm.enemy_y11 >= Frame_y_Begin)
	{
		loadimage(&danmu11, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x11, dm.enemy_y11, &danmu11);
	}
	
	if (dm.enemy_x12 <= Frame_x_End && dm.enemy_x12 >= Frame_x_Begin && dm.enemy_y12 < Frame_y_End - 23 && dm.enemy_y12 >= Frame_y_Begin)
	{
		loadimage(&danmu12, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x12, dm.enemy_y12, &danmu12);
	}
	
	if (dm.enemy_x13 <= Frame_x_End && dm.enemy_x13 >= Frame_x_Begin && dm.enemy_y13 < Frame_y_End - 23 && dm.enemy_y13 >= Frame_y_Begin)
	{
		loadimage(&danmu13, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x13, dm.enemy_y13, &danmu13);
	}
	
	if (dm.enemy_x21 <= Frame_x_End && dm.enemy_x21 >= Frame_x_Begin && dm.enemy_y21 < Frame_y_End - 23 && dm.enemy_y21 >= Frame_y_Begin)
	{
		loadimage(&danmu21, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x21, dm.enemy_y21, &danmu21);
	}
	
	if (dm.enemy_x22 <= Frame_x_End && dm.enemy_x22 >= Frame_x_Begin && dm.enemy_y22 < Frame_y_End - 23 && dm.enemy_y22 >= Frame_y_Begin)
	{
		loadimage(&danmu22, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x22, dm.enemy_y22, &danmu22);
	}
	
	if (dm.enemy_x23 <= Frame_x_End && dm.enemy_x23 >= Frame_x_Begin && dm.enemy_y23 < Frame_y_End - 23 && dm.enemy_y23 >= Frame_y_Begin)
	{
		loadimage(&danmu23, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x23, dm.enemy_y23, &danmu23);
	}
	
	if (dm.enemy_x31 <= Frame_x_End && dm.enemy_x31 >= Frame_x_Begin && dm.enemy_y31 < Frame_y_End - 23 && dm.enemy_y31 >= Frame_y_Begin)
	{
		loadimage(&danmu31, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x31, dm.enemy_y31, &danmu31);
	}
	
	if (dm.enemy_x32 <= Frame_x_End && dm.enemy_x32 >= Frame_x_Begin && dm.enemy_y32 < Frame_y_End - 23 && dm.enemy_y32 >= Frame_y_Begin)
	{
		loadimage(&danmu32, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x32, dm.enemy_y32, &danmu32);
	}
	
	if (dm.enemy_x33 <= Frame_x_End && dm.enemy_x33 >= Frame_x_Begin && dm.enemy_y33 < Frame_y_End - 23 && dm.enemy_y33 >= Frame_y_Begin)
	{
		loadimage(&danmu33, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x33, dm.enemy_y33, &danmu33);
	}
	

	//����
	if (dm.enemy_x4 <= Frame_x_End && dm.enemy_x4 >= Frame_x_Begin && dm.enemy_y4 < Frame_y_End-23  && dm.enemy_y4 > Frame_y_Begin+23)
	{
		loadimage(&danmu4, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x4, dm.enemy_y4, &danmu4);
	}
	
	if (dm.enemy_x5 <= Frame_x_End && dm.enemy_x5 >= Frame_x_Begin && dm.enemy_y5 < Frame_y_End-23 && dm.enemy_y5 > Frame_y_Begin+23)
	{
		loadimage(&danmu5, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x5, dm.enemy_y5, &danmu5);
	}
	
	if (dm.enemy_x6 <= Frame_x_End && dm.enemy_x6 >= Frame_x_Begin && dm.enemy_y6 < Frame_y_End-23 && dm.enemy_y6 > Frame_y_Begin+23)
	{
		loadimage(&danmu6, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x6, dm.enemy_y6, &danmu6);
	}
	
	if (dm.enemy_x14 <= Frame_x_End && dm.enemy_x14 >= Frame_x_Begin && dm.enemy_y14 < Frame_y_End-23 && dm.enemy_y14 > Frame_y_Begin + 23)
	{
		loadimage(&danmu14, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x14, dm.enemy_y14, &danmu14);
	}
	
	if (dm.enemy_x15 <= Frame_x_End && dm.enemy_x15 >= Frame_x_Begin && dm.enemy_y15 < Frame_y_End-23 && dm.enemy_y15 >Frame_y_Begin + 23)
	{
		loadimage(&danmu15, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x15, dm.enemy_y15, &danmu15);
	}
	
	if (dm.enemy_x16 <= Frame_x_End && dm.enemy_x16 >= Frame_x_Begin && dm.enemy_y16 < Frame_y_End-23 && dm.enemy_y16 >Frame_y_Begin + 23)
	{
		loadimage(&danmu16, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x16, dm.enemy_y16, &danmu16);
	}
	
	if (dm.enemy_x24 <= Frame_x_End && dm.enemy_x24 >= Frame_x_Begin && dm.enemy_y24 < Frame_y_End-23 && dm.enemy_y24 > Frame_y_Begin + 23)
	{
		loadimage(&danmu24, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x24, dm.enemy_y24, &danmu24);
	}
	
	if (dm.enemy_x25 <= Frame_x_End && dm.enemy_x25 >= Frame_x_Begin && dm.enemy_y25 < Frame_y_End-23 && dm.enemy_y25 >Frame_y_Begin + 23)
	{
		loadimage(&danmu25, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x25, dm.enemy_y25, &danmu25);
	}
	
	if (dm.enemy_x26 <= Frame_x_End && dm.enemy_x26 >= Frame_x_Begin && dm.enemy_y26 < Frame_y_End-23 && dm.enemy_y26 >Frame_y_Begin + 23)
	{
		loadimage(&danmu26, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x26, dm.enemy_y26, &danmu26);
	}
	
	if (dm.enemy_x34 <= Frame_x_End && dm.enemy_x34 >= Frame_x_Begin && dm.enemy_y34 < Frame_y_End-23 && dm.enemy_y34 > Frame_y_Begin + 23)
	{
		loadimage(&danmu34, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x34, dm.enemy_y34, &danmu34);
	}
	
	if (dm.enemy_x35 <= Frame_x_End && dm.enemy_x35 >= Frame_x_Begin && dm.enemy_y35 < Frame_y_End-23 && dm.enemy_y35 >Frame_y_Begin + 23)
	{
		loadimage(&danmu35, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x35, dm.enemy_y35, &danmu35);
	}
	
	if (dm.enemy_x36 <= Frame_x_End && dm.enemy_x36 >= Frame_x_Begin && dm.enemy_y36 < Frame_y_End-23 && dm.enemy_y36 >Frame_y_Begin + 23)
	{
		loadimage(&danmu36, "..\\data\\danmu.jpg");
		putimage(dm.enemy_x36, dm.enemy_y36, &danmu36);
	}
	
}

//�����ɫ
void SetRandColor()
{
	char r, g, b;

	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;

	settextcolor(RGB(r, g, b));
}

//���ش浵
void LoadFile();
void InputFile(const char* filename);  //�浵����
void ReadFile(const char* filename); //��������

//��ʼ�˵�
void StartupMenu()
{
	//����
	 loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	 putimage(250, 200, &img_MenuTitle);


	//չʾ������Ա����
	loadimage(&img_Developer1, "..\\data\\Developer1.png");
	putimage(0, 600, &img_Developer1);
	loadimage(&img_Developer2, "..\\data\\Developer2.png");
	putimage(0, 680, &img_Developer2);

	//��ʼ��ʾclick.....
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 25;						// ��������߶�Ϊ 25
	_tcscpy_s(f.lfFaceName, sizeof("Consolas"), _T("Consolas"));  // ��������
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ����� 
	settextcolor(WHITE);	                //������Ϊ��ɫ
	settextstyle(&f);						// ����������ʽ

	//�˵���ȡ�浵
	if (GetAsyncKeyState(0x4C) & 0x8000)
	{
	
			//�ص���ʼ�˵�����
			mciSendString("close Menubk", NULL, 0, NULL);

			//ս�裬��
			mciSendString("open ..\\data\\FIGHT.mp3 alias FIGHT", NULL, 0, NULL);
			mciSendString("play FIGHT repeat", NULL, 0, NULL);
			

			
			IsLeaveMenu = 1; 
			IsLeavePlot = 1;
			IsClean = 1;
			LoadFile();

			
		
	}

	if ((timeflag>=0)&&(timeflag <= 500)) {
		settextcolor(WHITE);	           //������Ϊ��ɫ
		outtextxy(475, 500, _T("Click to start the game"));
		outtextxy(475, 550, _T("Press 'L' to load files"));
		timeflag += 25;
		Sleep(50);
	}
	else if ((timeflag > 500) && (timeflag <= 1000)) {
		settextcolor(BLACK);
		timeflag += 25;
		Sleep(50);
	}  //������˸
	else if (timeflag > 1000) timeflag = 0;
	FlushBatchDraw();
	settextcolor(WHITE);

}







//�������ǻ���
void LoadGamingFrame()
{
	int Print_x = Frame_x_Begin;
	int Print_y = Frame_y_Begin;
	int Print_v = 1;
	int Print_xn = Print_x+ Print_v;
	int Print_yn = Print_y+ Print_v;
	int xa = Frame_x_Begin - 1;
	int xb = Frame_x_Begin + 1;
	int ya = Frame_y_Begin - 1;
	int yb = Frame_y_Begin + 1;
	int xc = Frame_x_End - 1;
	int xd = Frame_x_End + 1;
	int yc = Frame_y_End - 1;
	int yd = Frame_y_End + 1;

	if (IsLoadGamingFrame == 0)  //���δ�ӡ
	{
		while ((Print_xn <= Frame_x_End)) //��ӡ������
		{
			setcolor(WHITE);    //������ɫRGB(��,��,��)
			line(Print_x, ya, Print_xn, ya);
			line(Print_x, Frame_y_Begin, Print_xn, Frame_y_Begin);       //����
			line(Print_x, yb, Print_xn, yb);       //����
			line(Print_x, yc, Print_xn, yc);
			line(Print_x, Frame_y_End, Print_xn, Frame_y_End);       //����
			line(Print_x, yd, Print_xn, yd);       //����

			FlushBatchDraw();
			Sleep(5);

			Print_x = Print_xn;
			Print_xn += Print_v;
		}

		while ((Print_yn <= Frame_y_End)) //��ӡ������
		{
			setcolor(WHITE);    //������ɫRGB(��,��,��)
			line(xa, Print_y, xa, Print_yn);
			line(Frame_x_Begin, Print_y, Frame_x_Begin, Print_yn);
			line(xb, Print_y, xb, Print_yn);
			line(xc, Print_y, xc, Print_yn);
			line(Frame_x_End, Print_y, Frame_x_End, Print_yn);
			line(xd, Print_y, xd, Print_yn);

			FlushBatchDraw();
			Sleep(5);

			Print_y = Print_yn;
			Print_yn += Print_v;
		}
		IsLoadGamingFrame = 1; //ֻ��ӡһ��
	}

	else  //������ӡ
	{
		setcolor(WHITE);    //������ɫRGB(��,��,��)
		line(Frame_x_Begin, Frame_y_Begin, Frame_x_End, Frame_y_Begin);
		line(Frame_x_Begin, Frame_y_Begin-1, Frame_x_End, Frame_y_Begin-1);
		line(Frame_x_Begin, Frame_y_Begin+1, Frame_x_End, Frame_y_Begin+1);

		line(Frame_x_Begin, Frame_y_End, Frame_x_End, Frame_y_End);
		line(Frame_x_Begin, Frame_y_End-1, Frame_x_End, Frame_y_End-1);
		line(Frame_x_Begin, Frame_y_End+1, Frame_x_End, Frame_y_End+1);

		line(Frame_x_End-1, Frame_y_Begin, Frame_x_End-1, Frame_y_End);
		line(Frame_x_End, Frame_y_Begin, Frame_x_End, Frame_y_End);
		line(Frame_x_End+1, Frame_y_Begin, Frame_x_End+1, Frame_y_End);

		line(Frame_x_Begin, Frame_y_Begin, Frame_x_Begin, Frame_y_End);
		line(Frame_x_Begin-1, Frame_y_Begin, Frame_x_Begin-1, Frame_y_End);
		line(Frame_x_Begin+1, Frame_y_Begin, Frame_x_Begin+1, Frame_y_End);

	}
}




//�������� 
void Plot()
{
	

	//PART ONE*************

	//������
	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	//����part
	loadimage(&Plot1, "..\\data\\Plot1.png");
	putimage(0, 0, &Plot1);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2, "..\\data\\Plot2.png");
	putimage(0, 0, &Plot2);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3, "..\\data\\Plot3.png");
	putimage(0, 0, &Plot3);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot4, "..\\data\\Plot4.png");
	putimage(0, 0, &Plot4);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot5, "..\\data\\Plot5.png");
	putimage(0, 0, &Plot5);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot6, "..\\data\\Plot6.png");
	putimage(0, 0, &Plot6);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot7, "..\\data\\Plot7.png");
	putimage(0, 0, &Plot7);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot8, "..\\data\\Plot8.png");
	putimage(0, 0, &Plot8);
	FlushBatchDraw();
	Sleep(300);

	mciSendString("close KeyB", NULL, 0, NULL);

	loadimage(&Plot7, "..\\data\\Plot7.png");
	putimage(0, 0, &Plot7);
	FlushBatchDraw();
	Sleep(300);
	loadimage(&Plot8, "..\\data\\Plot8.png");
	putimage(0, 0, &Plot8);
	FlushBatchDraw();
	Sleep(300);
	loadimage(&Plot7, "..\\data\\Plot7.png");
	putimage(0, 0, &Plot7);
	FlushBatchDraw();
	Sleep(300);
	loadimage(&Plot8, "..\\data\\Plot8.png");
	putimage(0, 0, &Plot8);
	FlushBatchDraw();
	Sleep(300);

	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	loadimage(&Plot9, "..\\data\\Plot9.png");
	putimage(0, 0, &Plot9);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot10, "..\\data\\Plot10.png");
	putimage(0, 0, &Plot10);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot11, "..\\data\\Plot11.png");
	putimage(0, 0, &Plot11);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot12, "..\\data\\Plot12.png");
	putimage(0, 0, &Plot12);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot13, "..\\data\\Plot13.png");
	putimage(0, 0, &Plot13);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot14, "..\\data\\Plot14.png");
	putimage(0, 0, &Plot14);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot15, "..\\data\\Plot15.png");
	putimage(0, 0, &Plot15);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot16, "..\\data\\Plot16.png");
	putimage(0, 0, &Plot16);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot17, "..\\data\\Plot17.png");
	putimage(0, 0, &Plot17);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot18, "..\\data\\Plot18.png");
	putimage(0, 0, &Plot18);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot19, "..\\data\\Plot19.png");
	putimage(0, 0, &Plot19);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot20, "..\\data\\Plot20.png");
	putimage(0, 0, &Plot20);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot21, "..\\data\\Plot21.png");
	putimage(0, 0, &Plot21);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot22, "..\\data\\Plot22.png");
	putimage(0, 0, &Plot22);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot23, "..\\data\\Plot23.png");
	putimage(0, 0, &Plot23);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot24, "..\\data\\Plot24.png");
	putimage(0, 0, &Plot24);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot25, "..\\data\\Plot25.png");
	putimage(0, 0, &Plot25);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot26, "..\\data\\Plot26.png");
	putimage(0, 0, &Plot26);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot27, "..\\data\\Plot27.png");
	putimage(0, 0, &Plot27);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot28, "..\\data\\Plot28.png");
	putimage(0, 0, &Plot28);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot29, "..\\data\\Plot29.png");
	putimage(0, 0, &Plot29);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot30, "..\\data\\Plot30.png");
	putimage(0, 0, &Plot30);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot31, "..\\data\\Plot31.png");
	putimage(0, 0, &Plot31);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot32, "..\\data\\Plot32.png");
	putimage(0, 0, &Plot32);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot33, "..\\data\\Plot33.png");
	putimage(0, 0, &Plot33);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot34, "..\\data\\Plot34.png");
	putimage(0, 0, &Plot34);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot35, "..\\data\\Plot35.png");
	putimage(0, 0, &Plot35);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot36, "..\\data\\Plot36.png");
	putimage(0, 0, &Plot36);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot37, "..\\data\\Plot37.png");
	putimage(0, 0, &Plot37);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot38, "..\\data\\Plot38.png");
	putimage(0, 0, &Plot38);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot39, "..\\data\\Plot39.png");
	putimage(0, 0, &Plot39);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot40, "..\\data\\Plot40.png");
	putimage(0, 0, &Plot40);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot41, "..\\data\\Plot41.png");
	putimage(0, 0, &Plot41);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot42, "..\\data\\Plot42.png");
	putimage(0, 0, &Plot42);
	FlushBatchDraw();

	//�ص�������
	mciSendString("close KeyB", NULL, 0, NULL);

	Sleep(500);
	loadimage(&Plot43, "..\\data\\Plot43.png");
	putimage(0, 0, &Plot43);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&Plot44, "..\\data\\Plot44.png");
	putimage(0, 0, &Plot44);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&Plot445, "..\\data\\Plot445.png");
	putimage(0, 0, &Plot445);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot45, "..\\data\\Plot45.png");
	putimage(0, 0, &Plot45);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot455, "..\\data\\Plot455.png");
	putimage(0, 0, &Plot455);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot46, "..\\data\\Plot46.png");
	putimage(0, 0, &Plot46);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot465, "..\\data\\Plot455.png");
	putimage(0, 0, &Plot455);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot47, "..\\data\\Plot47.png");
	putimage(0, 0, &Plot47);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot475, "..\\data\\Plot475.png");
	putimage(0, 0, &Plot475);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot48, "..\\data\\Plot48.png");
	putimage(0, 0, &Plot48);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot485, "..\\data\\Plot485.png");
	putimage(0, 0, &Plot485);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&Plot49, "..\\data\\Plot49.png");
	putimage(0, 0, &Plot49);
	FlushBatchDraw();
	Sleep(100);


	//PART TWO*************

	mciSendString("open ..\\data\\Plot2.mp3 alias P2", NULL, 0, NULL);
	mciSendString("play P2 repeat", NULL, 0, NULL); 

	Sleep(500);

	loadimage(&Plot2_1, "..\\data\\Plot2_1.png");
	putimage(0, 0, &Plot2_1);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_2, "..\\data\\Plot2_2.png");
	putimage(0, 0, &Plot2_2);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_3, "..\\data\\Plot2_3.png");
	putimage(0, 0, &Plot2_3);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_4, "..\\data\\Plot2_4.png");
	putimage(0, 0, &Plot2_4);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_5, "..\\data\\Plot2_5.png");
	putimage(0, 0, &Plot2_5);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_6, "..\\data\\Plot2_6.png");
	putimage(0, 0, &Plot2_6);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_7, "..\\data\\Plot2_7.png");
	putimage(0, 0, &Plot2_7);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_8, "..\\data\\Plot2_8.png");
	putimage(0, 0, &Plot2_8);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_9, "..\\data\\Plot2_9.png");
	putimage(0, 0, &Plot2_9);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_10, "..\\data\\Plot2_10.png");
	putimage(0, 0, &Plot2_10);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_11, "..\\data\\Plot2_11.png");
	putimage(0, 0, &Plot2_11);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_12, "..\\data\\Plot2_12.png");
	putimage(0, 0, &Plot2_12);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_13, "..\\data\\Plot2_13.png");
	putimage(0, 0, &Plot2_13);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_14, "..\\data\\Plot2_14.png");
	putimage(0, 0, &Plot2_14);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_15, "..\\data\\Plot2_15.png");
	putimage(0, 0, &Plot2_15);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_16, "..\\data\\Plot2_16.png");
	putimage(0, 0, &Plot2_16);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_17, "..\\data\\Plot2_17.png");
	putimage(0, 0, &Plot2_17);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_18, "..\\data\\Plot2_18.png");
	putimage(0, 0, &Plot2_18);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_19, "..\\data\\Plot2_19.png");
	putimage(0, 0, &Plot2_19);
	FlushBatchDraw();
	Sleep(2000);
	loadimage(&Plot2_18, "..\\data\\Plot2_18.png");
	putimage(0, 0, &Plot2_18);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_17, "..\\data\\Plot2_17.png");
	putimage(0, 0, &Plot2_17);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_16, "..\\data\\Plot2_16.png");
	putimage(0, 0, &Plot2_16);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_15, "..\\data\\Plot2_15.png");
	putimage(0, 0, &Plot2_15);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_14, "..\\data\\Plot2_14.png");
	putimage(0, 0, &Plot2_14);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_13, "..\\data\\Plot2_13.png");
	putimage(0, 0, &Plot2_13);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_12, "..\\data\\Plot2_12.png");
	putimage(0, 0, &Plot2_12);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_11, "..\\data\\Plot2_11.png");
	putimage(0, 0, &Plot2_11);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_10, "..\\data\\Plot2_10.png");
	putimage(0, 0, &Plot2_10);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_9, "..\\data\\Plot2_9.png");
	putimage(0, 0, &Plot2_9);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_8, "..\\data\\Plot2_8.png");
	putimage(0, 0, &Plot2_8);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_7, "..\\data\\Plot2_7.png");
	putimage(0, 0, &Plot2_7);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_6, "..\\data\\Plot2_6.png");
	putimage(0, 0, &Plot2_6);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_5, "..\\data\\Plot2_5.png");
	putimage(0, 0, &Plot2_5);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_4, "..\\data\\Plot2_4.png");
	putimage(0, 0, &Plot2_4);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_3, "..\\data\\Plot2_3.png");
	putimage(0, 0, &Plot2_3);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_2, "..\\data\\Plot2_2.png");
	putimage(0, 0, &Plot2_2);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot2_1, "..\\data\\Plot2_1.png");
	putimage(0, 0, &Plot2_1);
	FlushBatchDraw();
	Sleep(100);
	
	loadimage(&black, "..\\data\\Black.jpeg");
	putimage(0, 0, &black);
	FlushBatchDraw();
	Sleep(500);

	mciSendString("close P2", NULL, 0, NULL);

	Sleep(1000);

	//PART THREE*************

	//������
	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	loadimage(&Plot3_1, "..\\data\\Plot3_1.png");
	putimage(0, 0, &Plot3_1);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_2, "..\\data\\Plot3_2.png");
	putimage(0, 0, &Plot3_2);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_3, "..\\data\\Plot3_3.png");
	putimage(0, 0, &Plot3_3);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_4, "..\\data\\Plot3_4.png");
	putimage(0, 0, &Plot3_4);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_5, "..\\data\\Plot3_5.png");
	putimage(0, 0, &Plot3_5);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_6, "..\\data\\Plot3_6.png");
	putimage(0, 0, &Plot3_6);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_7, "..\\data\\Plot3_7.png");
	putimage(0, 0, &Plot3_7);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_8, "..\\data\\Plot3_8.png");
	putimage(0, 0, &Plot3_8);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_9, "..\\data\\Plot3_9.png");
	putimage(0, 0, &Plot3_9);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_10, "..\\data\\Plot3_10.png");
	putimage(0, 0, &Plot3_10);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_11, "..\\data\\Plot3_11.png");
	putimage(0, 0, &Plot3_11);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_12, "..\\data\\Plot3_12.png");
	putimage(0, 0, &Plot3_12);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_13, "..\\data\\Plot3_13.png");
	putimage(0, 0, &Plot3_13);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_14, "..\\data\\Plot3_14.png");
	putimage(0, 0, &Plot3_14);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_15, "..\\data\\Plot3_15.png");
	putimage(0, 0, &Plot3_15);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_16, "..\\data\\Plot3_16.png");
	putimage(0, 0, &Plot3_16);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_17, "..\\data\\Plot3_17.png");
	putimage(0, 0, &Plot3_17);
	FlushBatchDraw();
	Sleep(100);

	//�ص�������
	mciSendString("close KeyB", NULL, 0, NULL);

	loadimage(&Plot3_18, "..\\data\\Plot3_18.png");
	putimage(0, 0, &Plot3_18);
	FlushBatchDraw();
	Sleep(400);
	loadimage(&Plot3_19, "..\\data\\Plot3_19.png");
	putimage(0, 0, &Plot3_19);
	FlushBatchDraw();
	Sleep(400);
	loadimage(&Plot3_20, "..\\data\\Plot3_20.png");
	putimage(0, 0, &Plot3_20);
	
	/*������*/
	mciSendString("open ..\\data\\DoorOpen.mp3 alias Door", NULL, 0, NULL);
	mciSendString("play Door", NULL, 0, NULL);

	FlushBatchDraw();
	Sleep(8000);

	loadimage(&Plot3_21, "..\\data\\Plot3_21.png");
	putimage(0, 0, &Plot3_21);
	FlushBatchDraw();
	//ս�裬��
	mciSendString("open ..\\data\\FIGHT.mp3 alias FIGHT", NULL, 0, NULL);
	mciSendString("play FIGHT repeat", NULL, 0, NULL);
	Sleep(300);

	loadimage(&Plot3_22, "..\\data\\Plot3_22.png");
	putimage(0, 0, &Plot3_22);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_23, "..\\data\\Plot3_23.png");
	putimage(0, 0, &Plot3_23);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_24, "..\\data\\Plot3_24.png");
	putimage(0, 0, &Plot3_24);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_25, "..\\data\\Plot3_25.png");
	putimage(0, 0, &Plot3_25);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_26, "..\\data\\Plot3_26.png");
	putimage(0, 0, &Plot3_26);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_27, "..\\data\\Plot3_27.png");
	putimage(0, 0, &Plot3_27);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_28, "..\\data\\Plot3_28.png");
	putimage(0, 0, &Plot3_28);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_29, "..\\data\\Plot3_29.png");
	putimage(0, 0, &Plot3_29);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_30, "..\\data\\Plot3_30.png");
	putimage(0, 0, &Plot3_30);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_31, "..\\data\\Plot3_31.png");
	putimage(0, 0, &Plot3_31);
	FlushBatchDraw();
	Sleep(1000);
	loadimage(&Plot3_32, "..\\data\\Plot3_32.png");
	putimage(0, 0, &Plot3_32);
	FlushBatchDraw();
	Sleep(1000);
	loadimage(&Plot3_33, "..\\data\\Plot3_33.png");
	putimage(0, 0, &Plot3_33);
	FlushBatchDraw();
	Sleep(1000);
	loadimage(&Plot3_34, "..\\data\\Plot3_34.png");
	putimage(0, 0, &Plot3_34);
	FlushBatchDraw();
	Sleep(1000);
	loadimage(&Plot3_35, "..\\data\\Plot3_35.png");
	putimage(0, 0, &Plot3_35);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_36, "..\\data\\Plot3_36.png");
	putimage(0, 0, &Plot3_36);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_37, "..\\data\\Plot3_37.png");
	putimage(0, 0, &Plot3_37);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_38, "..\\data\\Plot3_38.png");
	putimage(0, 0, &Plot3_38);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&Plot3_39, "..\\data\\Plot3_39.png");
	putimage(0, 0, &Plot3_39);
	FlushBatchDraw();
	Sleep(100);

	/*����*/
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();

	IsLeavePlot = 1;
}




/******************************************************************************************************************************/


//3.���û������޹صĸ���updateWithoutInput

//��Ļ
void ddanmu();

//WithoutInput��������
void updateWithoutInput()
{
	if ((IsLeaveMenu == 1) && (IsLeavePlot == 1))
	{
		//��Ļ
		ddanmu();

		//�ж������Ƿ�����
		if (hero.blood == 0) {
			mciSendString("open ..\\data\\Dead.mp3 alias D", NULL, 0, NULL);
			mciSendString("play D", NULL, 0, NULL);
			mciSendString("close FIGHT", NULL, 0, NULL);
			SelectEnd = 1;  //BE
			IsBreak = 1;  //out of loop
		}
		else if ((hero.blood > 0) && (monster.blood == 0))
		{
			mciSendString("close FIGHT", NULL, 0, NULL);
			mciSendString("open ..\\data\\Win.mp3 alias W", NULL, 0, NULL);
			mciSendString("play W", NULL, 0, NULL);
			SelectEnd = 0;  //BE
			IsBreak = 1;  //out of loop
		}
		//���ﵽ�߽�
		if (hero.position_x == Frame_x_Begin + 2 || hero.position_x < Frame_x_Begin + 2) hero.position_x = Frame_x_Begin + 2;
		if (hero.position_x == Frame_x_End - 21 || hero.position_x > Frame_x_End - 21) hero.position_x = Frame_x_End - 21;
		if (hero.position_y == Frame_y_Begin + 2 || hero.position_y < Frame_y_Begin + 2) hero.position_y = Frame_y_Begin + 2;
		if (hero.position_y == Frame_y_End - 21 || hero.position_y > Frame_y_End - 21) hero.position_y = Frame_y_End - 21;

		//����ʰȡ
		//Ѫƿ
		if (prop.Reach == 0 && abs(hero.position_x - prop.position_x) <= 20 && abs(hero.position_y - prop.position_y) <= 20)
		{
			prop.judge = 0;
			monster.blood--;
			prop.Reach = 1;
			prop.position_x = -100;
			prop.position_y = -100;

		}

		if (prop.Reach == 1)
		{
			_beginthread(timer1, 0, NULL);
			prop.Reach = 0;
		}

		if (hero.a == 1 && prop.judge == 0)
		{


			prop.position_x = rand() % (Frame_x_End - Frame_x_Begin - 60) + Frame_x_Begin + 30;
			prop.position_y = rand() % (Frame_y_End - Frame_y_Begin - 60) + Frame_y_Begin + 30;
			prop.judge = 1;


		}



		//����ƿ
		if (prop1.Reach == 0 && (abs(hero.position_x - prop1.position_x) <= 20 && abs(hero.position_y - prop1.position_y) <= 20))
		{
			hero.speed = 3;
			prop1.judge = 0;
			prop1.position_x = -100;
			prop1.position_y = -100;
			prop1.Reach = 1;

		}


		if (prop1.Reach == 1)
		{
			_beginthread(timer2, 0, NULL);
			_beginthread(timer3, 0, NULL);
			prop1.Reach = 0;
		}

		if (hero.b == 1 && prop1.judge == 0)

		{
			prop1.position_x = rand() % (Frame_x_End - Frame_x_Begin - 60) + Frame_x_Begin + 30;
			prop1.position_y = rand() % (Frame_y_End - Frame_y_Begin - 60) + Frame_y_Begin + 30;
			prop1.judge = 1;
		}


		if (hero.c == 1)
		{
			hero.speed = 1;
			hero.c = 0;
		}
		hero.a = 0;
		hero.b = 0;
		hero.c = 0;
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x1) <= 18 && abs(hero.position_y - dm.enemy_y1) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x2) <= 18 && abs(hero.position_y - dm.enemy_y2) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x3) <= 18 && abs(hero.position_y - dm.enemy_y3) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x4) <= 18 && abs(hero.position_y - dm.enemy_y4) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x5) <= 18 && abs(hero.position_y - dm.enemy_y5) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x6) <= 18 && abs(hero.position_y - dm.enemy_y6) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x11) <= 18 && abs(hero.position_y - dm.enemy_y11) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x12) <= 18 && abs(hero.position_y - dm.enemy_y12) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x13) <= 18 && abs(hero.position_y - dm.enemy_y13) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x14) <= 18 && abs(hero.position_y - dm.enemy_y14) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x15) <= 18 && abs(hero.position_y - dm.enemy_y15) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x16) <= 18 && abs(hero.position_y - dm.enemy_y16) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x21) <= 18 && abs(hero.position_y - dm.enemy_y21) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x22) <= 18 && abs(hero.position_y - dm.enemy_y22) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x23) <= 18 && abs(hero.position_y - dm.enemy_y23) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x24) <= 18 && abs(hero.position_y - dm.enemy_y24) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x25) <= 18 && abs(hero.position_y - dm.enemy_y25) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x26) <= 18 && abs(hero.position_y - dm.enemy_y26) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x31) <= 18 && abs(hero.position_y - dm.enemy_y31) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x32) <= 18 && abs(hero.position_y - dm.enemy_y32) <= 18))
		{
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x33) <= 18 && abs(hero.position_y - dm.enemy_y33) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x34) <= 18 && abs(hero.position_y - dm.enemy_y34) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x35) <= 18 && abs(hero.position_y - dm.enemy_y35) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
		if ((hero.IsZhuang == 0) && (abs(hero.position_x - dm.enemy_x36) <= 18 && abs(hero.position_y - dm.enemy_y36) <= 18)) {
			hero.blood--;
			hero.IsZhuang = 1;
			_beginthread(timer5, 0, NULL);
		}
	}
}



//������Ļ 
void ddanmu()
{
	if (dm.enemy_y1 > Frame_y_End && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x1 = Frame_x_Begin + rand() % (40);//���λ��ˢ��
		dm.enemy_y1 = Frame_y_Begin - 40;           //�����µĵ�Ļ 
	}
	if (dm.enemy_y1 == Frame_y_Begin + 24 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x2 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y2 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 50 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x3 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y3 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 75 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x21 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y21 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 24 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x23 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y23 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 75 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x31 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y31 = Frame_y_Begin - 40;

	}

	if (dm.enemy_y1 == Frame_y_Begin && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x11 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y11 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 24 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x12 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y12 = Frame_y_Begin - 40;


	}
	if (dm.enemy_y1 == Frame_y_Begin + 50 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x13 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y13 = Frame_y_Begin - 40;


	}
	if (dm.enemy_y1 == Frame_y_Begin + 75 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x22 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y22 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 90 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x33 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y33 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y1 == Frame_y_Begin + 75 && monster.blood != 3)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_x32 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y32 = Frame_y_Begin - 40;

	}
	//����


		if (dm.enemy_y4 < Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
		{
			dm.enemy_x4 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
			dm.enemy_y4 = Frame_y_End + 40;
		}
	if (dm.enemy_y4 == Frame_y_End - 24)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x5 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y5 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 50)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x6 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y6 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 75)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x24 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y24 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 50)   //��Ļ�ܳ���Ļ�����̼������� 
	{


		dm.enemy_x34 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y34 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 24)   //��Ļ�ܳ���Ļ�����̼������� 
	{


		dm.enemy_x35 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_Begin;//���λ��ˢ��
		dm.enemy_y35 = Frame_y_End + 40;
	}

	if (dm.enemy_y4 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x14 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y14 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 50)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x15 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y15 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 24)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x16 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y16 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 75)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x25 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y25 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 24)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x26 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y26 = Frame_y_End + 40;
	}
	if (dm.enemy_y4 == Frame_y_End - 72)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_x36 = rand() % (Frame_x_End / 2 - Frame_x_Begin / 2 - 20) + Frame_x_End / 2 + Frame_x_Begin / 2;//���λ��ˢ��
		dm.enemy_y36 = Frame_y_End + 40;
	}

	//��ֹ�غ�
	if (dm.enemy_y1 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y1 = Frame_y_Begin - 40;

	}
	if (dm.enemy_y2 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y2 = Frame_y_Begin - 800;

	}
	if (dm.enemy_y3 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y3 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y21 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y21 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y23 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y23 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y31 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y31 = Frame_y_Begin - 800;


	}


		if (dm.enemy_y11 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
		{

			dm.enemy_y11 = Frame_y_Begin - 800;


		}
	if (dm.enemy_y12 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼�������  
	{

		dm.enemy_y12 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y13 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y13 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y22 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼�������  
	{

		dm.enemy_y22 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y33 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y33 = Frame_y_Begin - 800;


	}
	if (dm.enemy_y32 == Frame_y_End)   //��Ļ�ܳ���Ļ�����̼������� 
	{

		dm.enemy_y32 = Frame_y_Begin - 800;


	}

	if (dm.enemy_y4 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y4 = Frame_y_End + 40;

	}
	if (dm.enemy_y5 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y5 = Frame_y_End + 800;

	}
	if (dm.enemy_y6 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y6 = Frame_y_End + 800;

	}
	if (dm.enemy_y14 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y14 = Frame_y_End + 800;

	}
	if (dm.enemy_y15 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y15 = Frame_y_End + 800;

	}
	if (dm.enemy_y16 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y16 = Frame_y_End + 800;

	}
	if (dm.enemy_y24 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y24 = Frame_y_End + 800;

	}
	if (dm.enemy_y25 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y25 = Frame_y_End + 800;

	}
	if (dm.enemy_y26 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y26 = Frame_y_End + 800;

	}
	if (dm.enemy_y34 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y34 = Frame_y_End + 800;

	}
	if (dm.enemy_y35 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y35 = Frame_y_End + 800;

	}
	if (dm.enemy_y36 == Frame_y_Begin)   //��Ļ�ܳ���Ļ�����̼������� 
	{
		dm.enemy_y36 = Frame_y_End + 800;

	}

	
		// �������Ƶл������ƶ����ٶȡ�ÿ������ѭ�������ƶ�һ�εл�
			// �����޸ĵĻ����û����������ٶȻ��Ǳ��ֺܿ죬������NPC���ƶ���ʾ���Խ���
		static int speed = 0;
	if (monster.blood == 5)
	{

		if (speed < 4)
			speed++;
		if (speed == 4)
		{
			dm.enemy_y1++;

			dm.enemy_y2++;

			dm.enemy_y3++;

			dm.enemy_y11++;

			dm.enemy_y12++;

			dm.enemy_y13++;

			dm.enemy_y21++;

			dm.enemy_y22++;

			dm.enemy_y23++;

			dm.enemy_y31++;

			dm.enemy_y32++;

			dm.enemy_y33++;

			speed = 0;
		}
	}

	else if (monster.blood == 4)
	{
		if (speed > 2)
		{
			speed = 0;
		}
		if (speed < 2)
			speed++;
		if (speed == 2)
		{
			dm.enemy_y1++;

			dm.enemy_y2++;

			dm.enemy_y3++;

			dm.enemy_y11++;

			dm.enemy_y12++;

			dm.enemy_y13++;

			dm.enemy_y21++;

			dm.enemy_y22++;

			dm.enemy_y23++;

			dm.enemy_y31++;

			dm.enemy_y32++;

			dm.enemy_y33++;

			speed = 0;
		}
	}


	else if (monster.blood == 3)
	{

		if (speed < 2)
			speed++;
		if (speed == 2)
		{

			dm.enemy_y1 = Frame_y_Begin - 40;

			dm.enemy_y2 = Frame_y_Begin - 800;

			dm.enemy_y3 = Frame_y_Begin - 800;

			dm.enemy_y11 = Frame_y_Begin - 800;

			dm.enemy_y12 = Frame_y_Begin - 800;

			dm.enemy_y13 = Frame_y_Begin - 800;

			dm.enemy_y21 = Frame_y_Begin - 800;

			dm.enemy_y22 = Frame_y_Begin - 800;

			dm.enemy_y23 = Frame_y_Begin - 800;

			dm.enemy_y31 = Frame_y_Begin - 800;

			dm.enemy_y32 = Frame_y_Begin - 800;

			dm.enemy_y33 = Frame_y_Begin - 800;

			dm.enemy_y4--;

			dm.enemy_y5--;

			dm.enemy_y6--;

			dm.enemy_y14--;

			dm.enemy_y15--;

			dm.enemy_y16--;

			dm.enemy_y24--;

			dm.enemy_y25--;

			speed = 0;
		}
	}

	else if (monster.blood == 2)
	{

		if (speed > 2)
		{
			speed = 0;
		}
		if (speed < 2)
			speed++;
		if (speed == 2)
		{
			dm.enemy_y1++;

			dm.enemy_y2++;

			dm.enemy_y3++;

			dm.enemy_y11++;

			dm.enemy_y12++;

			dm.enemy_y13++;

			dm.enemy_y21++;

			dm.enemy_y22++;

			dm.enemy_y23++;

			dm.enemy_y31++;

			dm.enemy_y32++;

			dm.enemy_y33++;

			dm.enemy_y4--;

			dm.enemy_y5--;

			dm.enemy_y6--;

			dm.enemy_y14--;

			dm.enemy_y15--;

			dm.enemy_y16--;

			dm.enemy_y24--;

			dm.enemy_y25--;

			speed = 0;
		}
	}


	else if (monster.blood == 1)
	{
		if (speed > 1)
		{
			speed = 0;
		}
		if (speed < 1)
			speed++;
		if (speed == 1)
		{
			dm.enemy_y1++;

			dm.enemy_y2++;

			dm.enemy_y3++;

			dm.enemy_y11++;

			dm.enemy_y12++;

			dm.enemy_y13++;

			dm.enemy_y21++;

			dm.enemy_y22++;

			dm.enemy_y23++;

			dm.enemy_y31++;

			dm.enemy_y32++;

			dm.enemy_y33++;

			dm.enemy_y4--;

			dm.enemy_y5--;

			dm.enemy_y6--;

			dm.enemy_y14--;

			dm.enemy_y15--;

			dm.enemy_y16--;

			dm.enemy_y24--;

			dm.enemy_y25--;

			dm.enemy_y26--;

			dm.enemy_y34--;

			dm.enemy_y35--;

			dm.enemy_y36--;

			speed = 0;
		}
	}
}



/******************************************************************************************************************************/


//4.���û������йصĸ���updateWithInput

void InputFile(const char* filename);  //�浵����
void ReadFile(const char* filename); //��������
void LoadFile(); //�ص�

//input��������
void updateWithInput()
{
	//1)Click����ʼ������ת
	if (IsLeaveMenu == 0)
	{
		while (MouseHit())
		{
			mouse = GetMouseMsg();
			if (mouse.uMsg == WM_LBUTTONDOWN) {
				setbkcolor(BLACK);
				cleardevice();
				IsLeaveMenu = 1;
				break;
			}
		}
	}

	if ((IsLeaveMenu == 1) && (IsLeavePlot==1))
	{
		//2)�浵����
		
			 if (GetAsyncKeyState(0x43) & 0x8000) {
				InputFile("..\\files\\file.dat");  //�浵
			}
			else if (GetAsyncKeyState(0x51) & 0x8000) {
				EndBatchDraw();
				closegraph(); 
				exit(0);//�˳���Ϸ
			}

			 //�����ƶ�
			 if (GetAsyncKeyState(0x57) & 0x8000) hero.position_y -= hero.speed;
			 if (GetAsyncKeyState(0x53) & 0x8000) hero.position_y += hero.speed;
			 if (GetAsyncKeyState(0x41) & 0x8000) hero.position_x -= hero.speed;
			 if (GetAsyncKeyState(0x44) & 0x8000) hero.position_x += hero.speed;
			
		}
	}


/******�ֺ�������******/
//����
void LoadFile()
{
	ReadFile("..\\files\\file.dat"); //����

	//���
	setbkcolor(BLACK);
	cleardevice();


	//monster
	if (monster.blood != monster.IsHit)//���
	{
		if ((monster.Hit >= 0) && (monster.Hit < 50))
		{
			loadimage(&beida1, "..\\data\\GAME\\beida1~1.bmp");
			putimage(450, 95, &beida1);
			monster.Hit++;
		}
		else if ((monster.Hit >= 50) && (monster.Hit < 100))
		{
			loadimage(&beida2, "..\\data\\GAME\\beida2~1.bmp");
			putimage(450, 95, &beida2);
			monster.Hit++;
		}
		if (monster.Hit == 100) {
			monster.IsHit--;
			monster.Hit = 0;
		}
	}

	else
	{

		if ((monster.i >= 0) && (monster.i < 50))
		{
			loadimage(&feichuan1, "..\\data\\GAME\\1.bmp");
			putimage(450, 95, &feichuan1);
			monster.i++;
			Sleep(1);
		}
		else if ((monster.i >= 50) && (monster.i < 100))
		{
			loadimage(&feichuan2, "..\\data\\GAME\\2.bmp");
			putimage(450, 95, &feichuan2);
			monster.i++;
			Sleep(1);
		}
		else if ((monster.i >= 100) && (monster.i < 150))
		{
			loadimage(&feichuan3, "..\\data\\GAME\\3.bmp");
			putimage(450, 95, &feichuan3);
			monster.i++;
			Sleep(1);
		}
		else if ((monster.i >= 150) && (monster.i < 200))
		{
			loadimage(&feichuan4, "..\\data\\GAME\\4.bmp");
			putimage(450, 95, &feichuan4);
			monster.i++;
			Sleep(1);
		}
		else if ((monster.i >= 200) && (monster.i < 250))
		{
			loadimage(&feichuan5, "..\\data\\GAME\\5.bmp");
			putimage(450, 95, &feichuan5);
			Sleep(1);
			monster.i++;
			if (monster.i == 250) monster.i = 0;
		}
	}

	//���ع���Ѫ��
	if (monster.blood >= 5)//count:Ѫ������
	{
		loadimage(&xuetiao1, "..\\data\\GAME\\xuetiao\\0.1xue.bmp");
		putimage(440, 15, &xuetiao1);//���Ѫ��Ѫ��
	}
	if (monster.blood == 4)
	{
		loadimage(&xuetiao2, "..\\data\\GAME\\xuetiao\\1.1xue.bmp");
		putimage(440, 15, &xuetiao2);//�ĵ�Ѫ��Ѫ��

	}
	if (monster.blood == 3)
	{
		loadimage(&xuetiao3, "..\\data\\GAME\\xuetiao\\2.1xue.bmp");
		putimage(440, 15, &xuetiao3);//����

	}
	if (monster.blood == 2)
	{
		loadimage(&xuetiao4, "..\\data\\GAME\\xuetiao\\3.1xue.bmp");
		putimage(440, 15, &xuetiao4);//����

	}
	if (monster.blood == 1)
	{
		loadimage(&xuetiao5, "..\\data\\GAME\\xuetiao\\4.1xue.bmp");
		putimage(440, 15, &xuetiao5);//һ��
	}



	//������Ϸ���
	LoadGamingFrame();

	//�������Ǽ���Ѫ��
	loadimage(&img_hero, "..\\data\\hero.PNG");
	putimage(hero.position_x, hero.position_y, &img_hero);

	if (hero.blood >= 3)
	{
		loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero1.bmp");
		putimage(500, 670 , &img_HeroBlood);
	}
	else if (hero.blood == 2)
	{
		loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero2.bmp");
		putimage(500, 670, &img_HeroBlood);
	}
	else if (hero.blood == 1)
	{
		loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero3.bmp");
		putimage(500, 670, &img_HeroBlood);
	}
	else if (hero.blood == 0)
	{
		loadimage(&img_HeroBlood, "..\\data\\HeroBlood\\hero4.bmp");
		putimage(500, 670, &img_HeroBlood);
		Sleep(500);
	}


	

	//���ص���
	loadimage(&img_red, "..\\data\\redpotion.png");
	loadimage(&img_blue, "..\\data\\bluepotion.png");
	_beginthread(timer4, 0, NULL);

	if (hero.d == 1)
	{
		if (prop.judge == 1)
			putimage(prop.position_x, prop.position_y, &img_red);
		if (prop1.judge == 1)
			putimage(prop1.position_x, prop1.position_y, &img_blue);
	}

	

	//���ص�Ļλ��
	dshow();


	FlushBatchDraw();
}


//*�浵����������װ
void InputFile(const char* filename)  //�浵����
{
	FILE* fpin;
	err = fopen_s(&fpin, filename, "wb+");
	if (err== 0) 
	{
		fseek(fpin, 0, SEEK_SET); //���뿪ʼ��
		fwrite(&hero, sizeof(HERO), 1, fpin); //������������
		fwrite(&monster, sizeof(MONSTER), 1, fpin); //�����������
		fwrite(&dm, sizeof(DM), 1, fpin); //���뵯Ļ����
		fwrite(&prop, sizeof(PROP), 1, fpin); //�����Ѫ��������
		fwrite(&prop1, sizeof(PROP), 1, fpin); //������ٵ�������
		fclose(fpin);
		settextcolor(WHITE);
		outtextxy(0, 360, "Successfully Save File!"); //�浵�ɹ�
		FlushBatchDraw();
		Sleep(1000);
		outtextxy(0, 360, "                                                 ");
		FlushBatchDraw();
		
	}
	else if (err != 0) {
		char errmsg[100];
		strerror_s(errmsg, 100 * sizeof(char), err);
		settextcolor(WHITE);
		outtextxy(0, 360,errmsg); //��������
		FlushBatchDraw();
		Sleep(1000);
		outtextxy(0, 360, "                                                    ");
		FlushBatchDraw();
	}

}
void ReadFile(const char* filename) //��������
{
	FILE* fpread;
	err = fopen_s(&fpread, filename, "rb+");
	if (err==0)
	{
		fseek(fpread, 0, SEEK_SET); //���뿪ʼ��
		fread(&hero, sizeof(hero), 1, fpread); //������������
		hero.a = 0;
		hero.b = 0;
		hero.c = 1;
		
		fread(&monster, sizeof(MONSTER), 1, fpread); //������������
		fread(&dm, sizeof(DM), 1, fpread); //������Ļ����
		fread(&prop, sizeof(PROP), 1, fpread); //������Ѫ��������
		prop.Reach = 0;
		
		if ((prop.judge == 0)&&(hero.d == 1))
		{
			prop.position_x = -100;
			prop.position_y = -100;
			prop.Reach = 1;
		} 
		else if (hero.d == 0) {
			
			prop.judge = 1;
			IsLoadD = 1;
			_beginthread(timer8, 0, NULL);
			
		}

		fread(&prop1, sizeof(PROP), 1, fpread); //�������ٵ�������
		prop1.Reach = 0;
		if ((prop1.judge == 0) && (hero.d == 1))
		{	
			prop1.position_x = -100;
			prop1.position_y = -100;
			prop1.Reach = 1;
		}
		else if (hero.d == 0) {
			
			prop1.judge = 1;
			IsLoadD = 1;
			_beginthread(timer9, 0, NULL);
		}
		fclose(fpread);
		settextcolor(WHITE);
		outtextxy(0, 360, "Successfully Load File!"); //�����ɹ�
		FlushBatchDraw();
		Sleep(1000);
		outtextxy(0, 360, "                                                 ");
		FlushBatchDraw();
	}
	else if (err != 0) {
		char errmsg[100];
		strerror_s(errmsg, 100 * sizeof(char), err);
		settextcolor(WHITE);
		outtextxy(0, 360, errmsg); //��������
		FlushBatchDraw();
		Sleep(1000);
		outtextxy(0, 360, "                                                    ");
		FlushBatchDraw();
	}
}


/******************************************************************************************************************************/



//5.��Ϸ����gameover

//�رջ���
void CloseFrame()
{
	int Print_x = Frame_x_Begin;
	int Print_y = Frame_y_Begin;
	int Print_v = 1;
	int Print_xn = Print_x + Print_v;
	int Print_yn = Print_y + Print_v;
	int xa = Frame_x_Begin - 1;
	int xb = Frame_x_Begin + 1;
	int ya = Frame_y_Begin - 1;
	int yb = Frame_y_Begin + 1;
	int xc = Frame_x_End - 1;
	int xd = Frame_x_End + 1;
	int yc = Frame_y_End - 1;
	int yd = Frame_y_End + 1;

	while ((Print_xn <= Frame_x_End)) //��ӡ������
	{
		setcolor(BLACK);    //������ɫRGB
		line(Print_x, ya, Print_xn, ya);
		line(Print_x, Frame_y_Begin, Print_xn, Frame_y_Begin);       //����
		line(Print_x, yb, Print_xn, yb);       //����
		line(Print_x, yc, Print_xn, yc);
		line(Print_x, Frame_y_End, Print_xn, Frame_y_End);       //����
		line(Print_x, yd, Print_xn, yd);       //����

		FlushBatchDraw();
		Sleep(5);

		Print_x = Print_xn;
		Print_xn += Print_v;
	}

	while ((Print_yn <= Frame_y_End)) //��ӡ������
	{
		setcolor(BLACK);    //������ɫRGB(��,��,��)
		line(xa, Print_y, xa, Print_yn);
		line(Frame_x_Begin, Print_y, Frame_x_Begin, Print_yn);
		line(xb, Print_y, xb, Print_yn);
		line(xc, Print_y, xc, Print_yn);
		line(Frame_x_End, Print_y, Frame_x_End, Print_yn);
		line(xd, Print_y, xd, Print_yn);

		FlushBatchDraw();
		Sleep(5);

		Print_y = Print_yn;
		Print_yn += Print_v;
	}
	IsLoadGamingFrame = 1; //ֻ��ӡһ��
}

//���ѡ��
void GoodEnd()
{
	mciSendString("open ..\\data\\Bomm.mp3 alias B", NULL, 0, NULL);
	mciSendString("play B", NULL, 0, NULL);

	//���ﱬը
	loadimage(&image_baozha1, "..\\data\\GAME\\baozha1.bmp");
	putimage(350, 0, &image_baozha1);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha2, "..\\data\\GAME\\baozha2.bmp");
	putimage(350, 0, &image_baozha2);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha3, "..\\data\\GAME\\baozha3.bmp");
	putimage(350, 0, &image_baozha3);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha4, "..\\data\\GAME\\baozha4.bmp");
	putimage(350, 0, &image_baozha4);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha5, "..\\data\\GAME\\baozha5.bmp");
	putimage(350, 0, &image_baozha5);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha6, "..\\data\\GAME\\baozha6.bmp");
	putimage(350, 0, &image_baozha6);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha7, "..\\data\\GAME\\baozha7.bmp");
	putimage(350, 0, &image_baozha7);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha8, "..\\data\\GAME\\baozha8.bmp");
	putimage(350, 0, &image_baozha8);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha9, "..\\data\\GAME\\baozha9.bmp");
	putimage(350, 0, &image_baozha9);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha10, "..\\data\\GAME\\baozha10.bmp");
	putimage(350, 0, &image_baozha10);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha11, "..\\data\\GAME\\baozha11.bmp");
	putimage(350, 0, &image_baozha11);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha12, "..\\data\\GAME\\baozha12.bmp");
	putimage(350, 0, &image_baozha12);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha13, "..\\data\\GAME\\baozha13.bmp");
	putimage(350, 0, &image_baozha13);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha14, "..\\data\\GAME\\baozha14.bmp");
	putimage(350, 0, &image_baozha14);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha15, "..\\data\\GAME\\baozha15.bmp");
	putimage(350, 0, &image_baozha15);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha16, "..\\data\\GAME\\baozha16.bmp");
	putimage(350, 0, &image_baozha16);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha17, "..\\data\\GAME\\baozha17.bmp");
	putimage(350, 0, &image_baozha17);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha18, "..\\data\\GAME\\baozha18.bmp");
	putimage(350, 0, &image_baozha18);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha19, "..\\data\\GAME\\baozha19.bmp");
	putimage(350, 0, &image_baozha19);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha20, "..\\data\\GAME\\baozha20.bmp");
	putimage(350, 0, &image_baozha20);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha21, "..\\data\\GAME\\baozha21.bmp");
	putimage(350, 0, &image_baozha21);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha22, "..\\data\\GAME\\baozha22.bmp");
	putimage(350, 0, &image_baozha22);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha23, "..\\data\\GAME\\baozha23.bmp");
	putimage(350, 0, &image_baozha23);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha24, "..\\data\\GAME\\baozha24.bmp");
	putimage(350, 0, &image_baozha24);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha25, "..\\data\\GAME\\baozha25.bmp");
	putimage(350, 0, &image_baozha25);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha26, "..\\data\\GAME\\baozha26.bmp");
	putimage(350, 0, &image_baozha26);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha27, "..\\data\\GAME\\baozha27.bmp");
	putimage(350, 0, &image_baozha27);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha28, "..\\data\\GAME\\baozha28.bmp");
	putimage(350, 0, &image_baozha28);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha29, "..\\data\\GAME\\baozha29.bmp");
	putimage(350, 0, &image_baozha29);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha30, "..\\data\\GAME\\baozha30.bmp");
	putimage(350, 0, &image_baozha30);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha31, "..\\data\\GAME\\baozha31.bmp");
	putimage(350, 0, &image_baozha31);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha32, "..\\data\\GAME\\baozha32.bmp");
	putimage(350, 0, &image_baozha32);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha33, "..\\data\\GAME\\baozha33.bmp");
	putimage(350, 0, &image_baozha33);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha34, "..\\data\\GAME\\baozha34.bmp");
	putimage(350, 0, &image_baozha34);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha35, "..\\data\\GAME\\baozha35.bmp");
	putimage(350, 0, &image_baozha35);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha36, "..\\data\\GAME\\baozha36.bmp");
	putimage(350, 0, &image_baozha36);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha37, "..\\data\\GAME\\baozha37.bmp");
	putimage(350, 0, &image_baozha37);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha38, "..\\data\\GAME\\baozha38.bmp");
	putimage(350, 0, &image_baozha38);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha39, "..\\data\\GAME\\baozha39.bmp");
	putimage(350, 0, &image_baozha39);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha40, "..\\data\\GAME\\baozha40.bmp");
	putimage(350, 0, &image_baozha40);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha41, "..\\data\\GAME\\baozha41.bmp");
	putimage(350, 0, &image_baozha41);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha42, "..\\data\\GAME\\baozha42.bmp");
	putimage(350, 0, &image_baozha42);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha43, "..\\data\\GAME\\baozha43.bmp");
	putimage(350, 0, &image_baozha43);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha44, "..\\data\\GAME\\baozha44.bmp");
	putimage(350, 0, &image_baozha44);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha45, "..\\data\\GAME\\baozha45.bmp");
	putimage(350, 0, &image_baozha45);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha46, "..\\data\\GAME\\baozha46.bmp");
	putimage(350, 0, &image_baozha46);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha47, "..\\data\\GAME\\baozha47.bmp");
	putimage(350, 0, &image_baozha47);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha48, "..\\data\\GAME\\baozha48.bmp");
	putimage(350, 0, &image_baozha48);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha49, "..\\data\\GAME\\baozha49.bmp");
	putimage(350, 0, &image_baozha49);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha50, "..\\data\\GAME\\baozha50.bmp");
	putimage(350, 0, &image_baozha50);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha51, "..\\data\\GAME\\baozha51.bmp");
	putimage(350, 0, &image_baozha51);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha52, "..\\data\\GAME\\baozha52.bmp");
	putimage(350, 0, &image_baozha52);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha53, "..\\data\\GAME\\baozha53.bmp");
	putimage(350, 0, &image_baozha53);
	FlushBatchDraw();
	Sleep(50);
	loadimage(&image_baozha54, "..\\data\\GAME\\baozha54.bmp");
	putimage(350, 0, &image_baozha54);
	FlushBatchDraw();
	Sleep(50);


	mciSendString("close W", NULL, 0, NULL);

	//GE
	mciSendString("open ..\\data\\GoodEnd.mp3 alias GE", NULL, 0, NULL);
	mciSendString("play GE repeat", NULL, 0, NULL);

	//������
	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd1.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd2.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd3.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd4.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd5.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd6.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd7.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd8.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd9.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd10.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd11.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd12.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd13.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	mciSendString("close KeyB", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd14.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(700);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd15.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(700);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd16.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(2000);

	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd17.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd18.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd19.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd20.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd21.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd22.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd23.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd24.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd25.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd26.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd27.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd28.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd29.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd30.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd31.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd32.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd33.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd34.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd35.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd36.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd37.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd38.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd39.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd40.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd41.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd42.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	mciSendString("close KeyB", NULL, 0, NULL);
	mciSendString("open ..\\data\\GE_Type.mp3 alias GT", NULL, 0, NULL);
	mciSendString("play GT repeat", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd43.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd44.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd45.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd46.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd47.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd48.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd49.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd50.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd51.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd52.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(200);

	mciSendString("close GT", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd52.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(1500);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd53.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd54.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd55.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd56.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd57.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd58.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd59.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd60.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd61.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd62.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);
	
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd63.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd64.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd65.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd66.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd67.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd68.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd69.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd70.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd71.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd72.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd73.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd74.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd75.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd76.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd77.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd78.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd79.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd80.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd81.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd82.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd83.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd84.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd85.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd86.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd87.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd88.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd89.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd90.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd91.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd92.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd93.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd94.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd95.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd96.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd97.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd98.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd99.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd100.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd101.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd102.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd103.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	mciSendString("close KeyB", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd104.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(700);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd105.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(700);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd106.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(1500);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd107.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd108.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd109.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd110.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd111.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd112.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd113.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd114.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd115.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd116.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(1000);

	//

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd117.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd118.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd119.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd120.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd121.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd122.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd123.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd124.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd125.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd126.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(2000);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd125.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd124.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd123.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd122.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd121.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd120.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd119.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd118.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd117.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd116.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd127.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd128.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd129.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd130.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd131.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd132.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd133.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd134.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd135.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd136.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(4000);


	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd135.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd134.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd133.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd132.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd131.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd130.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd129.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);

	mciSendString("open ..\\data\\Fall.mp3 alias Fall", NULL, 0, NULL);
	mciSendString("play Fall", NULL, 0, NULL);

	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd128.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(150);
	loadimage(&END, "..\\data\\GoodEnd\\GoodEnd127.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(15000);

	mciSendString("close GoodEnd", NULL, 0, NULL);

}

void BadEnd()
{
	//BE
	mciSendString("open ..\\data\\BadEnd.mp3 alias BE", NULL, 0, NULL);
	mciSendString("play BE repeat", NULL, 0, NULL);

	//������
	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	loadimage(&END, "..\\data\\BadEnd\\BadEnd1.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd2.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd3.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd4.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd5.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd6.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	mciSendString("close KeyB", NULL, 0, NULL);
	mciSendString("open ..\\data\\Keyboard.mp3 alias KeyB", NULL, 0, NULL);
	mciSendString("play KeyB repeat", NULL, 0, NULL);

	loadimage(&END, "..\\data\\BadEnd\\BadEnd7.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(250);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd8.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(250);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd9.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(250);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd10.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd11.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd12.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd13.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd14.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd15.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd16.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd17.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd18.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd19.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd20.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd21.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd22.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd23.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd24.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd25.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd26.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd27.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd28.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd29.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd30.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd31.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd32.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd33.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd34.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);

	mciSendString("close KeyB", NULL, 0, NULL);

	loadimage(&END, "..\\data\\BadEnd\\BadEnd35.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(700);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd36.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(700);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd37.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(1500);

	loadimage(&END, "..\\data\\BadEnd\\BadEnd38.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd39.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd40.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd41.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd42.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd43.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd44.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd45.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd46.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd47.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(100);



	loadimage(&END, "..\\data\\BadEnd\\BadEnd48.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd49.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd50.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd51.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd52.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd53.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(2000);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd54.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd55.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd56.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd57.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);
	loadimage(&END, "..\\data\\BadEnd\\BadEnd58.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(500);

	loadimage(&END, "..\\data\\BadEnd\\BadEnd47.png");
	putimage(0, 0, &END);
	FlushBatchDraw();
	Sleep(1000);

	//UNDERDEVIL!!!!!!!
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(250, 200, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(251, 201, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(253, 201, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(252, 202, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(252, 201, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(252, 202, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(251, 200, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(247, 201, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(248, 199, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(247, 198, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(253, 197, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(246, 200, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(251, 198, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(248, 203, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);
	loadimage(&img_MenuTitle, "..\\data\\MenuTitle.png");
	putimage(252, 198, &img_MenuTitle);
	FlushBatchDraw();
	Sleep(200);

	loadimage(&img_MenuTitleG1, "..\\data\\MenuTitleG1.png");
	putimage(400, 60, &img_MenuTitleG1);
	FlushBatchDraw();
	Sleep(1500);

	loadimage(&img_MenuTitleO1, "..\\data\\MenuTitleO1.png");
	putimage(0, 500, &img_MenuTitleO1);
	FlushBatchDraw();
	Sleep(400);

	loadimage(&img_MenuTitleB1, "..\\data\\MenuTitleB1.png");
	putimage(650, 600, &img_MenuTitleB1);
	FlushBatchDraw();
	Sleep(400);

	loadimage(&img_MenuTitleG3, "..\\data\\MenuTitleG3.png");
	putimage(500, 350, &img_MenuTitleG3);
	FlushBatchDraw();
	Sleep(350);

	loadimage(&img_MenuTitleO2, "..\\data\\MenuTitleO2.png");
	putimage(150, 80, &img_MenuTitleO2);
	FlushBatchDraw();
	Sleep(350);

	loadimage(&img_MenuTitleB4, "..\\data\\MenuTitleB4.png");
	putimage(260, 342, &img_MenuTitleB4);
	FlushBatchDraw();
	Sleep(350);

	loadimage(&img_MenuTitleG2, "..\\data\\MenuTitleG2.png");
	putimage(523, 120, &img_MenuTitleG3);
	FlushBatchDraw();
	Sleep(250);

	loadimage(&img_MenuTitleO4, "..\\data\\MenuTitleO4.png");
	putimage(486, 580, &img_MenuTitleO4);
	FlushBatchDraw();
	Sleep(250);

	loadimage(&img_MenuTitleB3, "..\\data\\MenuTitleB3.png");
	putimage(0, 50, &img_MenuTitleB3);
	FlushBatchDraw();
	Sleep(150);

	loadimage(&img_MenuTitleG4, "..\\data\\MenuTitleG4.png");
	putimage(290, 430, &img_MenuTitleG4);
	FlushBatchDraw();
	Sleep(150);

	loadimage(&img_MenuTitleO5, "..\\data\\MenuTitleO5.png");
	putimage(10, 160, &img_MenuTitleO5);
	FlushBatchDraw();
	Sleep(150);

	loadimage(&img_MenuTitleB2, "..\\data\\MenuTitleB2.png");
	putimage(650, 100, &img_MenuTitleB2);
	FlushBatchDraw();
	Sleep(3500);


	mciSendString("close BE", NULL, 0, NULL);
}

void gameover()
{

	

	//�ر����ǻ���
	CloseFrame();

	//ѡ����
	if (SelectEnd == 0)
	{
		GoodEnd();
	}
	else BadEnd();

	//������������
	EndBatchDraw();

	//�˳���Ϸ
	closegraph();

}


/******************************************************************************************************************************/
/******************************************************************************************************************************/



//�������� 
int main()
{
	startup(); //��ʼ��

	while (1)
	{
		
		show();  //��ʾ����

		updateWithoutInput();  // ���û������޹صĸ���

		updateWithInput();  // ���û������йصĸ���

		if (IsBreak == 1) break;

		cleardevice();
	}
	gameover();  //��Ϸ����

	return 0;
}


