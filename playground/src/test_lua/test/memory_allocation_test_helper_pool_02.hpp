#include "r2cm/r2cm_ostream.h"
#include "r2/r2_Assert.h"

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

	void OutputInfo()
	{
		std::cout << "+ Memory Pool Info\n";
		std::cout << "\t> Beg    : " << uint64_t( mBegin ) << "\n";
		std::cout << "\t> End    : " << uint64_t( mEnd ) << "\n";
		std::cout << "\t> Cur    : " << uint64_t( mCurrent ) << "\n";
		std::cout << "\t> Size   : " << uint64_t( mEnd ) - uint64_t( mBegin ) + 1 << "\n";
		std::cout << "\t> Use    : " << r2cm::clm( r2cm::eColor::FG_Green ) << uint64_t( mCurrent ) - uint64_t( mBegin ) << r2cm::clm() << "\n";
		std::cout << "\t> Remain : " << uint64_t( mEnd ) - uint64_t( mCurrent ) + 1 << "\n";
	}

	void* Allocate( size_t size )
	{
		R2ASSERT( size_t( mCurrent ) + size < size_t( mEnd ), "" );

		void* ptr = mCurrent;
		mCurrent = (char*)mCurrent + size;

		return ptr;
	}

	void Deallocate( void* p, size_t size )
	{
	}

	void* Realloc( void* p, size_t osize, size_t nsize )
	{
		void* ret = Allocate( nsize );
		memcpy( ret, p, osize );

		return ret;
	}

	static void *l_alloc( void *ud, void *ptr, size_t osize, size_t nsize )
	{
		(void)osize;  /* not used */

		LuaMemoryPool_02* pool = static_cast<LuaMemoryPool_02*>( ud );
		
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