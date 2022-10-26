//
// Created by L Su on 26/8/2022.
//

#include "karatsuba.h"
string karatsuba::addition(std::string str1, std::string str2, int base) {
    string addition_result="";

    reverse(str1.begin(),str1.end());
    int len1=str1.length();
    reverse(str2.begin(),str2.end());
    int len2=str2.length();

    int len=max(len1,len2);
    //两个n位数相加最多产生n+1位数的和，左边溢出的carry在后面处理

    int carry=0; //half adder没有carry

    for(int i=0;i<len;i++)
    {
        int a=0;//str1当前位的数字
        int b=0;//str2当前位的数字

        if(i<len1){
            a=str1[i]-'0';//从ASIIC对应回数字要-'0'
        }
        if(i<len2){
            b=str2[i]-'0';
        }

        int sum=a+b+carry;//str1和str2当前位相加后再加上进位

        carry=sum/base;//当前位向下一位的进位

        sum=sum%base;//当前位减去进位后的余数

        addition_result= to_string(sum)+addition_result;
    }
    //最左侧有进位溢出，把进位转成string后加上之前的string
    if(carry>0){
        addition_result= to_string(carry)+addition_result;
    }
    return addition_result;
    /*
     * len1=2,len2=1, len=2
     * 1st iteration:
     * 99+5  a=9 b=5,carry=0,=> sum=14, carry=1, sum=4, result="4"+""=4
     * 2nd iteration:
     * a=9,b="",carry=1 => sum=10,carry=1, sum=0, result="0"+"4"="04"
     * iterations end, remaining carry=1 >0
     * result="1"+"04"="104"
     */
}

string karatsuba::subtraction(std::string str1, std::string str2, int base) {
    string sub_result="";

    reverse(str1.begin(),str1.end());
    int len1=str1.length();
    reverse(str2.begin(),str2.end());
    int len2=str2.length();

    if(len1<len2){
        for(int i=0;i<len2-len1;i++){
            str1="0"+str1;
        }
    }else if(len2<len1){
        for(int i=0;i<len1-len2;i++){
            str2="0"+str2;
        }
    }

    int borrow=0;

    for(int i=0;i<len2;i++){

        int a=0;//str1当前位的数字
        int b=0;//str2当前位的数字


        a=str1[i]-'0';//从ASIIC对应回数字要-'0'
        b=str2[i]-'0';


        int sub=a-b-borrow;//当前digit相减的结果再减去前一位运算的借位carry

        if(sub<0){
            sub=sub+base;//不够减，借位
            borrow=1;//借位传递到下一位运算
        }else{
            borrow=0;//够减
        }

        sub_result= to_string(sub)+sub_result;
    }
    if(borrow>0){
        sub_result="-"+sub_result;
    }

    //reverse(sub_result.begin(),sub_result.end());
    return sub_result;

}
