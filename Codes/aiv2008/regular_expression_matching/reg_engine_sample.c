#include <stdio.h>
#include <string.h>
#include <malloc.h>
//这里只处理最简单的正则表达式，即包括括号，星号运算，连接运算和分支运算，这里分支运算在压栈是是一个点号
//其中括号优先级最大，其次是星号运算其次是连接运算最后是分支运算
//当前版本只是把一个简单的正则表达式的优先级理清
#define STRICT
//strict 的意思就是不要求显示的写出.运算符 ，因为在缺少这个运算符的情况下，我们还是可以推断出来这个
//运算符是存在的 ，例如 在）及 *及非运算符之后如果存在字母则是缺少连接符，我们可以自己加上去
int is_operator(char for_in)
{
    switch(for_in)
    {
    case'(':
    case')':
    case'.':
    case'*':
    case'|':
         return 1;
    default: return 0;
    }
}
int main(void)
{
    int token[100];
    int token_pointer;
    char reg_operator[100];
    int reg_operator_pointer;
    int name_number;
    int input_pointer;
    char reg_input[20];
    reg_operator_pointer=name_number=token_pointer=0;
    for(input_pointer=0;input_pointer<100;input_pointer++)//初始化堆栈 
    {
        reg_operator[input_pointer]='\0';
        token[input_pointer]=0;
    }
    input_pointer=0;
    printf("please  type in you regex short phrase\n");
    scanf("%s",reg_input);
    while(*(reg_input+input_pointer)!='\0')
    {
        if(!is_operator(*(reg_input+input_pointer)))
        {
            name_number++;
            token[token_pointer++]=name_number;
            printf("name%d is %c\n",name_number,*(reg_input+input_pointer));
            input_pointer++;
#ifndef STRICT
            if(!is_operator(*(reg_input+input_pointer)))
            {
                reg_operator[reg_operator_pointer++]='.';
            }
            else
            {
                if(*(reg_input+input_pointer)=='(')
                {
                    reg_operator[reg_operator_pointer++]='.';
                }
            }
#endif 

        }
        else//如果是操作符
        {
            if(reg_operator_pointer!=0)//如果当前栈中有操作符，则需要考虑不同操作符的优先级了
            {
                switch(*(reg_input+input_pointer))
                {
                case '('://括号直接入栈，不需要其他操作
                    reg_operator[reg_operator_pointer++]='(';
                    input_pointer++;
                    break;
                case ')':
                    if(reg_operator[reg_operator_pointer-1]=='(')
                    //如果两个括号匹配，则从操作符和运算数栈中分别弹出一个，然后再生成另外一个运算数入栈
                    {
                        name_number++;
                        printf("name%d is (name%d)\n",name_number,token[token_pointer-1]);
                        token[token_pointer-1]=name_number;
                        reg_operator_pointer--;//弹出匹配的括号
                        input_pointer++;
#ifndef STRICT
                        if(!is_operator(*(reg_input+input_pointer)))
                        {
                            reg_operator[reg_operator_pointer++]='.';
                        }
                        else
                        {
                            if(*(reg_input+input_pointer)=='(')
                            {
                                reg_operator[reg_operator_pointer++]='.';
                            }
                        }
#endif
                        break;
                    }
                    else//如果前面还有运算符，只有可能是连接和选择运算符
                    {
                        //对于这两种运算符，处理都是差不多的，不过还要考虑括号内有多个运算符的情况
                        //这时根据优先级只有可能是| .，不过第二个运算符我们留到第二次迭代的时候去处理
                        if(reg_operator[reg_operator_pointer-1]=='.')
                        {
                            name_number++;
                            printf("name%d is concat of name%d and name%d\n",name_number,token[token_pointer-1],token[token_pointer-2]);
                            token[token_pointer-2]=name_number;
                            token[token_pointer-1]=0;
                            token_pointer--;
                            reg_operator_pointer--;
                            reg_operator[reg_operator_pointer]='\0';
                            break;
                        }
                        else
                        {
                            name_number++;
                            printf("name%d is  name%d or name%d\n",name_number,token[token_pointer-1],token[token_pointer-2]);
                            token[token_pointer-2]=name_number;
                            token[token_pointer-1]=0;
                            token_pointer--;
                            reg_operator_pointer--;
                            reg_operator[reg_operator_pointer]='\0';
                            break;
                        }
                        
                    }
                case '*':
                    //这个运算符优先级基本上是最高的，因此不需要入栈了，直接处理
                    name_number++;
                    printf("name%d is multiple of name%d\n",name_number,token[token_pointer-1]);
                    token[token_pointer-1]=name_number;
                    input_pointer++;
#ifndef STRICT
                    if(!is_operator(*(reg_input+input_pointer)))
                    {
                        reg_operator[reg_operator_pointer++]='.';
                    }
                    else
                    {
                        if(*(reg_input+input_pointer)=='(')
                        {
                            reg_operator[reg_operator_pointer++]='.';
                        }
                    }
#endif

                    break;
                case '.':
                    //由于*运算符已经被直接处理了，所以只需要考虑其他的三个运算符
                    if(reg_operator[reg_operator_pointer-1]=='.')
                        //如果前面的那个运算符跟当前优先级相同，则处理前面的那个运算符
                        //这时字符栈要减一
                    {
                        name_number++;
                        printf("name%d is concat of name%d and name%d\n",name_number,token[token_pointer-2],token[token_pointer-1]);
                        token[token_pointer-2]=name_number;
                        token_pointer--;
                        reg_operator[reg_operator_pointer-1]='.';
                        input_pointer++;
                        break;
                    }
                    else
                        //其他情况则直接入栈就行，留到下次来判断优先级处理
                    {
                        reg_operator[reg_operator_pointer++]='.';
                        input_pointer++;
                        break;
                    }
                case '|':
                    if(reg_operator[reg_operator_pointer-1]!='(')//括号另外说
                    {
                        name_number++;
                        if(reg_operator[reg_operator_pointer-1]=='.')
                            //如果前面的优先级比当前的高，则处理前面的优先级
                        {
                            printf("name%d is concat of name%d and name%d\n",name_number,token[token_pointer-2],token[token_pointer-1]);
                        }
                        else
                            //这里处理的是相同优先级的情况，其实这里可以与前面的合并的，只不过打印信息不同
                        {
                            printf("name%d is  name%d or name%d\n",name_number,token[token_pointer-2],token[token_pointer-1]);
                        }
                        token[token_pointer-2]=name_number;
                        token_pointer--;
                        reg_operator[reg_operator_pointer-1]='|';
                        input_pointer++;
                        break;
                    }
                    else
                    {
                        reg_operator[reg_operator_pointer++]='|';
                        input_pointer++;
                        break;
                    }
                default: 
                    printf("error\n");
                    break;
                }
            }
            else//在当前操作符栈中没有符号的时候
            {
                if(reg_input[input_pointer]!='*')
                    //由于*优先级最高，而且是左结合的，所以不需要入栈了
                    //对于其他的操作符则需要入栈
                {
                    reg_operator[reg_operator_pointer++]=reg_input[input_pointer++];
#ifndef STRICT
                    if(!is_operator(*(reg_input+input_pointer)))
                    {
                        reg_operator[reg_operator_pointer++]='.';
                    }
                    else
                    {
                        if(*(reg_input+input_pointer)=='(')
                        {
                            reg_operator[reg_operator_pointer++]='.';
                        }
                    }
#endif

                }
                else
                {
                    name_number++;
                    printf("name%d is the multiple of name%d\n",name_number,token[token_pointer-1]);
                    token[token_pointer-1]=name_number;
                    input_pointer++;
                }
            }
        }
    }
    if(reg_operator_pointer==1)//如果全部的输入都弄完了，可是 操作符栈中还有数据，则输出 
    {
        if(reg_operator[reg_operator_pointer]=='.')
        {
            name_number++;
            printf("name%d is cancat of name%d and name%d\n",reg_operator[0],token[0],token[1]);
        }
        else
        {
            name_number++;
            printf("name%d is name%d or name%d\n",reg_operator[0],token[0],token[1]);
        }
    }
}
