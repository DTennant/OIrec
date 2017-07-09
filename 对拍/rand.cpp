#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
stringstream ss;
inline int random(int a, int b){return a + rand() % (b - a + 1);}
int main( int argc, char *argv[] ) {
    int seed=time(NULL);
    if(argc) {
        ss.clear();
        ss<<argv[1];
        ss>>seed;
    }
    srand(seed);
    //以下写你自己的数据生成代码 
    printf("1\n");
    int n=10;
    int m=random(1,20);
    printf("%d %d\n",n,m);
    for(int i=0 ; i<n ; ++i){
        printf(" %d ",random(0,m));
    }
    printf("\n");
    return 0;
}