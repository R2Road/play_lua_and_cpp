#include "r2cm/r2cm_ostream.h"

struct LuaMemoryPool
{
	void Free( void* p )
	{
		//std::cout << "LuaMemoryPool::Free" "\n";
		free( p );
	}

	void* Realloc( void* p, size_t size )
	{
		//std::cout << "LuaMemoryPool::Realloc" "\n";
		return realloc( p, size );
	}

	static void *l_alloc( void *ud, void *ptr, size_t osize, size_t nsize ) {
		(void)osize;  /* not used */

		//std::cout << "LuaMemoryPool::l_alloc" "\n";

		LuaMemoryPool* pool = static_cast<LuaMemoryPool*>( ud );
		
		if( nsize == 0 )
		{
			pool->Free( ptr );
			return NULL;
		}
		else
		{
			return pool->Realloc( ptr, nsize );
		}
	}
};