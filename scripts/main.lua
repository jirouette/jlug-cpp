-- main.lua
function init()
	print("Welcome to jlug ! ")
	git_version = Constants:getInstance():get("git_version")
	w = Window(800, 600, "jlug - "..git_version)
	map = Map("../res/maps/map.tmx", w, Input(w))
	c = Character(4, "jr", 20, 36, 0)
	map:addCharacter(c)
	while w:isOpen() do
		w:clear()
		c:setMove(map, "LEFT", 5)
		map:moveCharacters()
		map:displayLayers(w)
		map:displayCharacters(w)
		w:flip()
	end
	w:close()
end
