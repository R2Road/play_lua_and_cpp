function LUAFunction_1( arg1, arg2 )
	print( "[LUA] START : " .. arg1 .. " , " .. arg2 )

	result1 = CPPFunction_1( arg1, arg2 );

	print( "[LUA] END" );

	return result1;
end

function LUAFunction_2( arg1, arg2 )
	print( "[LUA] START : " .. arg1 .. " , " .. arg2 )

	result1, result2, result3 = CPPFunction_2( arg1, arg2 );

	print( "[LUA] END" );

	return result1, result2, result3;
end