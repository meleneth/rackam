JSON = (loadfile "JSON.lua")() -- one-time load of the routines

local ng = getmetatable(Blackbeard.Newsgroup)
ng.as_json = function()
  output = {}

  output['name'] = self.name
  output['min_message_no'] = self.min_message_no
  output['max_message_no'] = self.max_message_no

  return JSON:encode_pretty(output)
end


function newsgroup_as_json(ng)
  return ng:as_json()
end

n = Blackbeard.Newsgroup()

n.name = "alt.binaries.divx"
n.min_message_no = 42
n.max_message_no = 400000004

print(newsgroup_as_json(n))

print("starting tests")
r = Blackbeard.WebRequest("get /jack.css")
assert(r.path == "/", "Path is '/'")
assert(r.filename == "jack.css", "Path is jack.css")

print("Finished tests OK")

