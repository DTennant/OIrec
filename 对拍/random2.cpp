//random float
//from Lvsi‘s home
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
int main() {
    //freopen( "1.in","r",stdin );
    //freopen( "3.out","w",stdout );
    srand( time( NULL ) );
    int t,n = 10 ;
    while( n-- ){
        printf( "%.6lf\n",rand()*1.0 / 100 );
    }
    return 0;
}