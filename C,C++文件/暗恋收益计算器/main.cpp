#include <bits/stdc++.h>
using namespace std;

double p1,p2,p3,p4,k1,k2,a,b;

double youGet,taGet;

int main(){
    cout<<"使用前须知："<<endl;
    cout<<"本程序虽然仅供娱乐，但是是基于严谨数学模型编写。"<<endl;
    cout<<"因此本程序的计算结果可能并非乐观。"<<endl;
    cout<<"但是请记住：相信自己的选择永远最重要的。"<<endl;
    string flag;
    do {
        cout << "如果你已经充分考虑，请确认是否开始计算(y/n)：";
        cin >> flag;
    } while(flag != "y" && flag != "n");
    if(flag == "n"){
        return 0;
    }
    cout<<endl;
    do {
        cout << "你认为ta喜欢你的概率有多大？(0~1)：";
        cin >> p1;
    } while (p1 < 0 || p1 > 1);
    
    do {
        cout << "你认为ta被喜欢的人表白后同意的概率多大？(0~1)：";
        cin >> p3;
    } while (p3 < 0 || p3 > 1);
    
    do {
        cout << "你认为ta被不喜欢的人表白后同意的概率多大？(0~1)：";
        cin >> p4;
    } while (p4 < 0 || p4 > 1);
    
    do {
        cout << "你有多渴望爱情？(0~1)：";
        cin >> a;
    } while (a < 0 || a > 1);
    
    do {
        cout << "ta有多渴望爱情？(0~1)：";
        cin >> b;
    } while (b < 0 || b > 1);
    
    do {
        cout << "你面对重要事情时的情绪波动有多强烈？(1~5)：";
        cin >> k1;
    } while (k1 < 1 || k1 > 5);
    
    do {
        cout << "ta面对重要事情时的情绪波动有多强烈？(1~5)：";
        cin >> k2;
    } while (k2 < 1 || k2 > 5);
    
    do {
        cout << "你的主动性有多强？(0~1)：";
        cin >> p2;
    } while (p2 < 0 || p2 > 1);

    youGet = p1*p2*p3*k1*a+p1*p2*(1.0-p3)*(-1.0*k1*a)+p1*(1.0-p2)*(-1.0*a)+(1.0-p1)*(1.0-p2)*(-1.0*a)+(1.0-p1)*p2*p4*(0.5*k1*a)+(1.0-p1)*p2*(1.0-p4)*(-2.0*k1*a);
    taGet  = p1*p2*p3*k2*b+p1*p2*(1.0-p3)*(-1.0*k2*b)+p1*(1.0-p2)*(-1.0*b)+(1.0-p1)*(1.0-p2)*(-1.0*0)+(1.0-p1)*p2*p4*(-2.0*k2*b)+(1.0-p1)*p2*(1.0-p4)*(0);

    double ansYou = ((youGet)) * 20;
    double ansTa = ((taGet)) * 20;
    cout<<fixed<<setprecision(2)<<showpoint;
    cout<<endl<<"根据你提供的信息，你在暗恋ta后获得的收益为："<<ansYou<<endl;
    cout<<"而ta获得的收益为："<<ansTa<<endl;

    if(ansYou < 0 && ansTa < 0){
        cout<<"暗恋对你和ta来说或许都很痛苦吧..."<<endl;
        cout<<"如果强行下去，只会双双受伤..."<<endl;
        cout<<"与其这样，不如早日结束苦痛。"<<endl;
    }

    if(ansYou < 0 && ansTa > 0){
        cout<<"很遗憾...你的暗恋或许终将是黄粱一梦。"<<endl;
        cout<<"宛如一场无人知晓的盛宴，一场孤独的自我对白..."<<endl;
        cout<<"放弃吧。"<<endl;
    }

    if(ansYou > 0 && ansTa > 0){
        cout<<"恭喜你，暗恋对于你和ta来说就像是爱情的序章"<<endl;
        cout<<"虽然跌宕起伏，但美好的结局早已注定。"<<endl;
    }

    if(ansYou > 0 && ansTa < 0){
        cout<<"虽然这场暗恋对你来说收益显著，但是从ta的收益来看，似乎快乐并没有站在ta那一边"<<endl;
        cout<<"是否三思？"<<endl;
    }
}