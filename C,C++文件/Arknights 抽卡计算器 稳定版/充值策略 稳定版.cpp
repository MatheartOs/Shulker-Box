#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
using namespace std;

//对应6元、30元、98元、198元、328元、648元档位
int cnt[6] = {0, 0, 0, 0, 0, 0};

struct Recharge {
	int cost;         // 充值金额
	int rewardNormal; // 普通奖励
	int rewardBonus;  // 首充奖励
};

// 充值档位信息
// 第一列是充值金额 第二列是普通奖励 第三列是首充奖励
// 如果某个首充已经被使用过了，直接把第三列中的首充奖励换成普通奖励就行
Recharge coins[6] = {
	{6,   1,  3},
	{30,  7,  7},
	{98,  24, 40},
	{198, 50, 50},
	{328, 90, 90},
	{648, 185,185}
};

struct DPState {
	int cost;
	int prevReward;
	int coinUsed;
};

const int INF = INT_MAX / 2;

vector<DPState> computeDP(int R_MAX) {
	vector<DPState> dp(R_MAX+1, {INF, -1, -1});
	dp[0] = {0, -1, -1};
	for (int r = 0; r <= R_MAX; r++) {
		if(dp[r].cost == INF) continue;
		for (int i = 0; i < 6; i++) {
			int newR = r + coins[i].rewardNormal;
			if(newR > R_MAX) newR = R_MAX;
			if(dp[r].cost + coins[i].cost < dp[newR].cost) {
				dp[newR].cost = dp[r].cost + coins[i].cost;
				dp[newR].prevReward = r;
				dp[newR].coinUsed = i;
			}
		}
	}
	return dp;
}

int Kejin(int need) {
	int R_MAX = need + 185;
	vector<DPState> dp = computeDP(R_MAX);

	int bestTotalCost = INF;
	int bestTotalReward = 0;
	int bestBonusMask = 0;
	int bestNormalRewardAchieved = 0;

	for (int mask = 0; mask < (1 << 6); mask++) {
		int bonusReward = 0, bonusCost = 0;
		for (int i = 0; i < 6; i++) {
			if(mask & (1 << i)) {
				bonusReward += coins[i].rewardBonus;
				bonusCost += coins[i].cost;
			}
		}
		int remaining = (need - bonusReward) > 0 ? (need - bonusReward) : 0;
		int normalCost = INF;
		int achievedReward = -1;
		for (int r = remaining; r <= R_MAX; r++) {
			if(dp[r].cost < normalCost) {
				normalCost = dp[r].cost;
				achievedReward = r;
			}
		}
		if(normalCost == INF) continue;
		int totalCost = bonusCost + normalCost;
		int totalReward = bonusReward + achievedReward;
		if(totalCost < bestTotalCost) {
			bestTotalCost = totalCost;
			bestTotalReward = totalReward;
			bestBonusMask = mask;
			bestNormalRewardAchieved = achievedReward;
		}
	}

	if(bestTotalCost == INF) return -1;

	for (int i = 0; i < 6; i++) cnt[i] = 0;

	for (int i = 0; i < 6; i++) {
		if(bestBonusMask & (1 << i))
			cnt[i]++;
	}
	
	int r = bestNormalRewardAchieved;
	vector<int> normalCount(6, 0);
	while(r > 0) {
		int coin = dp[r].coinUsed;
		normalCount[coin]++;
		r = dp[r].prevReward;
	}

	for (int i = 0; i < 6; i++) {
		cnt[i] += normalCount[i];
	}

	ostringstream oss;
	bool first = true;
	for (int i = 0; i < 6; i++) {
		if(bestBonusMask & (1 << i)) {
			if(!first) oss << "+";
			oss << coins[i].rewardBonus;
			first = false;
			for (int j = 0; j < cnt[i]-1; j++) {
				oss << "+" << coins[i].rewardNormal;
			}
		} else {
			for (int j = 0; j < cnt[i]; j++) {
				if(!first) oss << "+";
				oss << coins[i].rewardNormal;
				first = false;
			}
		}
	}
	oss << "=" << bestTotalReward;
	
	cout <<"最少还需要氪 "<< bestTotalCost << " 元\n对应获得源石数量和各档位充值次数如下：\n" << oss.str() << "\n";
	
	return bestTotalCost;
}
double yuanshi;
double hechengyu;
double shichou;
double danchou;
int yueka_restDay;
int special_yueka_restDay;
int main(){
	
	freopen("info.txt","r",stdin);
	
	int target;
	cin>>target;
	cin>>yuanshi;
	cin>>hechengyu;
	cin>>shichou;
	cin>>danchou;
	cin>>yueka_restDay;
	cin>>special_yueka_restDay;
	
	cout<<"你的目标是 "<< target    <<" 井\n";
	cout<<"你还剩下 "<< yuanshi   <<" 颗源石\n";
	cout<<"你还剩下 "<< hechengyu <<" 合成玉\n";
	cout<<"你还剩下 "<< shichou   <<" 张十连券\n";
	cout<<"你还剩下 "<< danchou   <<" 张单抽券\n";
	cout<<"你的月卡还剩下 "<< yueka_restDay<<" 天\n";
	cout<<"你的特殊月卡还剩下 "<< special_yueka_restDay<<" 天\n\n";
	
	double sum = yuanshi/(10.0/3.0) + hechengyu/600.0 + shichou*10 + danchou + yueka_restDay/3.0 + special_yueka_restDay/3.0;
	double needed = 1.0*target - sum;
	//needed = 201;
	cout<<"你一共能抽："<<(long long)(sum)<<" 抽"<<endl;
	if(needed <= 0){
		cout<<"恭喜你攒够了！你一分钱不用花。";
		return 0;
	}
	double more_yuanshi_needed = needed*10.0/3.0;
	
	int INT_yuanshi = (int)more_yuanshi_needed;
	if(more_yuanshi_needed > INT_yuanshi) INT_yuanshi++;
	
	printf("你还需要 %d 颗源石\n",INT_yuanshi);

	Kejin(INT_yuanshi);
	cout<<fixed<<"6元：  "<<cnt[0]<<"次\n";
	cout<<"30元： "<<cnt[1]<<"次\n";
	cout<<"98元： "<<cnt[2]<<"次\n";
	cout<<"198元："<<cnt[3]<<"次\n";
	cout<<"328元："<<cnt[4]<<"次\n";
	cout<<"648元："<<cnt[5]<<"次\n";
	return 0;
}
