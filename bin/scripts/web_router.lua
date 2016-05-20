pprint = (loadfile "pprint.lua")()

local OBJDEF = {}

-- Split text into a list consisting of the strings in text,
-- separated by strings matching delimiter (which may be a pattern). 
-- example: strsplit(",%s*", "Anna, Bob, Charlie,Dolores")
function strsplit(delimiter, text)
  local list = {}
  local pos = 1
  if string.find("", delimiter, 1) then -- this would result in endless loops
    error("delimiter matches empty string!")
  end
  while 1 do
    local first, last = string.find(text, delimiter, pos)
    if first then -- found?
      table.insert(list, string.sub(text, pos, first-1))
      pos = last+1
    else
      table.insert(list, string.sub(text, pos))
      break
    end
  end
  return list
end

OBJDEF.__index = OBJDEF

function OBJDEF:new(args)
  local new = { }

  if args then
    for key, val in pairs(args) do
      new[key] = val
    end
  end

  new['routes'] = { }

  return setmetatable(new, OBJDEF)
  end

function OBJDEF:add_route(route, handler_func)
  print("Adding route: " .. route)
  self.routes[route] = handler_func
	result = strsplit("/", route)
	pprint(result)
end

return OBJDEF:new()
