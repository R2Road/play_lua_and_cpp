#include "r2tm/r2tm_ostream.hpp"

struct LuaMemoryPool_01
{
	void Deallocate( void* p, size_t size )
	{
		std::cout << "Deallocate : " << size  << "\n";
		free( p );
	}

	void* Reallocate( void* p, size_t osize, size_t nsize )
	{
		std::cout << "Realloc : " << nsize << "\n";
		return realloc( p, nsize );
	}

	static void *l_alloc( void *ud, void *ptr, size_t osize, size_t nsize ) {
		(void)osize;  /* not used */

		LuaMemoryPool_01* pool = static_cast<LuaMemoryPool_01*>( ud );
		
		if( nsize == 0 )
		{
			pool->Deallocate( ptr, osize );
			return NULL;
		}

		return pool->Reallocate( ptr, osize, nsize );
	}
};