print("Lua says 'hi'")

JSON = (loadfile "JSON.lua")() -- one-time load of the routines

n = Blackbeard.Newsgroup()

n.name = "alt.binaries.divx"

print(n.name)


function newsgroup_as_json(newsgroup)
  output = {}
  output['name'] = newsgroup.name
  return JSON:encode_pretty(output)
end

print(newsgroup_as_json(n))
