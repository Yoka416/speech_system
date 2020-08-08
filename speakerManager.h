#pragma once
#include<iostream>
using namespace std;
#include"speaker.h"
#include<vector>
#include<map>

class speakerManager
{
public:
	//四个容器
	vector<int>v1;
	vector<int>v2;
	vector<int>victory;
	map<int,speaker>m_speaker;
	speakerManager();

	//比赛轮数
	int index;
	
	void init();
	void showMeu();
	void createSpeaker();
	void Exit();
	void startSpeech();//开始比赛及流程
	void speechDraw();//抽签
	void speechcontent();//得出分数并导入
	void ShowScore();//显示分数
	void SaveRecord();//保存到文件中
	void load_Record();//读取文件记录
	void ShowRecord();//显示往届记录
	void clearRecord();//清空文件
	bool fileIsempty;
	map<int,vector<string>>m_Record;//用来存放往届记录的容器

	~speakerManager();
	

};
