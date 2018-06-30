def tarai(x, y, z)
	if y < x then
	  tarai( 
			tarai(x-1, y, z),
			tarai(y-1, z, x),
			tarai(z-1, x, y)
			)
	else
	  y          # not z!
	end
end
p tarai(12, 6, 0)