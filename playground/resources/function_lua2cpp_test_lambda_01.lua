function LUAFunction()
	print( "[LUA] Start" )
	ret = CPPFunction()
	print( "[LUA] End" )

	return ret;
end