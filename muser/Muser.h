#include<string>
using  std::string;

class Muser
{
private:

	int Id;								//�û�id
	string UName;						//�û��ǳ�
	string RealName;					//�û���ʵ����
	string PassWord;					//��¼����
	string Logo;						//ͷ��·��
	string Sex;							//�Ա�
	string Friends;						//����id
	string Birthday;					//����
	string Place;						//���ڵ�
	int state;							//״̬

public:
	Muser();
	Muser(int Id=0,
		string UName=string(""),
		string RealName=string(""),
		string PassWord=string(""),
		string Logo=string(""),
		string Sex=string(""),
		string Friends=string(""),
		string Birthday=string(""),
		string Place=string(""),
		int state=0
		);



}