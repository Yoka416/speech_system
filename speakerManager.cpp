#include "speakerManager.h"
#include"speaker.h"
#include<string>
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<vector>

 speakerManager::speakerManager()//���캯��
{
	//��ʼ������
	this->init();
	//����ѡ��
	this->createSpeaker();
	//���浽�ĵ��У����������¼
	this->load_Record();//ɵ����Ϊ����Ȼ�Ѻ����ŵ���!!��Ȼ��ķ�������!
 }

 void speakerManager::init()
 {
	 this->v1.clear();//�����ʼ��ѧϰһ��
	 this->v2.clear();
	 this->victory.clear();
	 this->m_speaker.clear();
	 this->m_Record.clear();
	 this->index=1;
 }


 void speakerManager::createSpeaker()
 {
	 string nameseed="ABCDEFGHIJKI";
	
	 for(int i=0;i <(int)nameseed.size();i++)//!ע�ⲻ��name.size()!
		{
			 string name = "ѡ��";
			 speaker sp;
			name+=nameseed[i];
			sp.name = name;

			for(int j=0;j<2;j++)//ÿһλѡ�ֶ�����������
		{
			sp.score[j]=0;
		}

			this->v1.push_back(i+10001);
			this->m_speaker.insert(make_pair(i+10001,sp));
		}
 }


 void speakerManager::startSpeech()//���������ܿ��
 {
	 //��ǩ
	 this->speechDraw();

	//����
	 this->speechcontent();

	 //��ʾ����ѡ����Ϣ
	 this->ShowScore();

	 this->index++;

	 //�ڶ��ֱ���

	 //��ǩ
	 this->speechDraw();

	//����
	 this->speechcontent();

	 //��ʾ����ѡ����Ϣ
	 this->ShowScore();

	 //���浽�ĵ���
	 this->SaveRecord();

	 //��ʼ������
	this->init();
	//����ѡ��
	this->createSpeaker();
	//���������¼
	this->load_Record();//!

	 //��ȡ�ĵ���¼
	 //this->load_Record();


	 system("pause");
	 system("cls");
 }
 void speakerManager::speechcontent()//�����ĺ�������
 {
	 cout<<"��ʼ��<<"<<this->index<<">>�ֱ���"<<endl;
	 cout<<endl;
	 vector<int>v_agc;//�������������Ų�ͬ��������
	 multimap<double,int,greater<double>>groupScore;//��������һ����������ţ��������е���������
	 //multimap�����map���Ա����ظ���Ԫ��
	 int num =0;//!��¼��Ա����������������!

	 if(this->index==1)
	 {
		 v_agc = v1;
	 }
	 else
	 {
		  v_agc = v2;
	 }

	 for(vector<int>::iterator it = v_agc.begin();it!=v_agc.end();it++)//����������
	 {
		 num++;
		 deque<double>de;//!double//���������ί����

		 for(int i=0; i<10;i++)
		 {
			 double score = (rand()%401+600)/10.f;//40-100,������
			// cout<<score;
			 de.push_back(score);//�Ž�����
		 }
			//cout<<endl;//����س���������֮��һ���Ӷ����10�пո�
			//������ЩҪ����������
			
			 de.pop_front();//ȥ����β
			 de.pop_back();
			 sort(de.begin(),de.end(),greater<double>());//��������
			 double sum = accumulate(de.begin(),de.end(),0.0f);//ע����0.0f
			 double ave = sum/(double)de.size();
			 this->m_speaker[*it].score[this->index-1] =ave;//!!this->m_speaker[*it]�������˫ͷ�����ĵڼ���λ��
			
			 groupScore.insert(make_pair(ave,*it));//��������ݷŵ���ʱ�����У���һ����ƽ���֣��ڶ�����ѡ�ֱ��
			 if( num % 6  ==  0)
			 {
				 int a = num  / 6 ;
				 cout<<"��"<<a<<"���Ա��ǩ������£�"<<endl;

				 for(multimap<double,int,greater<double>>::iterator it = groupScore.begin();it!=groupScore.end();it++)
				 {
					 cout<<"ѡ�ֱ��:"<<it->second<<"  "<<"ѡ��������"<<this->m_speaker[it->second].name<<"  "<<"ѡ��ƽ���֣�"<<it->first<<endl;
				 }

				 //ȡ�������е�ǰ����
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
					 //cout<<"ѡ�ֱ��:"<<it->second<<"ѡ��������"<<this->m_speaker[it->second].name<<"ѡ��ƽ���֣�"<<it->first<<endl;
				 }
				  groupScore.clear();
				 cout<<endl;
			 }		
	 }
	 cout<<"-------------------��"<<this->index<<"�ֱ�������----------------------"<<endl;
	 system("pause");
	//system("cls");
 }

 void speakerManager::ShowScore()
 {
	  cout<<"----------------��<<"<<this->index<<">>�ֽ���ѡ�ֵ���Ϣ���£�----------------"<<endl;
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
	 for(vector<int>::iterator it = v.begin();it!=v.end();it++)//����������
	 {
		
		 cout<<"ѡ�ֱ�ţ�"<<*it<<"   "<<"ѡ��������"<<this->m_speaker[*it].name<<"   "<<"ѡ�ַ�����"
			 <<this->m_speaker[*it].score[this->index-1]<<endl;//!double//���������ί����
	 }
	 cout<<endl;
	
	 system("pause");
	 system("cls");
	 this->showMeu();//Ϊ���ڵڶ��ֵ�ʱ�������ʾ
 }

 void speakerManager::speechDraw()
 {
	 cout<<"��<<"<<this->index<<">>��ѡ�����ڳ�ǩ..."<<endl;
	 cout<<"--------------------------------"<<endl;
	 cout<<"��ǩ�Ľ��Ϊ��"<<endl;
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
		 //�ڶ��ֱ���
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
	cout<<"*******��ӭ�μ��ݽ�����*******"<<endl;
	cout<<"********1.��ʼ�ݽ�����********"<<endl;
	cout<<"********2.�鿴�����¼********"<<endl;
	cout<<"********3.��ձ�����¼********"<<endl;
	cout<<"********0.�˳���������********"<<endl;
	cout<<"******************************"<<endl;

	 cout<<endl;
 }

 void speakerManager:: SaveRecord()
 {
	ofstream ofs;
	ofs.open("speech.csv",ios::out|ios::app);//app���������Բ���׷��
	for(vector<int>::iterator it=this->victory.begin();it!=this->victory.end();it++)
	{
		ofs<<*it<< ","<<this->m_speaker[*it].score[1]<<",";//��Ҫд��score[this->index -1]
		//!!!!��ӡʱǰ��һ��Ҫ��ofs,������cout!!!!
	}
	ofs<<endl;
	ofs.close();
	cout<<"��¼�ѱ��棡"<<endl;
	//�����ļ���Ϊ�յ�״̬
	this->fileIsempty=false;
 }

 void speakerManager::load_Record()//�����ļ����ݣ���ȡ�������
 {
	 ifstream ifs;
	 ifs.open("speech.csv",ios::in);
	 if(!ifs.is_open())
	 {
		 //cout<<"�ļ������ڣ�"<<endl;
		 this->fileIsempty=true;
		 ifs.close();
		 return;
	 }
		char ch;
		ifs>>ch;
	if(ifs.eof()) 
	{
			 //cout<<"�ļ�Ϊ�գ�"<<endl;
			 this->fileIsempty=true;
			 ifs.close();
			 return;
	}
		//cout<<"�ļ��Ѵ�!"<<endl;
		 this->fileIsempty=false;

		 ifs.putback(ch);//������������ȡ������ch�Ż�ȥ������

	//for(vector<int>::iterator it=this->victory.begin();it!=this->victory.end();it++)
	//{
	//	ofs<<*it<< ","<<this->m_speaker[*it].score[1]<<",";//��Ҫд��score[this->index -1]
	//	//!!!!��ӡʱǰ��һ��Ҫ��ofs,������cout!!!!
	//}//����������������

		 string data;
		 int index = 0;//���ڽ������潫��ȡ���������ݷŵ������м�¼����
		 while(ifs>>data)
		 {
			 //cout<<data<<endl;//�����һ���ַ�һ���ַ������������ķ�ʽ����һ���ַ���������ǲ�һ����
			 //10002,86.675,10009,81.3,10007,78.55,
		vector<string>v;//��Ŷ�ȡ���������ݣ�ע����Щ�����б���з���
		
		 int pos=-1;
		 int start=0;//���������ܰѷŵ�whileѭ���ﲻȻһ���Ӿ�������
		 while(true)
		{
			  pos= data.find(",",start);
			 if(pos ==-1)
		 {
			 //cout<<"û���ҵ����ݣ�"<<endl;
			 break;
		 }
			 string a=data.substr(start,pos-start);
			 //cout<<a<<endl;
			 v.push_back(a);
			 start = pos+1;//!!
		 }
		 this->m_Record.insert(make_pair(index,v));//�ǵü���.insert
		 index++;
		 }  
	  ifs.close();//��λ�÷Ŵ��³���
	  //for(map<int,vector<string>>::iterator it =this->m_Record.begin(); it!=this->m_Record.end();it++ )
		 //{
			// cout<<"�ݽ�������"<<it->first+1<<"��"<<"  "<<"�ھ���ţ�"<<it->second[0]<<"   "<<"�ھ�������" << it->second[1] <<endl;//�������һ��
		 //}	 
 }

 //��ʾ�����¼
 void speakerManager:: ShowRecord()
 {
	 if(this->fileIsempty)
	 {
		 cout<<"�ļ������ڻ�Ϊ�գ�"<<endl;
	 }
	 else
	 {
			 for(map<int,vector<string>>::iterator it =this->m_Record.begin(); it!=this->m_Record.end();it++ )
		 {
			 cout<<"��"<<it->first+1<<"���ݽ�����"<<endl;
			 cout<<"�ھ���ţ�"<<it->second[0]<<"   "<<"�ھ�������" << it->second[1] <<endl;//�������һ��
			 cout<<"�Ǿ���ţ�"<<it->second[2]<<"   "<<"�ھ�������" << it->second[3] <<endl;
			 cout<<"������ţ�"<<it->second[4]<<"   "<<"�ھ�������" << it->second[5] <<endl;
		 }	
	    system("pause");
		system("cls");
	 }
  
 }

 void speakerManager::clearRecord()
 {
	  if(this->fileIsempty)
	 {
		 cout<<"�ļ������ڻ�Ϊ�գ�"<<endl;
		 return;
	 }
	 cout<<"ȷ������ļ���"<<endl;
	 cout<<"1��ȷ����"<<endl;
	 cout<<"��������������"<<endl;

	 int select=0;
	 cin>>select;
		 
	 if(select==1)
	 {
		 ofstream ofs("speech.csv",ios::trunc);
		 ofs.close(); 
	 //��ʼ������
	this->init();
	//����ѡ��
	this->createSpeaker();
	//���������¼
	this->load_Record();//!
	cout<<"��ճɹ������������"<<endl;
	 }
	 else
	 {
		 cout<<"���������룡"<<endl;
	 }
	 

	     system("pause");
		system("cls");
		
 }
 void speakerManager::Exit()
 {
	 cout<<"��ӭ�´ι��٣�"<<endl;
	 system("pause");
	 exit(0);
 }



speakerManager::~speakerManager()//���캯��
{

 }


