function LUAFunction_1( arg1 )
	print( "[LUA] START : " .. arg1 )

	result1, result2 = CPPFunction_1( arg1 );

	print( "[LUA] END" );

	return result1, result2;
end

function LUAFunction_2( arg1, arg2 )
	print( "[LUA] START : " .. arg1 .. " , " .. arg2 )

	result1, result2, result3 = CPPFunction_2( arg1, arg2 );

	print( "[LUA] END" );

	return result1, result2, result3;
end