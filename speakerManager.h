#pragma once
#include<iostream>
using namespace std;
#include"speaker.h"
#include<vector>
#include<map>

class speakerManager
{
public:
	//�ĸ�����
	vector<int>v1;
	vector<int>v2;
	vector<int>victory;
	map<int,speaker>m_speaker;
	speakerManager();

	//��������
	int index;
	
	void init();
	void showMeu();
	void createSpeaker();
	void Exit();
	void startSpeech();//��ʼ����������
	void speechDraw();//��ǩ
	void speechcontent();//�ó�����������
	void ShowScore();//��ʾ����
	void SaveRecord();//���浽�ļ���
	void load_Record();//��ȡ�ļ���¼
	void ShowRecord();//��ʾ�����¼
	void clearRecord();//����ļ�
	bool fileIsempty;
	map<int,vector<string>>m_Record;//������������¼������

	~speakerManager();
	

};
