#include<iostream>
using namespace std;
#include<string>
#include"speakerManager.h"
#include"speaker.h"
#include<ctime>

int main ()
{
	srand((unsigned int)time(NULL));//!��Ҫ��time��null��˳��д����!
	speakerManager sp;
	
	/*for(map<int,speaker>::iterator it=sp.m_speaker.begin();it!=sp.m_speaker.end();it++)
	{
		cout<<"ѡ�ֱ�ţ�"<<it->first<<"  "<<"ѡ��������"<<it->second.name<<"   "<<"ѡ�ַ���"<<it->second.score[1]<<endl;;
	}*/
	
	int choice =0;


	while(true)
	{
		sp.showMeu();
		cout<<"����������ѡ��";
		cin>>choice;


		switch(choice)
		{
		case 1://��ʼ����
			sp.startSpeech();
			break;
		case 2://�鿴������¼
			sp.ShowRecord();
			break;
		case 3://��ձ�����¼
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