//
// Created by L Su on 17/8/2022.
//
/*
You must follow this guideline! Your submission will be marked automatically. Failure to
follow this guideline will result in 0.
Your submission should contain exactly one file: main.cpp. You do not need to submit a design.
Your program takes one line as input.
The input line contains three integers separated by spaces. Let
the three integers be I1, I2, and B. I1 and I2 are both nonnegative integers up to 100 digits long (there are
no leading 0s, except when the value itself is 0). B is I1 and I2’s base (B is from 2 to 10).1
Your program should output the sum of I1 and I2, using the school method, then the product of I1 and
I2, using the Karatsuba algorithm, and finally the ratio between I1 and I2 (rounded down). You are asked
to come up with a way to perform this division. It’s not covered in lectures. I2 will not be 0.
The results should still use base B. Please separate the results using one space.
Sample input 1: 101 5 10
Sample output 1: 106 505 20
Sample input 2: 10 111 2
Sample output 2: 1001 1110 0
Sample input 3: 111 10 2
Sample output 2: 1001 1110 11
If you are an undergraduate student, simply output 0 as the division result. For sample 3, instead of
1001 1110 11, simply output 1001 1110 0
 */
#include <iostream>
#include<string>
#include<vector>

using namespace std;

string removeZero(string str){
   str.erase(0, str.find_first_not_of('0'));
   return str;
}

string addition(string I1, string I2, int B)
{
    int len1 = I1.length();
    int len2 = I2.length();
    int len = max(len1, len2);
    string result = "";
    int carry = 0; //第一位carry为0
    for (int i = 0; i < len; i++)
    {
        int a = 0;
        int b = 0;
        if (i < len1) //a是I1从右向左的每一位的数字
            a = I1[len1 - 1 - i] - '0';//ASIIC中对应回数字要-'0'

       
        if (i < len2)
            b = I2[len2 - 1 - i] - '0';//b是I2从右向左的每一位的数字

        int sum = a + b + carry;
        carry = sum / B; //计算向左进位
        sum = sum % B; //计算本位数字
        result = to_string(sum) + result; //本位数字字符串+右侧数字位字符串： 3+9="2"+""； carry="1"
    }
    if (carry > 0)
        result = to_string(carry) + result;//结合最左侧进位 3+9="1"+"2"
    return result;

}

string multiplication(string I1, string I2, int B)
{
    int len1 = I1.size();
    int len2 = I2.size();
    if (len1 == 0 || len2 == 0)
        return "0";

    //初始化长度为len1+len2的全0向量
    vector<int> vec(len1 + len2, 0);

    //追踪result位置
    int i_n1 = 0;
    int i_n2 = 0;

    //从右向左遍历I1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = I1[i] - '0';//I1当前位数
        //cout<<"n1 is: "<<n1<<endl;


        //I1和I2的每一位数乘后向左移
        i_n2 = 0;

        // 从右向左遍历I2
        for (int j=len2-1; j>=0; j--)
        {

            int n2 = I2[j] - '0';//I2当前位数
            //cout<<"n2 is: "<<n2<<endl;

            // I1和I2当前位数相乘，再加上之前的结果，再加carry
            int sum = n1*n2 + vec[i_n1 + i_n2] + carry;
            //cout<<"sum is: "<<sum<<endl;


            carry = sum/B;//计算进位，下一iteration用
            //cout<<"carry is: "<<carry<<endl;

            vec[i_n1 + i_n2] = sum % B;//存储结果去vector result
            //cout<<"result is: "<<result[i_n1+i_n2]<<endl;

            i_n2++;
        }


        if (carry > 0)
            vec[i_n1 + i_n2] += carry;

        //向左移动
        i_n1++;
    }

    // 忽略右侧的0，因为之后是反过来的
    int i = vec.size() - 1;
//    while (i>=0 && result[i] == 0)
//        i--;
//
//    //如果一直都是0，那乘数中必有一个是0
//    if (i == -1)
//        return "0";


    string result = "";

    while (i >= 0)
        result += to_string(vec[i--]);//反过来的 i--

    // //remove leading 0
    // const regex pattern("^0+(?!$)");
    // result = regex_replace(result, pattern, "");
  

    return removeZero(result);

}

string subtraction(string I1, string I2,int B)
{

    string result = "";

    int len1 = I1.length();
    int len2 = I2.length();

    // 反转字符串
    reverse(I1.begin(), I1.end());
    reverse(I2.begin(), I2.end());

    int carry = 0;

    // Run loop till small string length
    // and subtract digit of str1 to str2
    for (int i = 0; i < len2; i++) {

        //当前位置的减法结果
        int sub = ((I1[i] - '0')- (I2[i] - '0')- carry);

        // If subtraction < 0 then add 10
        // into sub and take carry as 1
        if (sub < 0) {
            sub = sub + B;
            carry = 1;
        }
        else
            carry = 0;

        result.push_back(sub + '0');
    }

    // Subtract the remaining digits of
    // larger number
    for (int i = len2; i < len1; i++) {
        int sub = ((I1[i] - '0') - carry);

        // If the sub value is -ve,
        // then make it positive
        if (sub < 0) {
            sub = sub + B;
            carry = 1;
        }
        else
            carry = 0;

        result.push_back(sub + '0');
    }


   //倒转string
    reverse(result.begin(), result.end());

    //remove leading 0
  
    
    cout<<"减法结果： "<<removeZero(result)<<endl;

    return removeZero(result);
}

string Karatsuba(string I1,string I2,int B){
    if (I1.length() > I2.length())
        swap(I1, I2);

    //变一样长
    int len1 = I1.length(), len2 = I2.length();
    while (len2 > len1) {
        I1 = "0" + I1; //把短的string左边加"0"变长
        len1++;
    }

    // Base case
    if (len1 == 1) {

       //一位数直接乘
        int result = stoi(I1) * stoi(I2);
        return to_string(result);
    }

    //位数是奇数的话前面加0变偶数
    if (len1 % 2 == 1) {
        len1++;
        I1 = "0" + I1;
        I2 = "0" + I2;
    }

    string Al, Ar, Bl, Br;

    //字符串拆开
    for (int i = 0; i < len1 / 2; ++i) {
        Al += I1[i];
        Bl += I2[i];
        Ar += I1[len1 / 2 + i];
        Br += I2[len1 / 2 + i];
    }

    //递归call

    //  Al * Bl相乘
    string p = multiplication(Al, Bl, B);

    // Ar * Br相乘
    string q = multiplication(Ar, Br, B);

    // ((Al + Ar)*(Bl + Br)- Al*Bl - Ar*Br
    string r = subtraction(
            multiplication(addition(Al, Ar,B),
                            addition(Bl, Br,B),
                                B),
            addition(p, q,B),
            B);

    // p*(10^n)
    for (int i = 0; i < len1; ++i)
        p = p + "0";

    // s* 10^(n/2)
    for (int i = 0; i < len1 / 2; ++i)
        r = r + "0";

    //计算 p + r + s
    string result = addition(p, addition(q, r,B),B);

    // // Remove leading zeroes
    // const regex pattern("^0+(?!$)");
    // result= regex_replace(result, pattern, "");

    return removeZero(result);



}

int main(){
    string I1,I2;
    int B;
    cin>>I1>>I2>>B;
    cout<<addition(I1,I2,B)<<" ";
    if(I1.size()<4&&I2.size()<4){
        cout<<multiplication(I1,I2,B)<<" ";
    }else{
        cout<<Karatsuba(I1,I2,B)<<" ";
    }
    cout<<"0";
    cout<<subtraction(I1,I2,B)<<endl;



    return 0;
}