
/*
Hash table with linear probing
The keys are lower-case English words 
A table slot has three different statuses: “never used”, “tombstone”, and “occupied”. Table starts with
26 “never used” slots.

Sample input 1: Aaaa Accc Abbb
Sample output 1: aaa bbb ccc
Sample input 2: Abba Aaaa Acca
Sample output 2: bba aaa cca
Sample input 3: Abba Aaaa Acca Daaa
Sample output 3: bba cca
*/
#include<iostream>
#include<string>
#include<cstring> 
using namespace std;
//a class for each slot in the hash table
class TableSlot{
public:
    string value;//the value of the slot
    string status;//occupied, tombstone, or never used
};

//class for hash table
class HashTable{
public:
    HashTable();

    HashTable(string input){
        int i, k;
        char val[20];

        for (i = 0; i < 26; i++)
        {
                    table[i].status = "never used";//initialize the table each slot to "never used"
        }

        for (i = 0, k = 0; i <= input.length(); i++)
        {//读入字符串，每次读入一个单词
            if (input[i] == ' ' || input[i] == '\0')
            {
                        val[k] = '\0';//每次读入一个单词后，将单词的最后一个字符设为'\0'

                append(val);//将单词插入到哈希表中
                k = 0;//将k置为0，准备读入下一个单词
            }
            else
            {
                        val[k++] = input[i];//将单词的每个字符读入val数组中
                      //  cout <<k<<" "<< val[k - 1]<<endl;
            }
        }

    };

    void append(const char str[]){
        int len = strlen(str);//计算单词的长度
        if (len <= 1) return;//如果单词为空或者长度为1，则不插入哈希表中
        char opt = str[0];//取单词的第一个字符作为操作符
        char key = str[len - 1];//取单词的最后一个字符作为哈希表的键值(字母)

        string val(&str[1]);//将单词的第二个字符到最后一个字符作为哈希表的值

        if (opt == 'A')
        {
                    //cout<<"key is "<<key<<" value is "<<val<<endl;
                    insert(key, val);//如果操作符为'A'，则插入单词
        }
        if (opt == 'D')
        {
                    //cout<<"key is "<<key<<" value is "<<val<<endl;
                    remove(key, val);//如果操作符为'D'，则删除单词
        }
    };

    void print(){
        for(int i=0;i<26;i++){
            if(table[i].status=="occupied"){
                cout<<table[i].value<<" ";
            }
        }
    };

    void insert(char key, string val){
        int index = key-'a';//计算哈希表的键值
        int flag = 1;//flag=1表示哈希表中没有该键值，flag=0表示哈希表中有该键值
        while(flag==1) {
            if (table[index].status == "never used" || table[index].status == "tombstone") {
                //如果哈希表中该键值的状态为“never used”或者“tombstone”，则将该键值的值设为val,状态设为“occupied”
                table[index].value = val;
                //cout<<"index is "<<index<<" value is "<<table[index].value<<endl;
                table[index].status = "occupied";
                flag = 0;//将flag置为0，表示哈希表中已经有该键值
            } else if (table[index].status == "occupied" && table[index].value == val) {
                //如果哈希表中该键值的状态为“occupied”且该键值的值为val，则不插入该键值
                flag = 0;//将flag置为0，表示哈希表中已经有该键值
            } else {
                //如果哈希表中该键值的状态为“occupied”且该键值的值不为val，则将index+1对26取余，继续查找
                index=(index+1)%26;//
            }
        }
    };

    void remove(char key, string val){
        int index = key-'a';
        int flag = 1;
        while(flag==1) {
            if (table[index].status == "never used") {
                //如果哈希表中该键值的状态为“never used”，则不删除该键值
                flag = 0;
            } else if (table[index].status == "occupied" && table[index].value == val) {
                //如果哈希表中该键值的状态为“occupied”且该键值的值为val，则将该键值的状态设为“tombstone”
                table[index].status = "tombstone";
                //cout<<"index is "<<index<<" value is "<<table[index].value<<endl;
                flag = 0;
            }  else{
                //如果哈希表中该键值的状态为“occupied”且该键值的值不为val，则将index+1对26取余，继续查找
                index=(index+1)%26;
             
            }
        }
    };


    TableSlot table[26];//定义哈希表，哈希表的键值为26个字母，值为单词
};

int main(){
    string input;//定义输入字符串
    getline(cin,input);//读入输入字符串
    HashTable table(input);
    table.print();
    return 0;
}