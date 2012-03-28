JSON = (loadfile "JSON.lua")() -- one-time load of the routines

Blackbeard.rackam.still_running = false

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

print("testing filter...")
local f = Blackbeard.Filter()

f:parse_filter("(%e/%f) \"%a\"%d- yEnc (%p/%n)")
assert(f.filter_pieces[0] == "(", "Raw data")
assert(f.filter_pieces[1] == "%e", "Raw data")
assert(f.filter_pieces[2] == "/", "Raw data")
assert(f.filter_pieces[3] == "%f", "Raw data")
assert(f.filter_pieces[4] == ") \"", "Raw data")
assert(f.filter_pieces[5] == "%a", "Raw data")
assert(f.filter_pieces[6] == "\"", "Raw data")
assert(f.filter_pieces[7] == "%d", "Raw data")
assert(f.filter_pieces[8] == "- yEnc (", "Raw data")
assert(f.filter_pieces[9] == "%p", "Raw data")
assert(f.filter_pieces[10] == "/", "Raw data")
assert(f.filter_pieces[11] == "%n", "Raw data")
assert(f.filter_pieces[12] == ")", "Raw data")
assert(f.filter_pieces:size() == 13, "Number of filter fragments")

print("Finished tests OK")

