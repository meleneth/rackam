print("Lua says 'hi'")

JSON = (loadfile "JSON.lua")() -- one-time load of the routines

n = Blackbeard.Newsgroup()

n.name = "alt.binaries.divx"
n.min_message_no = 42
n.max_message_no = 400000004

print(n.name)


function newsgroup_as_json(newsgroup)
  output = {}

  output['name'] = newsgroup.name
  output['min_message_no'] = newsgroup.min_message_no
  output['max_message_no'] = newsgroup.max_message_no

  return JSON:encode_pretty(output)
end

print(newsgroup_as_json(n))

print("starting tests")
r = Blackbeard.WebRequest("get /jack.css")
assert(r.path == "/", "Path is '/'")
assert(r.filename == "jack.css", "Path is jack.css")

print("Finished tests OK")

