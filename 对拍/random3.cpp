//range random
//from Lvsi‘s home
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
int main(){
    //freopen( "1.in","r",stdin );
    //freopen( "3.out","w",stdout );
    srand( time( NULL ) );
    int t = 99,n = 10 ;
    while( n-- ) {
        printf( "%d\n",rand() % t );
    }
    return 0;
}