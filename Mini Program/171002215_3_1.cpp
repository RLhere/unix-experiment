 #include<iostream>
using namespace std;

int main()
{
    int n = 10;
    cout << "实参n地址： " <<&n << endl;
    long long int fibonaqi(int n);
    void test();
    cout << fibonaqi(n) << endl;
    cout << (int)test - (int)fibonaqi << endl;
    return 0;
}

long long int fibonaqi(int n)
{
    printf("n=%d:%p\n",n,&n);
    if(n==0) return 1;
    if(n==1) return 1;
    if(n > 1) return fibonaqi(n-1) + fibonaqi(n-2);
}

void test()
{
    return;
}