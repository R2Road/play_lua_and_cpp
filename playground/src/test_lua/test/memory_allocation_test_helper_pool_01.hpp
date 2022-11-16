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
		OutputInfo();
	}

	void OutputInfo()
	{
		std::cout << "+ Memory Pool Info\n";
		std::cout << "\t> Beg    : " << uint64_t( mBegin ) << "\n";
		std::cout << "\t> End    : " << uint64_t( mEnd ) << "\n";
		std::cout << "\t> Cur    : " << uint64_t( mCurrent ) << "\n";
		std::cout << "\t> Size   : " << uint64_t( mEnd ) - uint64_t( mBegin ) + 1 << "\n";
		std::cout << "\t> Use    : " << uint64_t( mCurrent ) - uint64_t( mBegin ) << "\n";
		std::cout << "\t> Remain : " << uint64_t( mEnd ) - uint64_t( mCurrent ) + 1 << "\n";
	}

	void* Allocate( size_t size )
	{
		std::cout << "Allocate : " << size << "\n";

		void* ptr = mCurrent;
		mCurrent = (char*)mCurrent  + size;
		return ptr;
	}

	void Deallocate( void* p, size_t size )
	{
		std::cout << "Deallocate : " << size  << "\n";
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
			if( nullptr != ptr )
			{
				pool->Deallocate( ptr, osize );
			}

			return NULL;
		}

		if( ptr == nullptr )
		{
			return pool->Allocate( nsize );
		}

		return pool->Realloc( ptr, osize, nsize );
	}
};