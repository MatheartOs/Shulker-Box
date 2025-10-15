#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
#include <ctime>
#include <cmath>
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

//获取今天的 tm 结构（时分秒归零）
static tm getTodayTM() {
	time_t t = time(nullptr);
	tm local = *localtime(&t);
	local.tm_hour = local.tm_min = local.tm_sec = 0;
	return local;
}

static bool isLeapYear(int y) {
    return (y%4==0 && y%100!=0) || (y%400==0);
}

static int daysInMonth(int y, int m) {
    static const int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m==2 && isLeapYear(y)) return 29;
    return mdays[m];
}

struct Date {
    int y, m, d;
};

static Date getTodayDate() {
    time_t t = time(nullptr);
    tm lt = *localtime(&t);
    return { lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday };
}

static void nextDay(Date &date) {
    date.d++;
    if (date.d > daysInMonth(date.y, date.m)) {
        date.d = 1;
        date.m++;
        if (date.m > 12) {
            date.m = 1;
            date.y++;
        }
    }
}

int daysBetween(int targetY, int targetM, int targetD, char includeToday) {
    Date cur = getTodayDate();
    Date tgt = { targetY, targetM, targetD };

    bool swapped = false;
    if (  tgt.y < cur.y
       || (tgt.y==cur.y && tgt.m<cur.m)
       || (tgt.y==cur.y && tgt.m==cur.m && tgt.d<cur.d) )
    {
        std::swap(cur, tgt);
        swapped = true;
    }

    if (includeToday == 'N') {
        nextDay(cur);
    }

    int cnt = 0;

    while (true) {
        cnt++;
        if (cur.y==tgt.y && cur.m==tgt.m && cur.d==tgt.d) break;
        nextDay(cur);
    }

    return cnt;
}

int weeksBetween(int targetY, int targetM, int targetD,
	char includeThisWeek,
	int startWeekday)
{
	tm today = getTodayTM();
	tm t = {};
	t.tm_year = targetY - 1900;
	t.tm_mon  = targetM - 1;
	t.tm_mday = targetD;
	time_t tt  = mktime(&t);
	time_t now = mktime(&today);
	double diffSec = difftime(tt, now);
	int spanDays = static_cast<int>(std::floor(std::abs(diffSec) / 86400.0));

	int targetWeekIdx = (startWeekday + spanDays) / 7;

	int weeks = targetWeekIdx + 1;

	if (includeThisWeek == 'N') {
		weeks -= 1;
		if (weeks < 0) weeks = 0;
	}
	return weeks;
}

int count17s(int targetY, int targetM, int targetD) {
    Date cur = getTodayDate();
    Date tgt = { targetY, targetM, targetD };

    // 如果目标在今天之前，交换以保证向后遍历
    if (  tgt.y < cur.y
       || (tgt.y==cur.y && tgt.m<cur.m)
       || (tgt.y==cur.y && tgt.m==cur.m && tgt.d<cur.d) )
    {
        std::swap(cur, tgt);
    }

    int cnt = 0;
    // 每次 nextDay 之后检查是否 ==17，然后遇到目标日后 break
    while (true) {
        nextDay(cur);
        if (cur.d == 17) {
            cnt++;
        }
        if (cur.y==tgt.y && cur.m==tgt.m && cur.d==tgt.d) {
            break;
        }
    }
    return cnt;
}

int monthsBetween(int targetY, int targetM, int targetD, char includeThisMonth) {
	tm today = getTodayTM();
	int curY = today.tm_year + 1900;
	int curM = today.tm_mon + 1;

	int delta = std::abs((targetY - curY) * 12 + (targetM - curM));

	int months = delta + 1;

	if (includeThisMonth == 'N') {
		months -= 1;
		if (months < 0) months = 0;
	}
	return months;
}

double yuanshi;
double hechengyu;
double shichou;
double danchou;
int yueka_restDay;
int special_yueka_restDay;
int weekDay;
char opt1;
char opt2;
char opt3;
char opt4;
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
	cin>>weekDay;
	cin>>opt1;
	cin>>opt2;
	cin>>opt3;
	cin>>opt4;


	cout<<"计算截止到哪个池子？(1:周年池 2:半周年池 3:夏活池 4:年限池): ";
	int which;
	cin >> which;
	int year;
	int month;
	int day;
	while (which != 1 && which != 2 && which != 3 && which != 4)
	{
		cout<<"听不懂你在说什么，重新选。"<<endl;
		cout<<"计算截止到哪个池子？(1:周年池 2:半周年池 3:夏活池 4:年限池): ";
		cin >> which;
	}
	cout<<which<<endl;
	switch (which)
	{
	case 1:
		year = 2026;
		month = 5;
		day = 1;
		break;
	case 2:
		year = 2025;
		month = 11;
		day = 1;
		break;
	case 3:
		year = 2025;
		month = 8;
		day = 1;
		break;
	case 4:
		year = 2026;
		month = 2;
		day = 10;
		break;
	}
	
	int moreHechengyu = 0;
	int moreYuanshi = 0;
	int moreShichou = 0;
	int moreDanchou = 0;

	int pastDays = daysBetween(year,month,day,opt1);
	int pastWeeks = weeksBetween(year,month,day,opt2,weekDay);
	int pastMonths = monthsBetween(year,month,day,opt3);
	int past17s = count17s(year,month,day);

	moreHechengyu = pastDays*100 + pastWeeks*(500+1800);
	moreYuanshi = pastMonths*42;
	moreShichou = pastMonths*1;
	moreDanchou = past17s*1;
	
	cout<<"你的目标是 "<< target    <<" 井\n";
	cout<<"你还剩下 "<< yuanshi   <<" 颗源石\n";
	yuanshi += moreYuanshi;
	cout<<"你还剩下 "<< hechengyu <<" 合成玉\n";
	hechengyu += moreHechengyu;
	cout<<"你还剩下 "<< shichou   <<" 张十连券\n";
	shichou += moreShichou;
	cout<<"你还剩下 "<< danchou   <<" 张单抽券\n";
	danchou += moreDanchou;
	cout<<"你的月卡还剩下 "<< yueka_restDay<<" 天\n";
	cout<<"你的特殊月卡还剩下 "<< special_yueka_restDay<<" 天\n\n";

	cout<<"截止 " <<year<<" 年 " <<month<<" 月 "<<day<<" 日:"<<endl;
	cout<<"期间一共经历 "<<pastDays<<" 天，"<<pastWeeks<<" 周，"<<pastMonths<<" 月。"<<endl;
	cout<<"如果你能做到天天全勤（每日100合成玉），周周全勤（每周500(任务)+1800(剿灭)合成玉，月月全勤（每月17日1单抽券+大月卡每月10连券+42源石），"<<endl;
	cout<<"那么从今天到截至日期，你还能攒："<<endl;
	cout<<moreYuanshi<<" 源石。"<<endl;
	cout<<moreHechengyu<<" 合成玉。"<<endl;
	cout<<moreShichou<<" 十连券。"<<endl;
	cout<<moreDanchou<<" 单抽券。"<<endl;
	if(opt4 == 'Y'){
		cout<<"根据你给出的信息，你能做到小月卡全勤，因此还能额外获得 "<<(pastDays)*200<<" 合成玉。"<<endl;
		moreHechengyu += (pastDays)*200;
		hechengyu += (pastDays)*200;
	}else{
		if(pastDays <= yueka_restDay){
			cout<<"根据你给出的信息，你不能做到小月卡全勤，但是你现有的月卡时间已经足够领到卡池开始，因此可以等效为小月卡全勤("<<endl;
			cout<<"因此还能额外获得 "<<(pastDays)*200<<" 合成玉。"<<endl;
			moreHechengyu += (pastDays)*200;
			hechengyu += (pastDays)*200;
		}else{
			cout<<"根据你给出的信息，你不能做到小月卡全勤，"<<endl;
			cout<<"因此还能额外获得 "<<(yueka_restDay)*200<<" 合成玉。"<<endl;
			moreHechengyu += (yueka_restDay)*200;
			hechengyu += (yueka_restDay)*200;
		}
	}
	cout<<"折合为："<<(int)((moreYuanshi/(10.0/3.0))+(moreHechengyu/600.0)+moreShichou*10+moreDanchou*1)<<" 抽（向下取整）"<<endl;

	
	double sum = yuanshi/(10.0/3.0) + hechengyu/600.0 + shichou*10 + danchou + yueka_restDay/3.0 + special_yueka_restDay/3.0;
	double needed = 1.0*target - sum;
	//needed = 201;
	cout<<"你一共能抽："<<(long long)(sum)<<" 抽"<<endl<<endl;
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

