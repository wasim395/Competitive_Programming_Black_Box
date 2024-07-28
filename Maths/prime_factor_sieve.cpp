
// time complexity -> o( n log(log(n)) ).

vector<bool> primeSieve( int n ){

    vector<bool> isPrime(n+1 , 1) ;
    isPrime[0] = 0 ;
    isPrime[1] = 1 ;

    for( int i=2 ; i*i<=n ; i++ ){
        if( isPrime[i] ){
            for( int j=i*i ; j<=n ; j += i ){
                isPrime[j] = 0 ;
            }
        }
    }
    return isPrime ;
}
