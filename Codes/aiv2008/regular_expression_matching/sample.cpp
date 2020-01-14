#include<iostream>

using namespace std;

class Solution {
private:
    enum STATUS{ END = 0, START, SIGNED1, INTEGER, POINT, FLOAT, EXPONENT, SIGNED2, SCIENCE };
    //STATUS dfa[256][9] = { {END} };
public:  
    STATUS dfa[256][9] = { {END} };
    Solution(){
        for (int i = 0; i < 256; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                dfa[i][j] = END;
            }
        }
        initDFA();
    }
    bool isNumeric(char* string)
    {
        STATUS current = START;
        while (*string && current != END)
        {
            current = DFA(current, *string);
            ++string;
        }
        switch (current)
        {
        case INTEGER:
        case FLOAT:
        case SCIENCE:
            return true;
        }
        return false;
    }
	
private:
    void initDFA(){
        char d = '0';
        // 1. START 变迁
        dfa['+'][START] = SIGNED1;
        dfa['-'][START] = SIGNED1;
        dfa['.'][START] = POINT;
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][START] = INTEGER;
        }
 
        // 2. SIGNED1 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][SIGNED1] = INTEGER;
        }
        dfa['.'][SIGNED1] = POINT;
 
        // 3. INTEGER 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][INTEGER] = INTEGER;
        }
        dfa['.'][INTEGER] = FLOAT;
        dfa['E'][INTEGER] = EXPONENT;
        dfa['e'][INTEGER] = EXPONENT;
 
        // 4. POINT 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][POINT] = FLOAT;
        }
 
        // 5. FLOAT 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][FLOAT] = FLOAT;
        }
        dfa['E'][FLOAT] = EXPONENT;
        dfa['e'][FLOAT] = EXPONENT;
 
        // 6. EXPONENT 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][EXPONENT] = SCIENCE;
        }
        dfa['+'][EXPONENT] = SIGNED2;
        dfa['-'][EXPONENT] = SIGNED2;
 
        // 7. SIGNED2 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][SIGNED2] = SCIENCE;
        }
 
        // 8. SCIENCE 变迁
        for (d = '0'; d <= '9'; ++d)
        {
            dfa[d][SCIENCE] = SCIENCE;
        }
 
        // 其余情况均变迁到  END
 
    }
 
    STATUS DFA(STATUS current, char input)
    {
        STATUS ret = START;
        return dfa[input][current];
    }
     
 
};


	int main() {
		Solution *solution = new Solution();
		int rowSize = 256;
		int colSize = 9;
		int i;
		for(i=0;i<rowSize;i++) {
			int j;
			for(j=0;j<colSize;j++) {
				cout<< solution->dfa[i][j];
				cout<<",";
			}
			cout<<endl;
		}	
    	bool b = solution->isNumeric("12e");
		cout<<"result is :";
		cout<<b<<endl;
		return 0;
	}
