#include<stdio.h>
int main(int argc, char const *argv[])
{
    void test();
    (int)(test);
    test();
    printf("%d\n",test);
    return 0;
}

void test()
{
    printf("l'am test function!\n");
}
