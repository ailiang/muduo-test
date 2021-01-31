#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <functional>
#include <iostream>

using namespace std;

class th_pool
{
public:
	th_pool()
	{
		pthread_mutex_init( &init_mutex, nullptr );
		pthread_mutex_init( &work_mutex, nullptr );
		pthread_cond_init( &init_cond, nullptr );
		pthread_cond_init( &work_cond, nullptr );
	}
	~th_pool()
	{
		pthread_mutex_destroy( &init_mutex );
		pthread_mutex_destroy( &work_mutex );
		pthread_cond_destroy( &init_cond );
		pthread_cond_destroy( &work_cond );
	}

	int start( int num )
	{
		for( int i = 0; i < num; ++i )
		{
			pthread_t pid;
			pthread_create( &pid, nullptr, Run, this );
		}

		pthread_mutex_lock( &init_mutex );
		while( run_count != num )
		{
			pthread_cond_wait( &init_cond, &init_mutex );
		}
		pthread_mutex_unlock(&init_mutex);
		cout << "all thread start finish, num : " << run_count << endl;
	}

	void add_work( std::function<void()> r )
	{
		pthread_mutex_lock( &work_mutex);
		works.push_back( move(r) );
		pthread_cond_signal( &work_cond );
		pthread_mutex_unlock( &work_mutex );
	}

	static void *Run( void* param )
	{
		if(  pthread_detach( pthread_self() ) != 0 )
		{
			cout << " detach failed \n ";
			return (void*)0;
		}
		auto pool = (th_pool*)param;
		pthread_mutex_lock(&pool->init_mutex);
		pool->run_count++;
		cout << "start a thread, run_count:" << pool->run_count << endl;
		pthread_cond_signal(&pool->init_cond);
		pthread_mutex_unlock(&pool->init_mutex);
		while( 1 )
		{
			std::function<void()> f;
			pthread_mutex_lock( &pool->work_mutex);
			while( pool->works.empty())
			{
				pthread_cond_wait( &pool->work_cond, &pool->work_mutex );
			}
			f = move(pool->works.front());
			pool->works.pop_front();
			pthread_mutex_unlock( &pool->work_mutex );
			f();
		}
		return (int*)0;
	}
	std::deque< std::function<void()> > works;
	int run_count = 0;
	pthread_mutex_t init_mutex ;
	pthread_cond_t init_cond;

	pthread_mutex_t work_mutex;
	pthread_cond_t work_cond;
};




