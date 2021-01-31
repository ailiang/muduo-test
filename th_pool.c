
#include "th_pool.h"
#define POOL_SIZE 10

int main()
{
	th_pool pool;
	pool.start( 10 );

	while(1)
	{
		int data;
		cin >> data;
		pool.add_work( [data]{
				sleep( data );
				cout << " task end: " << data << endl ;
				} );

	}
	
	return 0;
}
