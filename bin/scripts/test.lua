JSON = (loadfile "JSON.lua")() -- one-time load of the routines

print("starting tests")

print("testing webrequest...")
local r = Blackbeard.WebRequest("get /jack.css")
assert(r.path == "/", "Path is '/'")
assert(r.filename == "jack.css", "Path is jack.css")

print("testing stringpattern...")
local s = Blackbeard.StringPattern(7)

s:add_breaker(" - File ")
s:add_breaker(" of ")
s:add_breaker(": \"")
s:add_breaker("\" yEnc (")
s:add_breaker("/")
s:add_breaker(")")

assert(s:match("Star Wars Clone Wars - File 11 of 11: \"Clone Wars Chapter 20.mpg\" yEnc (248/258)"));
local matched = s:match("Star Wars Clone Wars \"Clone Wars Chapter 20.mpg\" yEnc (248/258)")
assert(matched == 0, "string doesn't match")

s:match("Star Wars Clone Wars - File 11 of 11: \"Clone Wars Chapter 20.mpg\" yEnc (248/258)")

print("Finished tests OK")

