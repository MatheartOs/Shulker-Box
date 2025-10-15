#include <bits/stdc++.h>
using namespace std;
/*2021 清华大学学生程序设计竞赛暨高校邀请赛T2*/
/*Matheart*/

//基础参数环节
int Number_of_Player;					//输入双方参战人数
int Alice_Player,Bob_player;			//双方阵营分别人数
int Round;								//统计回合数
bool gameover=false;					//判断是否需要结束游戏

int who_used_skill_10;					//谁开大了
int end_round_by_skill_10;				//开大之后10回合之内必结束比赛，因此比赛最后结束回合得到限制

int now_atk[50000][2],now_def[50000][2];//用来上buff，并且回合结束之后用来卸buff回溯
int det_atk[50000][2],det_def[50000][2],det_mp[50000][2];//用来记录技能buff时间

struct character						//角色属性
{
	int character_id;					//当前角色id
	
	int HP,hp;							//最大生命值 和 当前生命值
	int MP,mp;							//最大能量值 和 当前能量值
	int atk,det_atk;					//基础攻击力 和 攻击力增益
	int def,det_def;					//基础防御力 和 防御力增益
	
	int talent,talent_x,talent_y;		//天赋及其参数
	int skill,skill_x,skill_y,skill_z;	//技能及其参数
	
	bool if_alive;						//是否存活
	bool site;							//标记阵营 1为Alice阵营，0为Bob阵营
	int target;							//攻击目标
}Alice[15],Bob[15];						//双方

character start;						//定义空结构体用来赋初值

struct target_character					//攻击目标状态
{
	int character_id;					//攻击目标的编号
	bool if_alive;						//攻击目标是否存活
}Alice_Target[25][25],Bob_Target[25][25];

//判断胜负和是否平局
void if_gameover()
{
	if(Alice_Player==0&&Bob_player==0)			//如果都似了
	{
		cout<<"Ciallo~"<<endl;	//就平局力（悲
		gameover=true;							//标记游戏结束
	}
	if(Alice_Player==0&&Bob_player!=0)			//如果Alice似了
	{
		cout<<Round<<endl;						//游戏结束，输出结束回合数
		cout<<"Bob"<<endl;						//Bob就赢力（喜
		for(int i=1;i<=Number_of_Player;i++)
		{
			cout<<(max(Bob[i].hp,0))<<' ';
		}
		gameover=true;							//标记游戏结束
	}
	if(Alice_Player!=0&&Bob_player==0)			//如果Bob似了
	{
		cout<<Round<<endl;						//游戏结束，输出结束回合数
		cout<<"Alice"<<endl;					//Alice就赢力（喜
		for(int i=1;i<=Number_of_Player;i++)
		{
			cout<<(max(Alice[i].hp,0))<<' ';
		}
		gameover=true;							//标记游戏结束
	}
	return;
}

//判断是否死亡
void if_dead(character &i)						//这里务必要引用，因为要改变目标对象的状态！
{
	if(i.hp<=0)//如果血条掉光了，他就似了
	{
		i.if_alive=false;//开始处理后事
		i.hp=0;//要是被一发打成负血量就拉回到0
		if(i.site==1){//如果是Alice阵营
			Alice_Player--;//Alice就少一个角色
			for(int j=1;j<=Number_of_Player;j++)
			{
				for(int k=1;k<=Number_of_Player;k++)
				{
					if(Bob_Target[j][k].character_id==i.character_id)//在Bob的攻击对象里找到这个似了的
					{
						Bob_Target[j][k].if_alive=false;//告诉这个角色他的攻击对象似了，防止鞭尸
					}
				}
			}
		}
		else
		{//Bob阵营同理
			Bob_player--;
			for(int j=1;j<=Number_of_Player;j++)
			{
				for(int k=1;k<=Number_of_Player;k++)
				{
					if(Alice_Target[j][k].character_id==i.character_id)
					{
						Alice_Target[j][k].if_alive=false;
					}
				}
			}
		}
	}
	if_gameover();
}

void reduce_hp(character &i,int damage,int real_damage)//掉血环节
{
	if(i.talent==1)//如果掉血对象有【天赋 — 血肉皮囊】
	{
		i.hp-=max(damage-max(i.def+i.det_def,0),0)+real_damage-real_damage/2;//那么就少点真伤
	}
	else//如果没这个天赋
	{
		i.hp-=max(damage-max(i.def+i.det_def,0),0)+real_damage;//那就正常扣血
	}
	if(i.mp<i.MP)//根据题意，如果被打了，能量槽就要恢复一点
	{
		i.mp++;
	}
	if_dead(i);//打完之后看一下似了没
}

void find_target(character &i)
{
	if(i.site==1)//如果要找Alice的攻击目标
	{
		for(int j=1;j<=Number_of_Player;j++)
		{
			if(Alice_Target[i.character_id][j].if_alive)
			{
				i.target=Alice_Target[i.character_id][j].character_id;
				return;
			}
		}
	}
	if(i.site==0)//如果要找Bob的攻击目标
	{
		for(int j=1;j<=Number_of_Player;j++)
		{
			if(Bob_Target[i.character_id][j].if_alive)
			{
				i.target=Bob_Target[i.character_id][j].character_id;
				return;
			}
		}
	}
}

void Alice_attack(character &i)//Alice使用普攻
{
	int A=max(i.atk+i.det_atk,1);
	if(i.talent==4)//如果【天赋 — 超凡入圣】，那么普通攻击变为真伤
	{
		reduce_hp(Bob[i.target],0,A);
	}
	else if(i.talent==2)//如果【天赋 — 星河力量投射】，那么普攻附带x真伤
	{
		reduce_hp(Bob[i.target],A,i.talent_x);
	}
	else
	{
		reduce_hp(Bob[i.target],A,0); 
	}
}

void Bob_attack(character &i)//Bob使用普攻
{
	int A=max(i.atk+i.det_atk,1);
	if(i.talent==4)//如果【天赋 — 超凡入圣】，那么普通攻击变为真伤
	{
		reduce_hp(Alice[i.target],0,A);
	}
	else if(i.talent==2)//如果【天赋 — 星河力量投射】，那么普攻附带x真伤
	{
		reduce_hp(Alice[i.target],A,i.talent_x);
	}
	else
	{
		reduce_hp(Alice[i.target],A,0); 
	}
}

int damage_taking(character &i,int damage,int real_damage)//计算受伤后扣除生命值
{
	if(i.talent==1)
	{
		return max(damage-max(i.def+i.det_def,0),0)+real_damage-real_damage/2;
	}
	else
	{
		return max(damage-max(i.def+i.det_def,0),0)+real_damage;
	}
}

int Alice_attack_reduce(character &i)//计算Alice普攻扣除的生命值
{
	int A=max(i.atk+i.det_atk,1);
	if(i.talent==4)//如果【天赋 — 超凡入圣】，那么普通攻击变为真伤
	{
		return damage_taking(Bob[i.target],0,A);
	}
	else if(i.talent==2)//如果【天赋 — 星河力量投射】，那么普攻附带x真伤
	{
		return damage_taking(Bob[i.target],A,i.talent_x);
	}
	else
	{
		return damage_taking(Bob[i.target],A,0); 
	}
}

int Bob_attack_reduce(character &i)//计算Bob普攻扣除的生命值
{
	int A=max(i.atk+i.det_atk,1);
	if(i.talent==4)//如果【天赋 — 超凡入圣】，那么普通攻击变为真伤
	{
		return damage_taking(Alice[i.target],0,A);
	}
	else if(i.talent==2)//如果【天赋 — 星河力量投射】，那么普攻附带x真伤
	{
		return damage_taking(Alice[i.target],A,i.talent_x);
	}
	else
	{
		return damage_taking(Alice[i.target],A,0); 
	}
}

void Alice_skill_used_by(character &user)//使用技能
{
	int skill_id=user.skill;
	int x=user.skill_x;
	int y=user.skill_y;
	int z=user.skill_z;
	if(skill_id==0) //【技能：心态崩了！】
	{
		//最难绷的技能，拿到这技能的角色这辈子有了（开大除外）
		return;//如发
	}
	if(skill_id==1)//【技能：格林炸裂！】	ps:怎么是凯露酱的技能啊喂！
	{
		for(int i=1;i<=Number_of_Player;i++)//对所有角色
		{
			if(Bob[i].if_alive)//前提是活着
			{
				reduce_hp(Bob[i],x,0);//造成x点伤害
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
				else//如果没结束
				{
					Bob[i].mp=max(Bob[i].mp-Bob[i].mp/10,0);//给目标扣除能量值
				}
			}
		}
		return;
	}
	if(skill_id==2)//【技能：日 (zhou) 昇 (ji) 之 (dao) 雨 (dan)！】
	{
		for(int i=1;i<=Number_of_Player;i++)//对所有角色
		{
			if(Bob[i].if_alive)//前提是活着
			{
				reduce_hp(Bob[i],0,max(user.atk+user.det_atk,1));//造成A点真伤
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
			}
		}
		return;
	}
	if(skill_id==3)//【技能：天楼霸断剑！】
	{
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].if_alive)
			{
				reduce_hp(Bob[i],min(Bob[i].HP/10,x*(max(user.atk+user.det_atk,1))),0);
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
			}
		}
		return;
	}
	if(skill_id==4)//【技能：演出开始！】
	{
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_mp[i][1]+=y;
		}
		return;
	}
	if(skill_id==5)//【技能：天狼噬斩！】
	{
		Bob[user.target].det_def-=x;
		reduce_hp(Bob[user.target],0,max(user.atk+user.det_atk,1));
		return;
	}
	if(skill_id==6)//【技能：地 (太) 球 (虚) 蓝 (苍) 色 (蓝) 闪 (闪) 电！】
	{
		reduce_hp(Bob[user.target],0,max(user.atk+user.det_atk,1));
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_atk[i][0]-=y;
		}
		return;
	}
	if(skill_id==7)//【技能：极光绽放！】
	{
		character who_has_the_min_hp;
		who_has_the_min_hp.hp=2e9;
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				if(Alice[i].hp<who_has_the_min_hp.hp)
				{
					who_has_the_min_hp=Alice[i];
				}
				/*
				else if(Alice[i].hp==who_has_the_min_hp.hp && Alice[i].character_id<who_has_the_min_hp.character_id)
				{
					who_has_the_min_hp=Alice[i];
				}
				*/
			}
		}
		Alice[who_has_the_min_hp.character_id].hp=min(Alice[who_has_the_min_hp.character_id].hp+z,Alice[who_has_the_min_hp.character_id].HP);
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_atk[i][1]+=y;
		}
		return;
	}
	if(skill_id==8)//【技能：流星！】
	{
		for(int i=1;i<=Number_of_Player;i++)//对所有角色
		{
			if(Bob[i].if_alive)//前提是活着
			{
				reduce_hp(Bob[i],max(user.atk+user.det_atk,1),0);//造成A点真伤
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
			}
		}
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_def[i][0]-=y;
		}
		return;
	}
	if(skill_id==9)//【技能：精灵庇护！】
	{
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				Alice[i].hp=min(Alice[i].hp+z,Alice[i].HP);
			}
		}
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_def[i][1]+=y;
		}
		return;
	}
	if(skill_id==10)//【技能：全力超全开！轮回之终末！】	大招
	{
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				Alice[i].atk*=2;
				Alice[i].def*=2;
				Alice[i].hp=max(Alice[i].HP/2,Alice[i].hp);
				Alice[i].mp=max(Alice[i].MP/2,Alice[i].mp);
			}
		}
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_mp[i][1]+=1;
		}
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive&&Alice[i].skill==10)
			{
				Alice[i].skill=0;
			}
			if(Bob[i].if_alive&&Bob[i].skill==10)
			{
				Bob[i].skill=0;
			}
		}
		who_used_skill_10=1;
		end_round_by_skill_10=Round+x-1;
		return;
	}
}

void Bob_skill_used_by(character &user)//使用技能
{
	int skill_id=user.skill;
	int x=user.skill_x;
	int y=user.skill_y;
	int z=user.skill_z;
	if(skill_id==0) //【技能：心态崩了！】
	{
		//最难绷的技能，拿到这技能的角色这辈子有了（开大除外）
		return;//如发
	}
	if(skill_id==1)//【技能：格林炸裂！】	ps:怎么是凯露酱的技能啊喂！
	{
		for(int i=1;i<=Number_of_Player;i++)//对所有角色
		{
			if(Alice[i].if_alive)//前提是活着
			{
				reduce_hp(Alice[i],x,0);//造成x点伤害
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
				else//如果没结束
				{
					Alice[i].mp=max(Alice[i].mp-Alice[i].mp/10,0);//给目标扣除能量值
				}
			}
		}
		return;
	}
	if(skill_id==2)//【技能：日 (zhou) 昇 (ji) 之 (dao) 雨 (dan)！】
	{
		for(int i=1;i<=Number_of_Player;i++)//对所有角色
		{
			if(Alice[i].if_alive)//前提是活着
			{
				reduce_hp(Alice[i],0,max(user.atk+user.det_atk,1));//造成A点真伤
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
			}
		}
		return;
	}
	if(skill_id==3)//【技能：天楼霸断剑！】
	{
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				reduce_hp(Alice[i],min(Alice[i].HP/10,x*max(user.atk+user.det_atk,1)),0);
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
			}
		}
		return;
	}
	if(skill_id==4)//【技能：演出开始！】
	{
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_mp[i][0]+=y;
		}
		return;
	}
	if(skill_id==5)//【技能：天狼噬斩！】
	{
		Alice[user.target].det_def-=x;
		reduce_hp(Alice[user.target],0,max(user.atk+user.det_atk,1));
		return;
	}
	if(skill_id==6)//【技能：地 (太) 球 (虚) 蓝 (苍) 色 (蓝) 闪 (闪) 电！】
	{
		reduce_hp(Alice[user.target],0,max(user.atk+user.det_atk,1));
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_atk[i][1]-=y;
		}
		return;
	}
	if(skill_id==7)//【技能：极光绽放！】
	{
		character who_has_the_min_hp;
		who_has_the_min_hp.hp=2e9;
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].if_alive)
			{
				if(Bob[i].hp<who_has_the_min_hp.hp)
				{
					who_has_the_min_hp=Bob[i];
				}
				/*
				  else if(Bob[i].hp==who_has_the_min_hp.hp && Bob[i].character_id<who_has_the_min_hp.character_id)
				  {
				  who_has_the_min_hp=Bob[i];
				  }
				 */
			}
		}
		Bob[who_has_the_min_hp.character_id].hp=min(Bob[who_has_the_min_hp.character_id].hp+z,Bob[who_has_the_min_hp.character_id].HP);
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_atk[i][0]+=y;
		}
		return;
	}
	if(skill_id==8)//【技能：流星！】
	{
		for(int i=1;i<=Number_of_Player;i++)//对所有角色
		{
			if(Alice[i].if_alive)//前提是活着
			{
				reduce_hp(Alice[i],max(user.atk+user.det_atk,1),0);//造成A点真伤
				if(gameover)//打完之后看一下游戏结束了没
				{
					return;
				}
			}
		}
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_def[i][1]-=y;
		}
		return;
	}
	if(skill_id==9)//【技能：精灵庇护！】
	{
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].if_alive)
			{
				Bob[i].hp=min(Bob[i].hp+z,Bob[i].HP);
			}
		}
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_def[i][0]+=y;
		}
		return;
	}
	if(skill_id==10)//【技能：全力超全开！轮回之终末！】	大招
	{
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].if_alive)
			{
				Bob[i].atk*=2;
				Bob[i].def*=2;
				Bob[i].hp=max(Bob[i].HP/2,Bob[i].hp);
				Bob[i].mp=max(Bob[i].MP/2,Bob[i].mp);
			}
		}
		for(int i=Round;i<=Round+x-1;i++)
		{
			det_mp[i][0]+=1;
		}
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive&&Alice[i].skill==10)
			{
				Alice[i].skill=0;
			}
			if(Bob[i].if_alive&&Bob[i].skill==10)
			{
				Bob[i].skill=0;
			}
		}
		who_used_skill_10=2;
		end_round_by_skill_10=Round+x-1;
		return;
	}
}

//进入游戏主体部分
int main()
{
	start={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};									//初始化赋初值结构体
	
	cin>>Number_of_Player;															//输入双方的参战人数
	Alice_Player=Number_of_Player;													//初始状态，双方人全满
	Bob_player=Number_of_Player;													//初始状态，双方人全满
	
	for(int i=1;i<=Number_of_Player;i++)											//描述Alice队的角色
	{
		cin>>Alice[i].HP>>Alice[i].MP>>Alice[i].atk>>Alice[i].def;					//input第4i-3行，输入角色面板
		for(int j=1;j<=Number_of_Player;j++)
		{
			cin>>Alice_Target[i][j].character_id;									//input第4i-2行，输入攻击顺序
			Alice_Target[i][j].if_alive=true;										//游戏还未开始，所有攻击目标均为存活状态
		}
		cin>>Alice[i].talent>>Alice[i].talent_x>>Alice[i].talent_y;					//input第4i-1行，输入该角色天赋
		cin>>Alice[i].skill>>Alice[i].skill_x>>Alice[i].skill_y>>Alice[i].skill_z;	//input第4i行，输入该角色技能
		
		Alice[i].hp=Alice[i].HP;													//保证开始游戏时角色满血
		Alice[i].if_alive=true;														//得让角色一开始是活着的
		Alice[i].character_id=i;													//先打个编号，后面可能会有用
		Alice[i].site=1;															//划分阵营，Alice的阵营是1
	}
	
	for(int i=1;i<=Number_of_Player;i++)											//描述Bob队的角色
	{
		cin>>Bob[i].HP>>Bob[i].MP>>Bob[i].atk>>Bob[i].def;							//第4i-3行，输入角色面板
		for(int j=1;j<=Number_of_Player;j++)
		{
			cin>>Bob_Target[i][j].character_id;										//input第4i-2行，输入攻击顺序
			Bob_Target[i][j].if_alive=true;											//游戏还未开始，所有攻击目标均为存活状态
		}
		cin>>Bob[i].talent>>Bob[i].talent_x>>Bob[i].talent_y;						//input第4i-1行，输入该角色天赋
		cin>>Bob[i].skill>>Bob[i].skill_x>>Bob[i].skill_y>>Bob[i].skill_z;			//input第4i行，输入该角色技能
		
		Bob[i].hp=Bob[i].HP;														//保证开始游戏时角色满血
		Bob[i].if_alive=true;														//得让角色一开始是活着的
		Bob[i].character_id=i;														//先打个编号，后面可能会有用
		Bob[i].site=0;																//划分阵营，Bob的阵营是0
	}
	
	//输入信息完毕，准备开战！
	for(Round=1;Round<=23335;Round++)												//跳出循环说明分不出胜负
	{
		//记录本回合buff
		now_atk[Round][1]=det_atk[Round][1];
		now_def[Round][1]=det_def[Round][1];
		now_atk[Round][0]=det_atk[Round][0];
		now_def[Round][0]=det_def[Round][0];
		//Alice和Bob行动前上buff
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				Alice[i].det_def+=now_def[Round][1];
				Alice[i].det_atk+=now_atk[Round][1];
			}
			if(Bob[i].if_alive)
			{
				Bob[i].det_def+=now_def[Round][0];
				Bob[i].det_atk+=now_atk[Round][0];
			}
		}
		
		//Alice行动
		
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				find_target(Alice[i]);
			}
		}
		
		//寻找Alice放技能的人
		character Alice_skiller;
		Alice_skiller=start;
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].mp==Alice[i].MP && Alice[i].if_alive)
			{
				if(Alice[i].skill>Alice_skiller.skill)
				{
					Alice_skiller=Alice[i];
				}
				else if(Alice[i].skill==Alice_skiller.skill)
				{
					if(Alice[i].character_id>Alice_skiller.character_id)
					{
						Alice_skiller=Alice[i];
					}
				}
			}
		}
		
		if(Alice_skiller.character_id!=0)//如果不等于0说明找到了能放技能的人
		{
			int id=Alice_skiller.character_id;
			Alice[id].mp=0;//因为放了技能所以能量值清零
			Alice_skill_used_by(Alice_skiller);
			if(gameover)
			{
				return 0;
			}
			Alice[id].mp+=1;//角色释放完技能后能量值加 1
			if(Alice[id].talent==5)//如果放技能的角色有【天赋 — 科技至上】，那么还要考虑放完技能之后额外回复的能量值
			{
				Alice[id].mp=min(Alice[id].mp+Alice[id].talent_y,Alice[id].MP);
			}
			for(int i=1;i<=Number_of_Player;i++)
			{
				if(Alice[i].if_alive)
				{
					Alice[i].det_def-=now_def[Round][1];
					Alice[i].det_atk-=now_atk[Round][1];
				}
				if(Bob[i].if_alive)
				{
					Bob[i].det_def-=now_def[Round][0];
					Bob[i].det_atk-=now_atk[Round][0];
				}
			}
			now_atk[Round][1]=det_atk[Round][1];
			now_def[Round][1]=det_def[Round][1];
			now_atk[Round][0]=det_atk[Round][0];
			now_def[Round][0]=det_def[Round][0];
			for(int i=1;i<=Number_of_Player;i++)
			{
				if(Alice[i].if_alive)
				{
					Alice[i].det_def+=det_def[Round][1];
					Alice[i].det_atk+=det_atk[Round][1];
				}
				if(Bob[i].if_alive)
				{
					Bob[i].det_def+=det_def[Round][0];
					Bob[i].det_atk+=det_atk[Round][0];
				}
			}
		}
		
		character Alice_attacker=start;
		if(Alice_skiller.character_id==0)//没有能用技能的人，就使用普攻
		{
			for(int i=1;i<=Number_of_Player;i++)
			{
				if(Alice[i].if_alive)
				{
					if(Bob[Alice[i].target].hp>Bob[Alice_attacker.target].hp)
					{
						Alice_attacker=Alice[i];
					}
					else if(Bob[Alice[i].target].hp==Bob[Alice_attacker.target].hp)
					{
						int damage_1=Alice_attack_reduce(Alice[i]);
						int damage_2=Alice_attack_reduce(Alice_attacker);
						if(damage_1>damage_2)
						{
							Alice_attacker=Alice[i];
						}
						else if(damage_1==damage_2)
						{
							if(Alice[i].character_id>Alice_attacker.character_id)
							{
								Alice_attacker=Alice[i];
							}
						}
					}
				}
			}
			int id=Alice_attacker.character_id;
			Alice_attack(Alice_attacker);//放普攻
			if(gameover)
			{
				return 0;
			}
			Alice[id].mp=min(Alice[id].mp+1,Alice[id].MP);//普攻回能
			if(Alice[id].talent==5)//科技至上天赋回血
			{
				Alice[id].hp=min(Alice[id].hp+Alice[id].talent_x,Alice[id].HP);
			}
		}
		
		//Alice行动结束
		
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				Alice[i].mp=min(Alice[i].mp+1,Alice[i].MP);
				if(Alice[i].talent==3)
				{
					Alice[i].hp=min(Alice[i].hp+Alice[i].talent_x,Alice[i].HP);
					Alice[i].mp=min(Alice[i].mp+Alice[i].talent_y,Alice[i].MP);
				}
				Alice[i].mp=min(Alice[i].mp+det_mp[Round][1],Alice[i].MP);
			}
		}
		
		//Bob行动
		
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].if_alive)
			{
				find_target(Bob[i]);
			}
		}
		
		character Bob_skiller;
		Bob_skiller=start;
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].mp==Bob[i].MP && Bob[i].if_alive)
			{
				if(Bob[i].skill>Bob_skiller.skill)
				{
					Bob_skiller=Bob[i];
				}
				else if(Bob[i].skill==Bob_skiller.skill)
				{
					if(Bob[i].character_id>Bob_skiller.character_id)
					{
						Bob_skiller=Bob[i];
					}
				}
			}
		}
		
		if(Bob_skiller.character_id!=0)//如果不等于0说明找到了能放技能的人
		{
			int id=Bob_skiller.character_id;
			Bob[id].mp=0;//因为放了技能所以能量值清零
			Bob_skill_used_by(Bob_skiller);
			if(gameover)
			{
				return 0;
			}
			Bob[id].mp+=1;//角色释放完技能后能量值加 1
			if(Bob[id].talent==5)//如果放技能的角色有【天赋 — 科技至上】，那么还要考虑放完技能之后额外回复的能量值
			{
				Bob[id].mp=min(Bob[id].mp+Bob[id].talent_y,Bob[id].MP);
			}
			for(int i=1;i<=Number_of_Player;i++)
			{
				if(Alice[i].if_alive)
				{
					Alice[i].det_def-=now_def[Round][1];
					Alice[i].det_atk-=now_atk[Round][1];
				}
				if(Bob[i].if_alive)
				{
					Bob[i].det_def-=now_def[Round][0];
					Bob[i].det_atk-=now_atk[Round][0];
				}
			}
			now_atk[Round][1]=det_atk[Round][1];
			now_def[Round][1]=det_def[Round][1];
			now_atk[Round][0]=det_atk[Round][0];
			now_def[Round][0]=det_def[Round][0];
			for(int i=1;i<=Number_of_Player;i++)
			{
				if(Alice[i].if_alive)
				{
					Alice[i].det_def+=det_def[Round][1];
					Alice[i].det_atk+=det_atk[Round][1];
				}
				if(Bob[i].if_alive)
				{
					Bob[i].det_def+=det_def[Round][0];
					Bob[i].det_atk+=det_atk[Round][0];
				}
			}
		}
		
		character Bob_attacker=start;
		if(Bob_skiller.character_id==0)//没有能用技能的人，就使用普攻
		{
			for(int i=1;i<=Number_of_Player;i++)
			{
				if(Bob[i].if_alive)
				{
					if(Alice[Bob[i].target].hp>Alice[Bob_attacker.target].hp)
					{
						Bob_attacker=Bob[i];
					}
					else if(Alice[Bob[i].target].hp==Alice[Bob_attacker.target].hp)
					{
						int damage_1=Bob_attack_reduce(Bob[i]);
						int damage_2=Bob_attack_reduce(Bob_attacker);
						if(damage_1>damage_2)
						{
							Bob_attacker=Bob[i];
						}
						else if(damage_1==damage_2)
						{
							if(Bob[i].character_id>Bob_attacker.character_id)
							{
								Bob_attacker=Bob[i];
							}
						}
					}
				}
			}
			int id=Bob_attacker.character_id;
			Bob_attack(Bob_attacker);//放普攻
			if(gameover)
			{
				return 0;
			}
			Bob[id].mp=min(Bob[id].mp+1,Bob[id].MP);//普攻回能
			if(Bob[id].talent==5)//科技至上天赋回血
			{
				Bob[id].hp=min(Bob[id].hp+Bob[id].talent_x,Bob[id].HP);
			}
		}
		
		//Bob行动结束
		
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Bob[i].if_alive)
			{
				Bob[i].mp=min(Bob[i].mp+1,Bob[i].MP);
				if(Bob[i].talent==3)
				{
					Bob[i].hp=min(Bob[i].hp+Bob[i].talent_x,Bob[i].HP);
					Bob[i].mp=min(Bob[i].mp+Bob[i].talent_y,Bob[i].MP);
				}
				Bob[i].mp=min(Bob[i].mp+det_mp[Round][0],Bob[i].MP);
			}
		}
		
		//回合结算阶段
		
		for(int i=1;i<=Number_of_Player;i++)
		{
			if(Alice[i].if_alive)
			{
				Alice[i].det_def-=now_def[Round][1];
				Alice[i].det_atk-=now_atk[Round][1];
			}
			if(Bob[i].if_alive)
			{
				Bob[i].det_def-=now_def[Round][0];
				Bob[i].det_atk-=now_atk[Round][0];
			}
		}
		if(Round==end_round_by_skill_10)
		{
			if(who_used_skill_10==1)
			{
				Alice_Player=0;
			}
			else
			{
				Bob_player=0;
			}
		}
		if_gameover();
		if(gameover)
		{
			return 0;
		}
	}
	cout<<"Ciallo~"<<endl;											//如果超过最大回合，默认游戏无法结束，输出表情
	return 0;
	//至此，一锤定音
	//尘埃，已然落定
}
