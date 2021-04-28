#include <bits/stdc++.h>
using namespace std;

void solve()
{
	
    //LOGIC:- Try to bring all 1 near to the middle most 1
	//If number of 1 is even then anyone of the two middlemost 1
	
    int i ,j ,n ,k = 0 ,ans = 0 ;
	cin >> n ;
	
    //to take input of the array
    int arr[n] ;
	for( i = 0 ; i < n ; i++ )
		cin >> arr[i] ;

	// a is array to store all index of 1
	int a[n] ;
	for( j = 0 ; j < n ; j++ )
	{
		if( arr[j] == 1 )
			a[k++] = j ;
	}

	//mid is variable of middlemost 1 index
	int mid ;
    mid = a[k/2] ;

	//Now bringing all to middle most 1
	for( i = k/2 ; i >= 0 ; i-- )
		ans += abs(mid - a[i]) - (k/2 - i) ;
        
	for(i = k/2 ; i < k; i++)
		ans += abs(mid - a[i]) - (i - k/2) ;

  //in both cases substaction is required to avoid overlapping of non middle 1 to middle 1
	cout << ans << endl ;
}

int main()
{
		solve() ;
}
