#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned int
#define N 1048576
int memory[N],pos;
string code[N]={
	"input 0",             // 输入一个整数，并将其存放于内存的 0 号位置。
	"input 1",             // 输入一个整数，并将其存放于内存的 1 号位置。
	"calc add 0 1 2",      // 将内存的 0 号位置的数据与内存的 1 号位置的数据进行 add 运算，并将结果存放在内存的 2 号位置。
	"output int 2",        // 以 int 形式输出内存的 2 号位置中的数据。
	"exit"                 // 退出程序。
};
/*
程序解释:
	对其中每种指令的介绍（{} 表示必选参数，[] 表示可选参数）：
	
	input {x}：
		输入一个整数（范围：[-2的63次方 ，2的63次方 ]），并将其存放于内存的 x 号位置。
	
	output {mode} {x}：
		以 mode 形式（int 或 char，其中 char 形式是按照 ASCII 码输出）输出内存的 x 号位置中的数据。
	
	write {x} {y}：
		将内存的 x 号位置的数据设为 y。
	
	copy {x} {y}：
		将内存的 x 号位置的数据拷贝至内存的 y 号位置。
	
	calc {mode} {x} {y} [z]（当 mode 为 not 时无需 z）：
		将内存的 x 号位置的数据与内存的 y 号位置的数据进行 mode 运算（and、or、xor、add、sub、mul、div 或 mod，其中 div 操作在除数为 0 时会提示 Error: Division by Zero 并退出程序），并将结果存放在内存的 z 号位置。
	
		注：当 mode 为 not 时，其效果为将内存的 x 号位置的数据按位取反的结果存放在内存的 y 号位置；此处的 and、or、xor 和 not 均为位运算，逻辑运算是可以通过这个实现的，故没有单独制作。
	
	goto {x}：
		跳转至第 x 行（从 0 开始）代码。
	
	if {mode} {x} {y} {z}：
		如果内存的 x,y 号位置的数据满足 mode 这一关系（mode 可在 <、>、==、<=、>= 和 != 中选择），则跳转至第 z 行（从 0 开始）代码。
	
	++ {x}：
		将内存的 x 号位置的数据加 1。
	
	-- {x}：
		将内存的 x 号位置的数据减 1。
	
	exit：
		退出程序。
	
	此外，如果在运行过程中发现了无效的代码，则会提示 Error: Invalid Code 并直接退出程序。
	
	将 code 数组设为 "input 0", "input 1", "calc add 0 1 2", "output int 2", "exit" 即可实现 A+B Problem 的要求。
*/
string readStr(int x,int y)	// 从 code[x][y] 开始读取一个字符串, 读到空格为止 
{
	pos=y;
	string ret="";
	int len=code[x].length();
	while(pos<len && code[x][pos]==' ')
	{
		++pos;
	}
	while(pos<len && code[x][pos]!=' ')
	{
		ret=ret+code[x][pos++];
	}
	return ret;
}
int readInt(int x,int y)	// 从 code[x][y] 开始读取一个整数, 读到非数字为止 
{
	pos=y;
	int ret=0, len=code[x].length();
	bool f=0;
	while(pos<len && !isdigit(code[x][pos]))
	{
		if(code[x][pos]=='-')
		{
			f=1;
		}
		++pos;
	}
	while(pos<len && isdigit(code[x][pos]))
	{
		ret=(ret<<3)+(ret<<1)+(code[x][pos++]^48);
	}
	return f?-ret:ret;
}
signed main()
{
	for(int i=0;;i=(i+1)%N)
	{
		string op=readStr(i,0);
		if(op=="input")
		{
			int x=readInt(i,pos);
			cin>>memory[x];
		}
		else if(op=="output")
		{
			string mode=readStr(i,pos);
			if(mode=="int")
			{
				int x=readInt(i,pos);
				cout<<memory[x];
			}
			else if(mode=="char")
			{
				int x=readInt(i,pos);
				cout<<char(memory[x]%128);
			}
			else
			{
				cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
				break;
			}
		}
		else if(op=="write")
		{
			int x=readInt(i,pos), y=readInt(i,pos);
			memory[x]=y;
		}
		else if(op=="copy")
		{
			int x=readInt(i,pos), y=readInt(i,pos);
			memory[y]=memory[x];
		}
		else if(op=="calc")	// and or not xor add sub mul div mod
		{
			string mode=readStr(i,pos);
			int x=readInt(i,pos), y=readInt(i,pos), z=(mode=="not" ? 0 : readInt(i,pos));
			x=memory[x], y=memory[y];
			if(mode=="and")
			{
				memory[z]=x&y;
			}
			else if(mode=="or")
			{
				memory[z]=x|y;
			}
			else if(mode=="not")
			{
				memory[y]=~x;
			}
			else if(mode=="xor")
			{
				memory[z]=x^y;
			}
			else if(mode=="add")
			{
				memory[z]=x+y;
			}
			else if(mode=="sub")
			{
				memory[z]=x-y;
			}
			else if(mode=="mul")
			{
				memory[z]=x*y;
			}
			else if(mode=="div")
			{
				if(y==0)
				{
					cout<<"\n\nError: Division by Zero\n\n";
					break;
				}
				memory[z]=x/y;
			}
			else if(mode=="mod")
			{
				memory[z]=x%y;
			}
			else
			{
				cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
				break;
			}
		}
		else if(op=="goto")
		{
			int x=readInt(i,pos);
			i=x-1;
		}
		else if(op=="if")	// < > == <= >= !=
		{
			string mode=readStr(i,pos);
			int x=readInt(i,pos), y=readInt(i,pos), z=readInt(i,pos);
			x=memory[x], y=memory[y];
			if(mode=="<")
			{
				if(x<y)
				{
					i=z-1;
				}
			}
			else if(mode==">")
			{
				if(x>y)
				{
					i=z-1;
				}
			}
			else if(mode=="==")
			{
				if(x==y)
				{
					i=z-1;
				}
			}
			else if(mode=="<=")
			{
				if(x<=y)
				{
					i=z-1;
				}
			}
			else if(mode==">=")
			{
				if(x>=y)
				{
					i=z-1;
				}
			}
			else if(mode=="!=")
			{
				if(x!=y)
				{
					i=z-1;
				}
			}
			else
			{
				cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
				break;
			}
		}
		else if(op=="++")
		{
			int x=readInt(i,pos);
			memory[x]++;
		}
		else if(op=="--")
		{
			int x=readInt(i,pos);
			memory[x]--;
		}
		else if(op=="exit")
		{
			break;
		}
		else
		{
			cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
			break;
		}
	}
	return 0;
}
