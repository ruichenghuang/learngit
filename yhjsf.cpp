#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int n=5;//总进程
const int m=4;//资源种类[A][B][C][D]
int TreadNo[5]={1,2,3,4,5};//进程号
int Resource[m];//总资源数
int Available[m];//剩余资源
int Need[n][m];//每个进程最大需求
int Allocation[n][m];//当前分配情况
int Request[n][m];//总请求情况
int a,b;//用于循环

void T()//菜单
{cout<<"****************************************"<<endl; 
 
cout<<"* 银行家算法演示系统 *"<<endl; 
 
cout<<"*****************************************"<<endl; 
 
cout<<"*         1.一键生成例题进程            *"<<endl; 
 
cout<<"*         2.请求资源并启动算法          *"<<endl; 
 
cout<<"*         3.查看进程                    *"<<endl; 
  
cout<<"*         4.退出                        *"<<endl;
cout<<"-----------------------------------------"<<endl;

cout<<" 请输入（1—4）：(请先输入1载入进程)"<<endl;
}
int main()
{
	while(1)
	{
		T();
		int sw=0;
		cin>>sw;
		switch(sw)
		{
		case 1:
			Need[0][0]=0;Need[0][1]=0;Need[0][2]=1;Need[0][3]=2;
			Need[1][0]=1;Need[1][1]=7;Need[1][2]=5;Need[1][3]=0;
		    Need[2][0]=2;Need[2][1]=3;Need[2][2]=5;Need[2][3]=6;
			Need[3][0]=0;Need[3][1]=6;Need[3][2]=5;Need[3][3]=2;
			Need[4][0]=0;Need[4][1]=6;Need[4][2]=5;Need[4][3]=6;

			Allocation[0][0]=0;Allocation[0][1]=0;Allocation[0][2]=0;Allocation[0][3]=0;
			Allocation[1][0]=1;Allocation[1][1]=0;Allocation[1][2]=0;Allocation[1][3]=0;
			Allocation[2][0]=1;Allocation[2][1]=3;Allocation[2][2]=5;Allocation[2][3]=4;
			Allocation[3][0]=0;Allocation[3][1]=6;Allocation[3][2]=3;Allocation[3][3]=2;
			Allocation[4][0]=0;Allocation[4][1]=0;Allocation[4][2]=1;Allocation[4][3]=4;

			Available[0]=1;Available[1]=5;Available[2]=2;Available[3]=0;

			Resource[0]=Available[0];Resource[1]=Available[1];Resource[2]=Available[2];Resource[3]=Available[3];
			for(a=0;a<=n-1;a++)
			{
				for(b=0;b<=m-1;b++)
				{
					Resource[b]=Resource[b]+Allocation[a][b];				
					Request[a][b]=0;
				}
			}
			
			cout<<"操作成功！"<<endl;
			cout<<endl;
			break;
		case 2:
			int p,sign,sign1,sign2,sign3;
			int A[m];//存放临时请求的数值
			//---------------------------------------------------------------------
			cout<<"进程号"<<setw(4)<<"A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<setw(10)<<"Need A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<setw(14)<<"Request A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<endl;  
			for(a=0;a<=n-1;a++) 
			{ 
				cout<<setw(4)<<TreadNo[a]<<setw(6)<<Allocation[a][0]<<setw(4)<<Allocation[a][1]<<setw(4)<<Allocation[a][2]<<setw(4)<<Allocation[a][3]<<setw(10)<<Need[a][0]<<setw(4)<<Need[a][1]<<setw(4)<<Need[a][2]<<setw(4)<<Need[a][3]<<setw(14)<<Request[a][0]<<setw(4)<<Request[a][1]<<setw(4)<<Request[a][2]<<setw(4)<<Request[a][3]<<endl;  
			} 
			cout<<endl;
			cout<<setw(5)<<"剩余     A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<setw(10)<<"总资源  A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<endl;
			cout<<setw(10)<<Available[0]<<setw(4)<<Available[1]<<setw(4)<<Available[2]<<setw(4)<<Available[3]<<setw(10)<<Resource[0]<<setw(4)<<Resource[1]<<setw(4)<<Resource[2]<<setw(4)<<Resource[3]<<endl;
		    cout<<endl; 
			//--------------------------打印进程状态列表--------------------------------
			cout<<"请输入请求资源的进程号：(输入0表示不请求资源，直接启动算法)"<<endl;
			cin>>p;
			if(p==0)  
			{
				p=1;
				A[0]=0;A[1]=0;A[2]=0;A[3]=0;
			}
			else
			{
			for(a=0;a<=n-1;a++)
			{
				if(p==TreadNo[a]) sign=1;
			}
			if(sign!=1) {cout<<"操作失败！找不到该进程！"<<endl; break;}
			
			cout<<"请输入请求的资源量（不大于所需资源和剩余资源）"<<endl;
			cout<<"A:  ";
			cin>>A[0];
				Request[p-1][0]=Request[p-1][0]+A[0];
			cout<<"B:  ";
			cin>>A[1];
				Request[p-1][1]=Request[p-1][1]+A[1];
			cout<<"C:  ";
			cin>>A[2];
				Request[p-1][2]=Request[p-1][2]+A[2];
			cout<<"D:  ";
			cin>>A[3];
				Request[p-1][3]=Request[p-1][3]+A[3];
			}
		
			
		    if(A[0]>Available[0]||A[1]>Available[1]||A[2]>Available[2]||A[3]>Available[3])
			{
				cout<<"操作失败！请求量大于剩余资源！"<<endl;
				for(a=0;a<=m-1;a++)
				{
					Request[p-1][a]=Request[p-1][a]-A[a];
				}
				break;
			}
			else if(Need[p-1][0]-Allocation[p-1][0]<A[0]||Need[p-1][1]-Allocation[p-1][1]<A[1]||Need[p-1][2]-Allocation[p-1][2]<A[2]||Need[p-1][3]-Allocation[p-1][3]<A[3])
			{
				cout<<"操作失败！请求量大于所需资源！"<<endl;
				for(a=0;a<=m-1;a++)
				{
					Request[p-1][a]=Request[p-1][a]-A[a];
				}
				break;
			}
			else
			{
				int Finish[n];//安全标志
				int need[n][m];//进程运行完毕需求资源量
				int work[m];//临时资源量
				for (a=0;a<=m-1;a++)
				{   
					work[a]=Available[a]-A[a];
				}
				for(a=0;a<=n-1;a++)
				{
					if(a==p-1) 
					{
						for(b=0;b<=m-1;b++)
						{
							need[a][b]=Need[a][b]-Allocation[a][b]-A[b];
						}					
					}
					else 
					{
						for(b=0;b<=m-1;b++)
						{
							need[a][b]=Need[a][b]-Allocation[a][b];
						}
							
					}
				}
				for(a=0;a<=n-1;a++)
					{
						Finish[a]=0;
					}
				while(1)
				{
				sign2=0;
				for(a=0;a<=n-1;a++)
				{	
					if(need[a][0]<=work[0]&&need[a][1]<=work[1]&&need[a][2]<=work[2]&&need[a][3]<=work[3])
					{
						if(Finish[a]!=1)
						{   sign2=1;
							Finish[a]=1;
							if(a==p-1)
							{
								for(b=0;b<=m-1;b++)
								{
									work[b]=work[b]+Allocation[a][b]+A[b];
								}

							}
							else
							{
								for(b=0;b<=m-1;b++)
								{
									work[b]=work[b]+Allocation[a][b];
								}
						   
							}	
						}
					}
					else Finish[a]=0;
					
				}
				if(sign2==0) break;
			    }

				for(a=0;a<=n-1;a++)
				{
					if(Finish[a]==0) 
					{
						sign1=1;
					}
				}
				if(sign1!=1)
				{
					cout<<endl;
					cout<<"系统安全！"<<endl;
				    cout<<endl;
					for(a=0;a<=m-1;a++)
					{						
						Allocation[p-1][a]=Allocation[p-1][a]+A[a];
						Available[a]=Available[a]-A[a];					
					}
				
                    for(a=0;a<=m-1;a++)
					{
						if(need[p-1][0]==0&&need[p-1][1]==0&&need[p-1][2]==0&&need[p-1][3]==0)
						{
							Available[a]=Available[a]+Allocation[p-1][a];
							Allocation[p-1][a]=0;
							Need[p-1][a]=0;
                            Request[p-1][a]=0;
						}
					}

				}
				else 
				{
                    cout<<"系统不安全！"<<endl;
					for(a=0;a<=m-1;a++)
				    {
					   Request[p-1][a]=Request[p-1][a]-A[a];
				    }
				}


			}
			sign3=0;
			for(a=0;a<=n-1;a++)
			{			
				for(b=0;b<=m-1;b++)
				{				
					if(Need[a][b]!=0) sign3=1;
				}
			}
			if(sign3==0) {cout<<"！！进程全部运行完毕！！"<<endl;}
			cout<<endl;
			break;
		
		case 3:
			cout<<"进程号"<<setw(4)<<"A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<setw(10)<<"Need A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<setw(14)<<"Request A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<endl;  
			for(a=0;a<=n-1;a++) 
			{ 
				cout<<setw(4)<<TreadNo[a]<<setw(6)<<Allocation[a][0]<<setw(4)<<Allocation[a][1]<<setw(4)<<Allocation[a][2]<<setw(4)<<Allocation[a][3]<<setw(10)<<Need[a][0]<<setw(4)<<Need[a][1]<<setw(4)<<Need[a][2]<<setw(4)<<Need[a][3]<<setw(14)<<Request[a][0]<<setw(4)<<Request[a][1]<<setw(4)<<Request[a][2]<<setw(4)<<Request[a][3]<<endl;  
			} 
			cout<<endl;
			cout<<setw(5)<<"剩余     A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<setw(10)<<"总资源  A"<<setw(4)<<"B"<<setw(4)<<"C"<<setw(4)<<"D"<<endl;
			cout<<setw(10)<<Available[0]<<setw(4)<<Available[1]<<setw(4)<<Available[2]<<setw(4)<<Available[3]<<setw(10)<<Resource[0]<<setw(4)<<Resource[1]<<setw(4)<<Resource[2]<<setw(4)<<Resource[3]<<endl;
		    cout<<endl;   
			break;
		case 4: 
			char t;  
			cout<<"退出？（Y/N）"<<endl; 
			cin>>t; 
			if(t=='Y'||t=='y') 
				exit(0);  
			break;  
		default: cout<<"请重新输入功能序号！"<<endl;
			break;  	
		}
//	system("pause"); 
/*printf("Press any key to continue") ;
struct termios te;
int ch;
tcgetattr(STDIN_FILENO,&te);
te.c_lflag &=~(ICANON|ECHO);
tcsetattr(STDIN_FILENO,TCSANOW,&te);
tcflush(STDIN_FILENO,TCIFLUSH);
fgetc(stdin) ; 
te.c_lflag |=(ICANON|ECHO);
tcsetattr(STDIN_FILENO,TCSANOW,&te);
 */
usleep(2000000);
/*for(;;)
{pause();}*/

system("clear");
	}
}
