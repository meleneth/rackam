pprint = (loadfile "pprint.lua")()
JSON = (loadfile "JSON.lua")() -- one-time load of the routines
print("What are you going to do now bullwinkle?")
WebRouter = (loadfile "web_router.lua")()

Blackbeard.rackam.still_running = false

print("testing webrequest...")
local r = Blackbeard.WebRequest("get /jack.css")
assert(r.path == "/", "Path is '/'")
assert(r.filename == "jack.css", "Path is jack.css")

local r = Blackbeard.WebRequest("get /n")
assert(r.path == "/", "Path is '/'")
assert(r.filename == "n", "Filename is n")

local r = Blackbeard.WebRequest("get /n/alt.binaries.multimedia/authors")
print("---------")
print(r.path)
print("---------")
assert(r.path == "/n/alt.binaries.multimedia/", "Path is '/'")
assert(r.filename == "authors", "Filename is authors")

function no_func()
end

WebRouter:add_route("/n/:newsgroup/authors", no_func)

print "And the band marches on"

