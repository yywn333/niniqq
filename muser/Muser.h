#include<string>
using  std::string;

class Muser
{
private:

	int Id;								//用户id
	string UName;						//用户昵称
	string RealName;					//用户真实姓名
	string PassWord;					//登录密码
	string Logo;						//头像路径
	string Sex;							//性别
	string Friends;						//好友id
	string Birthday;					//生日
	string Place;						//所在地
	int state;							//状态

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