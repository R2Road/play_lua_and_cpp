function CallCPPFunction1( arg1, arg2 )
	print( "[LUA] Call - CallCPPFunction1 - " .. arg1 .. " , " .. arg2 )

	result = CPPFunction1( arg1, arg2 );

	return result;
end

function CallCPPFunction2( arg1, arg2 )
	print( "[LUA] Call - CallCPPFunction2 - " .. arg1 .. " , " .. arg2 )

	result = CPPFunction2( arg1, arg2 );

	return result;
end