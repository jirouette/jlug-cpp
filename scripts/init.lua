-- test.lua

function init()
	script("scripts/test.lua")
end

function main(s)
	print("Welcome to " .. s .. " ! ")
	local w = Window(200, 200, "coucou")
	w:clear()
	w:flip()
	print(w)
	w:test(w)
end
