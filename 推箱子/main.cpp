#include<iostream>
#include<Windows.h>
#include<graphics.h>
#include<string>
#include<conio.h>
#include"box_man.h"

using namespace std;

IMAGE image[ALL];

int map[][COL]={
	{WALL,0,0,0,0,0,0,0,0,0,0,0},  //ֱ����ö��Ԫ�ش���int���͵�ֵ�������,����˵��ö��Ԫ�صײ��ǳ�����
	{0,1,0,1,1,1,1,1,1,1,0,0},
	{0,1,4,1,0,2,1,0,2,1,0,0},
	{0,1,0,1,0,1,0,0,1,1,1,0},
	{0,1,0,2,0,1,1,4,1,1,1,0},
	{0,1,1,1,0,3,1,1,1,4,1,0},
	{0,1,2,1,1,4,1,1,1,1,1,0},
	{0,1,0,0,1,0,1,1,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0}
};

void gameFail(IMAGE *bg){
	putimage(0,0,bg);
	settextcolor(RED);
	RECT rectangle={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	settextstyle(40,0,_T("΢���ź�"));
	drawtext(_T("��������,��Ϸʧ��"),&rectangle,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

void gameOver(IMAGE *bg){
	putimage(0,0,bg);
	putimage(440,304,&image[MAN]);
	settextcolor(WHITE);
	RECT rec={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	settextstyle(20,0,_T("΢���ź�"));
	drawtext(_T("��ϲ��,���Ϊ��һ���ϸ�İ����ӵ���˾��!"),&rec,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

bool isGameOver(){
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			if(map[i][j]==BOX_DES){
				return false;
			}
		}
	}
	return  true;
}

void changeMap(struct _POS *pos,PROPS prop){
	map[pos->x][pos->y]=prop;
	putimage(START_X + pos->y * RATIO,START_Y + pos->x * RATIO,&image[prop]);
}

void gameControl(DIRECTION direct){  //direct ��ǰ������
	struct _POS next_pos=man;
	struct _POS next_next_pos=man;

	switch(direct){
		case UP:
			next_pos.x--;
			next_next_pos.x-=2;
			break;
		case DOWN:
			next_pos.x++;
			next_next_pos.x+=2;
			break;
		case LEFT:
			next_pos.y--;
			next_next_pos.y-=2;
			break;
		case RIGHT:
			next_pos.y++;
			next_next_pos.y+=2;
			break;
	}
	
	if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==FLOOR){
		if(isDes(man,des)){
			changeMap(&next_pos,MAN);
			changeMap(&man,BOX_DES);
			man=next_pos;
		}else{
			changeMap(&next_pos,MAN);
			changeMap(&man,FLOOR);
			man=next_pos;
		}
	}else if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==BOX){
		if(isValid(next_next_pos)&&map[next_next_pos.x][next_next_pos.y]==FLOOR){
			if(isDes(man,des)){
				changeMap(&next_next_pos,BOX);
				changeMap(&next_pos,MAN);
				changeMap(&man,BOX_DES);
				man=next_pos;
			}else{
				changeMap(&next_next_pos,BOX);
				changeMap(&next_pos,MAN);
				changeMap(&man,FLOOR);
				man=next_pos;
			}
		}else if(isValid(next_next_pos)&&map[next_next_pos.x][next_next_pos.y]==BOX_DES){
			changeMap(&next_next_pos,BOX);  //��HIT�ĳ�BOX,��ʵ��С�˿��԰��Ѿ�����Ŀ�ĵص���������
			changeMap(&next_pos,MAN);
			changeMap(&man,FLOOR);
			man=next_pos;
		}
	}else if(isValid(next_pos)&&map[next_pos.x][next_pos.y]==BOX_DES){
		changeMap(&next_pos,MAN);
		changeMap(&man,FLOOR);
		man=next_pos;
	}
}

int main(){
	/*ǽ:0 �ذ�:1 ����Ŀ�ĵ�:2  С��:3 ����:4 ���ӵ���Ŀ�ĵ�:5*/
	IMAGE bg_img;
	initgraph(WIDTH,HEIGHT);
	loadimage(&bg_img,_T("blackground.bmp"),WIDTH,HEIGHT,true);
	putimage(0,0,&bg_img);

	loadimage(&image[0],_T("wall.bmp"),RATIO,RATIO,true);
	loadimage(&image[1],_T("floor.bmp"),RATIO,RATIO,true);
	loadimage(&image[2],_T("des.bmp"),RATIO,RATIO,true);
	loadimage(&image[3],_T("man.bmp"),RATIO,RATIO,true);
	loadimage(&image[4],_T("box.bmp"),RATIO,RATIO,true);
	loadimage(&image[5],_T("box.bmp"),RATIO,RATIO,true);  //ע�ʹ���ȡ��HIT(�����Ƶ�Ŀ�ĵ�),ʵ��С�˿��԰��Ѿ�����Ŀ�ĵص���������

	int tmp=0;
	for(int i=0;i<ROW;i++){
		for(int j=0;j<COL;j++){
			putimage(START_X+j*RATIO,START_Y+i*RATIO,&image[map[i][j]]);
			if(map[i][j]==MAN){  //MAN����3
				man.x=i;
				man.y=j;
			}
			if(map[i][j]==BOX_DES){
				des.x[tmp]=i;
				des.y[tmp]=j;
				tmp++;
			}
		}
		cout<<endl;
	}

	int time=0;
	bool quit=false;
	do{
		if(_kbhit()){  //keyboard:����
			char ch=getch();
			if(ch==KEY_UP){
				gameControl(UP);
			}else if(ch==KEY_DOWN){
				gameControl(DOWN);
			}else if(ch==KEY_LEFT){
				gameControl(LEFT);
			}else if(ch==KEY_RIGHT){
				gameControl(RIGHT);
			}else if(ch==KEY_QUIT){
				quit=true;
			}
			if(isGameOver()){
				gameOver(&bg_img);
				quit=true;
			}
			time++;
			if(time>STEP){
				gameFail(&bg_img);
				quit=true;
			}
		}
		Sleep(100);
	}while(!quit);

	system("pause");
	closegraph();
	return 0;
}