-- main.lua
function init()
	print("Welcome to jlug ! ")
	w = Window(800, 600, "jlug")
	map = Map("../res/maps/map.tmx", w, Input(w))
	while w:isOpen() do
		w:clear()
		map:moveCharacters()
		map:displayLayers(w)
		map:displayCharacters(w)
		w:flip()
	end
	w:close()
end
