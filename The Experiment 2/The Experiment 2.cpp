/*
 * @Description: An implementation of universal Turing machine
 * @Version: 1.0
 * @Author: Kevin Liu
 * @Date: 2019-10-24 16:07:15
 * @LastEditors: Kevin Liu
 * @LastEditTime: 2019-10-24 16:10:01
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string>
using namespace std;

//the structure of data
template<typename T,typename U>
class Key
{
    public:
        T mKey;
        U mVal;

    U getVal()
    {
        return mVal;
    }

    T getKey()
    {
        return mKey;
    }
};

int main(int argc, char const *argv[])
{
    cout << "This is the rules:" << endl;

    ifstream ifs(argv[1],ios::in);//打开文件

    if(!ifs.is_open())//失败报错退出
    {
        cout<< "文件打开失败" << endl;
        return 0;
    }

/*
    char buf[1024];
    while(ifs >> buf)
    {
        cout << buf << endl;
    }
*/

    int alllines = 0;
    char buf[1024];//the cache for reading file linely
    int size[6]={1,1,1,1,1,1};//the last one is for set Delta while the other is for other sets

    int i = 0;//the line number
    while (!ifs.eof())//just for memory size statistic
    {

        ifs.getline(buf, sizeof(buf));
        //translate symbol to binary
            //statistic the size of memory
        cout << buf <<endl;

        for(int j = 0;buf[j]!=';';j++)//statistic the number of elements
        {
            if(buf[j] == ',') size[i]++;
        }

        i++;
        alllines = i;
    }

    size[5] = i - 6;
//define the memory
    Key <string,string> Q[size[0]];
    Key <string,string> Sigma[size[1]];
    Key <string,string> q0[size[2]];
    Key <string,string> Accept[size[3]];
    Key <string,string> Reject[size[4]];
    string Delta[size[5]];

//define the scope
    Key <string, string> R,L,N;
    R.mKey = "R";
    R.mVal = "0";
    L.mKey = "L";
    L.mVal = "00";
    N.mKey = "-";
    N.mVal = "000";

    ifs.close();//关闭流对象

    ifstream ifs1(argv[1],ios::in);//打开文件

    if(!ifs1.is_open())//失败报错退出
    {
        cout<< "文件打开失败" << endl;
        return 0;
    }

    i = 0;//for finding the true position of the key and value of six teams
    while(!ifs1.eof())//translate the five teams
    {
        ifs1.getline(buf, sizeof(buf));

        //translate the symbols to binary
        string media = buf;
        string temp;
        switch(i)
        {
            case 0://Q
                {
                    for(int j = 0;j < size[i]; j++)
                    {

                        if(media.find(",")<20)
                        {
                            Q[j].mKey = media.substr(media.find(" ")+1,media.find(",")-media.find(" ")-1);
                            media = media.substr(media.find(",")+1,media.length());
                        }
                        else
                        {
                            Q[j].mKey = media.substr(media.find(" ")+1,media.find(";")-media.find(" ")-1);
                        }
                        Q[j].mVal.assign(j+1,'0');
                    }
                    break;
                }
            case 1://Sigma
                {
                    for(int j = 0;j < size[i]; j++)
                    {

                        if(media.find(",")<20)
                        {
                            Sigma[j].mKey = media.substr(media.find(" ")+1,media.find(",")-media.find(" ")-1);
                            media = media.substr(media.find(",")+1,media.length());
                        }
                        else
                        {
                            Sigma[j].mKey = media.substr(media.find(" ")+1,media.find(";")-media.find(" ")-1);
                        }
                        Sigma[j].mVal.assign(j+1,'0');
                    }
                    break;
                }
            case 2://q0
                {
                    for(int j = 0;j < size[i]; j++)
                    {

                        if(media.find(",")<20)
                        {
                            q0[j].mKey = media.substr(media.find(" ")+1,media.find(",")-media.find(" ")-1);
                            media = media.substr(media.find(",")+1,media.length());
                        }
                        else
                        {
                            q0[j].mKey = media.substr(media.find(" ")+1,media.find(";")-media.find(" ")-1);
                        }
                        q0[j].mVal.assign(j+1,'0');
                    }
                    break;
                }
            case 3://Accept
                {
                    for(int j = 0;j < size[i]; j++)
                    {

                        if(media.find(",")<20)
                        {
                            Accept[j].mKey = media.substr(media.find(" ")+1,media.find(",")-media.find(" ")-1);
                            media = media.substr(media.find(",")+1,media.length());
                        }
                        else
                        {
                            Accept[j].mKey = media.substr(media.find(" ")+1,media.find(";")-media.find(" ")-1);
                        }
                        Accept[j].mVal.assign(j+1,'0');
                    }
                    break;
                }
            case 4://Reject
                {
                    for(int j = 0;j < size[i]; j++)
                    {

                        if(media.find(",")<20)
                        {
                            Reject[j].mKey = media.substr(media.find(" ")+1,media.find(",")-media.find(" ")-1);
                            media = media.substr(media.find(",")+1,media.length());
                        }
                        else
                        {
                            Reject[j].mKey = media.substr(media.find(" ")+1,media.find(";")-media.find(" ")-1);
                        }
                        Reject[j].mVal.assign(j+1,'0');
                    }
                    break;
                }
            default:break;
        }


        //keep the same symbol same binary
        for(int te=0;te<size[0];te++)
        {
            for(int ta=0;ta<size[2];ta++)
            {
                if(Q[te].mKey==q0[ta].mKey)
                {
                    q0[ta].mVal = Q[te].mVal;
                }
            }
            for(int tb=0;tb<size[3];tb++)
            {
                if(Q[te].mKey==Accept[tb].mKey)
                {
                    Accept[tb].mVal = Q[te].mVal;
                }
            }
            for(int tc=0;tc<size[4];tc++)
            {
                if(Q[te].mKey==Reject[tc].mKey)
                {
                    Reject[tc].mVal = Q[te].mVal;
                }
            }
        }

//if ......  Delta to binary
        if(i>5 && i<alllines)
        {
            string tt = buf;
            string xun[5];
            xun[0] = tt.substr(tt.find(" ")+1,tt.find(",")-tt.find(" ")-1);
            tt = tt.substr(tt.find(",")+1,tt.length());
            xun[1] = tt.substr(tt.find(" ")+1,tt.find(")")-tt.find(" ")-1);
            tt = tt.substr(tt.find("(")+1,tt.length());
            xun[2] = tt.substr(tt.find(" ")+1,tt.find(",")-tt.find(" ")-1);
            tt = tt.substr(tt.find(",")+1,tt.length());
            xun[3] = tt.substr(tt.find(" ")+1,tt.find(",")-tt.find(" ")-1);
            tt = tt.substr(tt.find(",")+1,tt.length());
            xun[4] = tt.substr(tt.find(" ")+1,tt.find(")")-tt.find(" ")-1);
            for(int m = 0; m < 5; m++)
            {
                switch(m)
                {
                    case 0:
                        {
                            for(int n = 0;n < size[0];n++)
                            {
                                if(Q[n].mKey==xun[m])
                                {
                                    Delta[i-6]=Delta[i-6]+Q[n].mVal+"1";
                                }
                            }
                            break;
                        }
                    case 1:
                        {
                            for(int n = 0;n < size[1];n++)
                            {
                                if(Sigma[n].mKey==xun[m])
                                {
                                    Delta[i-6]=Delta[i-6]+Sigma[n].mVal+"1";
                                }
                            }
                            break;
                        }
                    case 2:
                        {
                            for(int n = 0;n < size[0];n++)
                            {
                                if(Q[n].mKey==xun[m])
                                {
                                    Delta[i-6]=Delta[i-6]+Q[n].mVal+"1";
                                }
                            }
                            break;
                        }
                    case 3:
                        {
                            for(int n = 0;n < size[0];n++)
                            {
                                if(Sigma[n].mKey==xun[m])
                                {
                                    Delta[i-6]=Delta[i-6]+Sigma[n].mVal+"1";
                                }
                            }
                            break;
                        }
                    case 4:
                        {
                            if(xun[m]==R.mKey)
                                Delta[i-6]=Delta[i-6]+R.mVal;
                            else if(xun[m]==L.mKey)
                                Delta[i-6]=Delta[i-6]+L.mVal;
                            else
                                Delta[i-6]=Delta[i-6]+N.mVal;
                            break;
                        }
                    default:break;
                }
            }
        }

        i++;
        

//      cout << buf << endl;

        
        
    }
//
//
//print the binary codes of five teams

    cout<<"这是状态集和符号集的编码："<<endl;
    for(int k = 0;k < size[0];k++)
    {
        cout << Q[k].mKey << " " << Q[k].mVal << endl;
    }
    for(int k = 0;k < size[1];k++)
    {
        cout << Sigma[k].mKey << " " << Sigma[k].mVal << endl;
    }
    for(int k = 0;k < size[2];k++)
    {
        cout << q0[k].mKey << " " << q0[k].mVal << endl;
    }
    for(int k = 0;k < size[3];k++)
    {
        cout << Accept[k].mKey << " " << Accept[k].mVal << endl;
    }
    for(int k = 0;k < size[4];k++)
    {
        cout << Reject[k].mKey << " " << Reject[k].mVal << endl;
    }


//

//print the Delta binary
    int NumberofDeltaRules = alllines - 7;
    cout<<"这是"<<NumberofDeltaRules<<"条Delta规则的二进制编码形式："<<endl;
    for(int mm = 0;mm < alllines - 7;mm++)
    {
        cout<<mm << ":  "<<Delta[mm]<<endl;
    }
//


/*
// print the size[]
    for(int l = 0;l < 6;l++)
    {
        cout << size[l] << endl;
    }
*/




/**
// print the size[]
    for(int i = 0;i < 5;i++)
    {
        cout << size[i] << endl;
    }
*/

/*  
// one way to cout the file
    char c;

    while ( c = ifs.get() != EOF)
    {
        cout << c;
    }
*/
    ifs1.close();//关闭流对象

    
    

    
    //receive and deal with the input
    int r;
    string Mstartstate = q0[0].mVal;
    string input;
    string reader;
    cin >> input;
    int len = input.length();
    string binput[len];
//    cout << sizeof(binput)/sizeof(binput[0])<<endl;
    for(int i=0;i<input.length();i++)
    {
        //cout<<i<<endl;
        reader = input.substr(i,1);
        //cout<< "reader: " << reader << endl;
        for(r=0;r<size[1];r++)
        {
        //    cout<< r << endl;
            if(Sigma[r].mKey==reader)
            {
                binput[i]=Sigma[r].mVal;
                break;
            }
        }
        //cout<<r<<endl;
        //cout<<i<<endl;
        if(r==size[1])
        {
            cout<<"Error:the input is not in the Sigma!"<<endl;
            return 0;
        }
    }

//    for(int lll=0;lll<input.length();lll++)
//    {
//        cout << binput[lll]<<"1";
//    }
//the initial of the M
    string start = Mstartstate + "1" + binput[0] + "1";
    string state = Mstartstate;
    cout << "图灵机初始状态编码：" << state << endl;
    int id=0;
    string exit="";

    int test=0;
    for(;;)
    {
        if(exit!="000")
        {


            for(int m=0;m<size[5];m++)
            {
                if(!Delta[m].compare(0,start.length(),start,0,start.length()))
                {   
                //    cout<<binput[id]<<"    ";
                    cout<<test<<"   "<<Delta[m]<<endl;
                    test++;

                    string xun = Delta[m].substr(Delta[m].find("1")+1,Delta[m].length());
                    //cout << xun <<endl;
                    xun = xun.substr(xun.find("1")+1,xun.length());
                    //cout << xun <<endl;
                    state = xun.substr(0,xun.find("1"));
                    //cout << "state: " << state <<endl;
                    xun = xun.substr(xun.find("1")+1,xun.length());
                    //cout << xun <<endl;
                    //if(id==input.length())
                    //    break;


                    binput[id] = xun.substr(0,xun.find("1"));
                    //cout << id << ":" << binput[id] <<endl;
                    xun = xun.substr(xun.find("1")+1,xun.length());
                    //cout<<xun<<endl;
                    //cout<<endl<<endl;
                    if(xun=="0")
                    {
                        id+=1;
                    }
                    else if(xun=="00")
                    {
                        id-=1;
                    }
                    else if(xun=="000")
                    {
                        id=id;
                    }
                    cout<<binput[id]<<endl;
                    exit = xun;
                }
            }
            start = state+"1"+binput[id]+"1";
        }
        else
        {
            break;
        }
        cout<<"这是纸带上字符变化的过程及对应步骤执行的规则编码："<<endl;
        for(int en=0;en<input.length();en++)
        {
            for(int d=0;d<size[1];d++)
            {
                if(binput[en]==Sigma[d].mVal)
                {
                    cout<<Sigma[d].mKey;
                }
            }
        }
        cout<<endl;
    }
//print the end
    for(int en=0;en<input.length();en++)
    {
        for(int d=0;d<size[1];d++)
        {
            if(binput[en]==Sigma[d].mVal)
            {
                cout<<Sigma[d].mKey;
            }
        }
    }
    cout<<endl;
    //
    //cout<<binput[0]<< " " <<binput[1]<< " " <<binput[2]<<endl;
    //reader = input.substr(0,1);
    //string instate = q0[0];
    //string start = (instate + reader);
    //translate the M binary
    //Work due to the M binary like: -,R,L,Rewrite,noncarry……
    //cout the input which is dealt by the rules defined by Delta
    //cout << input << endl;

    return 0;
}