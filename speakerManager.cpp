#include "speakerManager.h"
#include"speaker.h"
#include<string>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<vector>

 speakerManager::speakerManager()//构造函数
{
	//初始化容器
	this->init();
	//创建选手
	this->createSpeaker();
	//保存到文档中，加载往届记录
	this->load_Record();//傻逼行为，竟然把函数放到这!!竟然真的放在这里!
 }

 void speakerManager::init()
 {
	 this->v1.clear();//这里初始化学习一下
	 this->v2.clear();
	 this->victory.clear();
	 this->m_speaker.clear();
	 this->m_Record.clear();
	 this->index=1;
 }


 void speakerManager::createSpeaker()
 {
	 string nameseed="ABCDEFGHIJKI";
	
	 for(int i=0;i <(int)nameseed.size();i++)//!注意不是name.size()!
		{
			 string name = "选手";
			 speaker sp;
			name+=nameseed[i];
			sp.name = name;

			for(int j=0;j<2;j++)//每一位选手都有两个分数
		{
			sp.score[j]=0;
		}

			this->v1.push_back(i+10001);
			this->m_speaker.insert(make_pair(i+10001,sp));
		}
 }


 void speakerManager::startSpeech()//比赛流程总框架
 {
	 //抽签
	 this->speechDraw();

	//比赛
	 this->speechcontent();

	 //显示晋级选手信息
	 this->ShowScore();

	 this->index++;

	 //第二轮比赛

	 //抽签
	 this->speechDraw();

	//比赛
	 this->speechcontent();

	 //显示晋级选手信息
	 this->ShowScore();

	 //保存到文档中
	 this->SaveRecord();

	 //初始化容器
	this->init();
	//创建选手
	this->createSpeaker();
	//加载往届记录
	this->load_Record();//!

	 //读取文档记录
	 //this->load_Record();


	 system("pause");
	 system("cls");
 }
 void speakerManager::speechcontent()//比赛的核心内容
 {
	 cout<<"开始第<<"<<this->index<<">>轮比赛"<<endl;
	 cout<<endl;
	 vector<int>v_agc;//这个容器用来存放不同轮数数据
	 multimap<double,int,greater<double>>groupScore;//！！创建一个分数，编号，降序排列的数组容器
	 //multimap相对于map可以保存重复的元素
	 int num =0;//!记录人员个数，方便后面分组!

	 if(this->index==1)
	 {
		 v_agc = v1;
	 }
	 else
	 {
		  v_agc = v2;
	 }

	 for(vector<int>::iterator it = v_agc.begin();it!=v_agc.end();it++)//遍历该容器
	 {
		 num++;
		 deque<double>de;//!double//用来存放评委评分

		 for(int i=0; i<10;i++)
		 {
			 double score = (rand()%401+600)/10.f;//40-100,带分数
			// cout<<score;
			 de.push_back(score);//放进分数
		 }
			//cout<<endl;//这个回车导致两组之间一下子多出来10行空格
			//下面这些要在括号外面
			
			 de.pop_front();//去掉首尾
			 de.pop_back();
			 sort(de.begin(),de.end(),greater<double>());//降序排序
			 double sum = accumulate(de.begin(),de.end(),0.0f);//注意是0.0f
			 double ave = sum/(double)de.size();
			 this->m_speaker[*it].score[this->index-1] =ave;//!!this->m_speaker[*it]代表这个双头容器的第几个位置
			
			 groupScore.insert(make_pair(ave,*it));//将打分数据放到临时容器中，第一个是平均分，第二个是选手编号
			 if( num % 6  ==  0)
			 {
				 int a = num  / 6 ;
				 cout<<"第"<<a<<"组成员抽签情况如下："<<endl;

				 for(multimap<double,int,greater<double>>::iterator it = groupScore.begin();it!=groupScore.end();it++)
				 {
					 cout<<"选手编号:"<<it->second<<"  "<<"选手姓名："<<this->m_speaker[it->second].name<<"  "<<"选手平均分："<<it->first<<endl;
				 }

				 //取走容器中的前三名
				 int count=0;
				  for(multimap<double,int,greater<double>>::iterator it = groupScore.begin();it!=groupScore.end() && count<3;it++,count++)
				 {
					 if(this->index==1)
					 {
						 v2.push_back(it->second);
					 }
					 else
					 {
						 victory.push_back(it->second);
					 }
					 //cout<<"选手编号:"<<it->second<<"选手姓名："<<this->m_speaker[it->second].name<<"选手平均分："<<it->first<<endl;
				 }
				  groupScore.clear();
				 cout<<endl;
			 }		
	 }
	 cout<<"-------------------第"<<this->index<<"轮比赛结束----------------------"<<endl;
	 system("pause");
	//system("cls");
 }

 void speakerManager::ShowScore()
 {
	  cout<<"----------------第<<"<<this->index<<">>轮晋级选手的信息如下：----------------"<<endl;
	  vector<int>v; 
	  if(this->index==1)
	 {
		 v = this->v2;
	 }
	 else
	 {
		  v = this->victory;
	 }
	  sort(v.begin(),v.end());
	 for(vector<int>::iterator it = v.begin();it!=v.end();it++)//遍历该容器
	 {
		
		 cout<<"选手编号："<<*it<<"   "<<"选手姓名："<<this->m_speaker[*it].name<<"   "<<"选手分数："
			 <<this->m_speaker[*it].score[this->index-1]<<endl;//!double//用来存放评委评分
	 }
	 cout<<endl;
	
	 system("pause");
	 system("cls");
	 this->showMeu();//为了在第二轮的时候可以显示
 }

 void speakerManager::speechDraw()
 {
	 cout<<"第<<"<<this->index<<">>轮选手正在抽签..."<<endl;
	 cout<<"--------------------------------"<<endl;
	 cout<<"抽签的结果为："<<endl;
	 if(this->index==1)//!!
	 {
		 	 random_shuffle(v1.begin(),v1.end());
			 for(vector<int>::iterator it=this->v1.begin();it!=this->v1.end();it++)
			{
				 cout<<*it<<"  ";
			}
			 //this->index++;
			 cout<<endl;
			 //cout<<"--------------------------------"<<endl;
	 }
	 else
	 {
		 //第二轮比赛
		// cout<<"--------------------------------"<<endl;
		  random_shuffle(v2.begin(),v2.end());
		  for(vector<int>::iterator it=this->v2.begin();it!=this->v2.end();it++)
		{
		  cout<<*it<<"  ";
		}
	 }
	  system("pause");
	  cout<<endl;
	  //system("cls");
 }

 void speakerManager::showMeu()
 {
	cout<<"******************************"<<endl;
	cout<<"*******欢迎参加演讲比赛*******"<<endl;
	cout<<"********1.开始演讲比赛********"<<endl;
	cout<<"********2.查看往届记录********"<<endl;
	cout<<"********3.清空比赛记录********"<<endl;
	cout<<"********0.退出比赛程序********"<<endl;
	cout<<"******************************"<<endl;

	 cout<<endl;
 }

 void speakerManager:: SaveRecord()
 {
	ofstream ofs;
	ofs.open("speech.csv",ios::out|ios::app);//app代表后面可以不断追加
	for(vector<int>::iterator it=this->victory.begin();it!=this->victory.end();it++)
	{
		ofs<<*it<< ","<<this->m_speaker[*it].score[1]<<",";//不要写成score[this->index -1]
		//!!!!打印时前面一定要是ofs,不能是cout!!!!
	}
	ofs<<endl;
	ofs.close();
	cout<<"记录已保存！"<<endl;
	//更改文件不为空的状态
	this->fileIsempty=false;
 }

 void speakerManager::load_Record()//解析文件数据，获取往届分数
 {
	 ifstream ifs;
	 ifs.open("speech.csv",ios::in);
	 if(!ifs.is_open())
	 {
		 //cout<<"文件不存在！"<<endl;
		 this->fileIsempty=true;
		 ifs.close();
		 return;
	 }
		char ch;
		ifs>>ch;
	if(ifs.eof()) 
	{
			 //cout<<"文件为空！"<<endl;
			 this->fileIsempty=true;
			 ifs.close();
			 return;
	}
		//cout<<"文件已打开!"<<endl;
		 this->fileIsempty=false;

		 ifs.putback(ch);//！！！将上面取出来的ch放回去！！！

	//for(vector<int>::iterator it=this->victory.begin();it!=this->victory.end();it++)
	//{
	//	ofs<<*it<< ","<<this->m_speaker[*it].score[1]<<",";//不要写成score[this->index -1]
	//	//!!!!打印时前面一定要是ofs,不能是cout!!!!
	//}//根本不是这样读的

		 string data;
		 int index = 0;//用于将最下面将读取出来的数据放到容器中记录轮数
		 while(ifs>>data)
		 {
			 //cout<<data<<endl;//这个是一个字符一个字符输出，而下面的方式不是一个字符串输出，是不一样的
			 //10002,86.675,10009,81.3,10007,78.55,
		vector<string>v;//存放读取出来的数据，注意这些数据有编号有分数
		
		 int pos=-1;
		 int start=0;//这两个不能把放到while循环里不然一下子就跳出了
		 while(true)
		{
			  pos= data.find(",",start);
			 if(pos ==-1)
		 {
			 //cout<<"没有找到数据！"<<endl;
			 break;
		 }
			 string a=data.substr(start,pos-start);
			 //cout<<a<<endl;
			 v.push_back(a);
			 start = pos+1;//!!
		 }
		 this->m_Record.insert(make_pair(index,v));//记得加上.insert
		 index++;
		 }  
	  ifs.close();//！位置放错导致出错！
	  //for(map<int,vector<string>>::iterator it =this->m_Record.begin(); it!=this->m_Record.end();it++ )
		 //{
			// cout<<"演讲比赛第"<<it->first+1<<"届"<<"  "<<"冠军编号："<<it->second[0]<<"   "<<"冠军分数：" << it->second[1] <<endl;//仅仅输出一个
		 //}	 
 }

 //显示往届记录
 void speakerManager:: ShowRecord()
 {
	 if(this->fileIsempty)
	 {
		 cout<<"文件不存在或为空！"<<endl;
	 }
	 else
	 {
			 for(map<int,vector<string>>::iterator it =this->m_Record.begin(); it!=this->m_Record.end();it++ )
		 {
			 cout<<"第"<<it->first+1<<"届演讲比赛"<<endl;
			 cout<<"冠军编号："<<it->second[0]<<"   "<<"冠军分数：" << it->second[1] <<endl;//仅仅输出一个
			 cout<<"亚军编号："<<it->second[2]<<"   "<<"冠军分数：" << it->second[3] <<endl;
			 cout<<"季军编号："<<it->second[4]<<"   "<<"冠军分数：" << it->second[5] <<endl;
		 }	
	    system("pause");
		system("cls");
	 }
  
 }

 void speakerManager::clearRecord()
 {
	  if(this->fileIsempty)
	 {
		 cout<<"文件不存在或为空！"<<endl;
		 return;
	 }
	 cout<<"确定清空文件？"<<endl;
	 cout<<"1、确定！"<<endl;
	 cout<<"其他、重新输入"<<endl;

	 int select=0;
	 cin>>select;
		 
	 if(select==1)
	 {
		 ofstream ofs("speech.csv",ios::trunc);
		 ofs.close(); 
	 //初始化容器
	this->init();
	//创建选手
	this->createSpeaker();
	//加载往届记录
	this->load_Record();//!
	cout<<"清空成功！完结撒花！"<<endl;
	 }
	 else
	 {
		 cout<<"请重新输入！"<<endl;
	 }
	 

	     system("pause");
		system("cls");
		
 }
 void speakerManager::Exit()
 {
	 cout<<"欢迎下次光临！"<<endl;
	 system("pause");
	 exit(0);
 }



speakerManager::~speakerManager()//构造函数
{

 }


