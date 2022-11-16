#include "r2cm/r2cm_ostream.h"

struct LuaMemoryPool_02
{
	void* mBegin;
	void* mEnd;
	void* mCurrent;

	LuaMemoryPool_02( void* begin, void* end ) :
		mBegin( begin )
		, mEnd( end )
		, mCurrent( begin )
	{}

	void* Allocate( size_t size )
	{
		void* ptr = mCurrent;
		mCurrent = (char*)mCurrent  + size;
		return ptr;
	}

	void Deallocate( void* p )
	{
	}

	void* Realloc( void* p, size_t osize, size_t nsize )
	{
		void* ret = Allocate( nsize );
		memcpy( ret, p, osize );

		return ret;
	}

	static void *l_alloc( void *ud, void *ptr, size_t osize, size_t nsize ) {
		(void)osize;  /* not used */

		LuaMemoryPool_02* pool = static_cast<LuaMemoryPool_02*>( ud );
		
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