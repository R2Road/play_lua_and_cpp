#include "r2cm/r2cm_ostream.h"

struct LuaMemoryPool_01
{
	void* mBegin;
	void* mEnd;
	void* mCurrent;

	LuaMemoryPool_01( void* begin, void* end ) :
		mBegin( begin )
		, mEnd( end )
		, mCurrent( begin )
	{}

	void* Allocate( size_t size )
	{
		std::cout << "Allocate : " << size << "\n";

		void* ptr = mCurrent;
		mCurrent = (char*)mCurrent  + size;
		return ptr;
	}

	void Deallocate( void* p )
	{
		std::cout << "Deallocate : " << "\n";
	}

	void* Realloc( void* p, size_t osize, size_t nsize )
	{
		void* ret = Allocate( nsize );
		memcpy( ret, p, osize );

		return ret;
	}

	static void *l_alloc( void *ud, void *ptr, size_t osize, size_t nsize ) {
		(void)osize;  /* not used */

		LuaMemoryPool_01* pool = static_cast<LuaMemoryPool_01*>( ud );
		
		if( nsize == 0 )
		{
			pool->Deallocate( ptr );
			return NULL;
		}

		if( ptr == nullptr )
		{
			return pool->Allocate( nsize );
		}

		return pool->Realloc( ptr, osize, nsize );
	}
};