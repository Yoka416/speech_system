#include<iostream>
using namespace std;
#include<string>
#include"speakerManager.h"
#include"speaker.h"
#include<ctime>

int main ()
{
	srand((unsigned int)time(NULL));//!不要把time和null的顺序写错了!
	speakerManager sp;
	
	/*for(map<int,speaker>::iterator it=sp.m_speaker.begin();it!=sp.m_speaker.end();it++)
	{
		cout<<"选手编号："<<it->first<<"  "<<"选手姓名："<<it->second.name<<"   "<<"选手分数"<<it->second.score[1]<<endl;;
	}*/
	
	int choice =0;


	while(true)
	{
		sp.showMeu();
		cout<<"请输入您的选择：";
		cin>>choice;


		switch(choice)
		{
		case 1://开始比赛
			sp.startSpeech();
			break;
		case 2://查看比赛记录
			sp.ShowRecord();
			break;
		case 3://清空比赛记录
			sp.clearRecord();
			break;
		case 0:
			sp.Exit();
			break;
		default:
			system("cls");
			break;
		}
	
	}
	

	system("pause");
	return 0;
}