function CallCPPFunction_1( arg1, arg2 )
	print( "[LUA] Call : CallCPPFunction_1 - " .. arg1 .. " , " .. arg2 )

	result1 = CPPFunction_1( arg1, arg2 );

	return result1;
end

function CallCPPFunction_2( arg1, arg2 )
	print( "[LUA] Call : CallCPPFunction_2 - " .. arg1 .. " , " .. arg2 )

	result1, result2, result3 = CPPFunction_2( arg1, arg2 );

	return result1, result2, result3;
end