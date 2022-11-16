#include "r2cm/r2cm_ostream.h"

struct LuaMemoryPool_01
{
	void* mBegin;
	void* mEnd;
	void* mCurrent;
	size_t mAllocatedSize;

	LuaMemoryPool_01( void* begin, void* end ) :
		mBegin( begin )
		, mEnd( end )
		, mCurrent( begin )
	{}
	~LuaMemoryPool_01()
	{
		std::cout << "~LuaMemoryPool_01()\n";
		std::cout << "\t> Beg    : " << reinterpret_cast<size_t>( mBegin ) << "\n";
		std::cout << "\t> End    : " << reinterpret_cast<size_t>( mEnd ) << "\n";
		std::cout << "\t> Cur    : " << reinterpret_cast<size_t>( mCurrent ) << "\n";
		std::cout << "\t> Size   : " << reinterpret_cast<size_t>( mEnd ) - reinterpret_cast<size_t>( mBegin ) + 1 << "\n";
		std::cout << "\t> Use    : " << reinterpret_cast<size_t>( mCurrent ) - reinterpret_cast<size_t>( mBegin ) << "\n";
		std::cout << "\t> Remain : " << reinterpret_cast<size_t>( mEnd ) - reinterpret_cast<size_t>( mCurrent ) + 1 << "\n";
	}

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