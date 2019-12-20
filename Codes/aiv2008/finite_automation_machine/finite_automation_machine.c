#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 1000


unsigned int status[MAXSIZE][26];

void computeTransitionFunction(char *p)      //O(  m^3|Σ| )  可改进到O(  m|Σ| )
{    //通过定义直接计算转换函数  一共有4层循环，所有看上去代价很大，，
    int m=strlen(p);
    int q;
    for(q=0;q!=m+1;++q){  //从状态0开始计算 一共0-m个状态m+1次
	int j;
	for(j=0;j!=26;++j){ //26个字符 每个都要试Σ次
		int k=min(m,q+1);       // 求 δ(q,a)的值， 它最大值为 min(m,q+1)
		printf("j=%d, m=%d, q+1=%d, k=%d\n",j, m, q+1, k);
		while(k!=0){   //最多减小到0  返回状态0  最多m+1次
			int i;
			for(i=k;i!=0;--i){   //逐个查看 P[1..k]是否满足要求 是 P[1...q]a 这个字符串的后缀m次
				if(i==k){         //p[k]要与a比较
					if(p[i-1]==(char)(j+97)){ //相等继续
						continue;
					}else {//否则 这个k不符合要求
						break;
					}
				} else{ //继续比较P[1..k-1]和P[1..q]
		        		if(p[i-1]==p[q-(k-i)])continue;
		        		else break;
		    		}
			}//for
			//如果i减小到了0 则说明这个k符合要求，
			if(i==0){ 
				status[q][j]=k;break;
			} //赋值
			else { //否则减小k
				--k;
			}
    		}//while
        }
    }
}

void finiteAutomationMachine(char *s, int m) {
	int n =strlen(s);
	int q = 0;
	int i;
	for(i=0;i!=n;++i) {
		q = status[q][(int)(s[i]-97)];
		//printf("%c,%d\n",s[i], q);
		if(q == m) {
			printf("index of s is %d\n", i - m + 1);
		}
	}
}

int min(int a, int b) {
	return a < b ? a : b;
}

int main(){
 
char *s="fsdfsadsadfadsffsdfsadsadfadsf";
char *p="fsdfsadsadfadsf";//模式P
  
computeTransitionFunction(p);
finiteAutomationMachine(s,strlen(p));
 
return 0;
}

