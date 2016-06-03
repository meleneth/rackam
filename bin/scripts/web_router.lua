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

  new['routes'] = {}

  return setmetatable(new, OBJDEF)
end

function OBJDEF:add_route(route, route_func)
  print("Adding route: " .. route)
  local r = {}
  r['route_func'] = route_func
  r['route_template'] = route
  r['route_pieces'] = strsplit("/", route)
  r['route_name'] = route
  table.insert(self.routes, r)
  return r
end

function OBJDEF:_starts_with_colon(str)
  if string.len(str) == 0 then
    return false
  end
  if string.sub(str, 1, 1) == ":" then
    return string.sub(str, 2, string.len(str))
  end
  return false
end

function OBJDEF:check_route(request)
  local candidate = request.path .. request.filename
  local candidate_bits = strsplit("/", candidate)

  for ri,route in ipairs(self.routes) do
    result = self:_route_bits(route, candidate_bits)
    if result then
      return result
    end
  end
  return false
end

function OBJDEF:route(request, response)
  local candidate = request.path .. request.filename
  local candidate_bits = strsplit("/", candidate)

  for ri,route in ipairs(self.routes) do
    result = self:_route_bits(route, candidate_bits)
    if result then
      print("Matched route " .. route.route_name)
      return route['route_func'](request, result, response)
    end
  end
  return false
end

function OBJDEF:_route_bits(route, bits)
  rp = route.route_pieces
  if #rp ~= #bits then
    return false
  end
  local match = {}

  for i, v in ipairs(bits) do
    p = route.route_pieces[i]
    local colon_match = self:_starts_with_colon(route.route_pieces[i])
    if colon_match then
      match[colon_match] = v
    elseif v ~= route.route_pieces[i] then
      return false
    end
  end
  return match
end



return OBJDEF:new()
