JSON = (loadfile "JSON.lua")() -- one-time load of the routines
WebRouter = (loadfile "web_router.lua")()

function web_escape(s)
  if s == nil then
    return ''
  end
  s = string.gsub(s, "&", "&amp;")
  s = string.gsub(s, ">", "&gt;")
  s = string.gsub(s, "<", "&lt;")
  return s
end

-- A new inheritsFrom() function
-- this code from lua users wiki,  lua inheritence

function inheritsFrom( baseClass )

    local new_class = {}
    local class_mt = { __index = new_class }

    function new_class:create(...)
        local newinst = {}
        setmetatable( newinst, class_mt )
        if newinst.initialize then
          newinst:initialize(...)
        end
        return newinst
    end

    if nil ~= baseClass then
        setmetatable( new_class, { __index = baseClass } )
    end

    -- Implementation of additional OO properties starts here --

    -- Return the class object of the instance
    function new_class:class()
        return new_class
    end

    -- Return the super class object of the instance
    function new_class:superClass()
        return baseClass
    end

    -- Return true if the caller is an instance of theClass
    function new_class:isa( theClass )
        local b_isa = false

        local cur_class = new_class

        while ( nil ~= cur_class ) and ( false == b_isa ) do
            if cur_class == theClass then
                b_isa = true
            else
                cur_class = cur_class:superClass()
            end
        end

        return b_isa
    end

    return new_class
end

function paged_web_render(webrequest, items, renderfunc)
-- getting tricksy
  local max_i = items:size() - 1
  local page_ipp = webrequest:paramn("page_ipp")
  local page_first = webrequest:paramn("page_first")
  if page_ipp   == 0 then page_ipp = 20 end
  local page_last = page_first + page_ipp
  if page_last > max_i then page_last = max_i end
  return web_render(page_first, page_last, items, renderfunc)
end

function web_render(start_val, end_val, items, renderfunc)
  local response_lines = {}
  for i = start_val, end_val do
    local item = items[i]
    local result = renderfunc(item)
    table.insert(response_lines, result)
  end
  return "[\n" .. table.concat(response_lines, ",\n") .. "]\n"
end


function author_as_json(author)
  local output = {}

  output['id'] = author.id
  output['name'] = web_escape(author.name)
  output['newsgroup'] = web_escape(author.newsgroup.name)
  output['size'] = author:get_size_str()

  if author.postsets then
    output['num_postsets'] = author.postsets:size()
  end
  if author.postfiles then
    output['num_postfiles'] = author.postfiles:size()
  end
  if author.headers then
    output['num_headers'] = author.headers:size()
  end

  return JSON:encode(output)
end

function filter_as_json(filter)
  local output = {}

  output['text'] = filter.text
  output['num_matched'] = filter:get_num_matched_str()
  return JSON:encode(output)
end

function postset_as_json(postset)
  local output = {}

  output['id'] = postset.id
  output['name'] = web_escape(postset.subject)
  output['newsgroup'] = web_escape(postset.newsgroup.name)
  output['author'] = web_escape(postset.author.name)
  output['min_message_no'] = postset:get_min_message_no_str()
  output['max_message_no'] = postset:get_max_message_no_str()
  output['size'] = postset:get_size_str()

  return JSON:encode(output)
end

function postfile_as_json(postfile)
  local output = {}

  output['id'] = postfile.id
  output['name'] = web_escape(postfile.name)
  output['newsgroup'] = web_escape(postfile.newsgroup.name)
  output['author'] = web_escape(postfile.author.name)
  output['min_message_no'] = postfile:get_min_message_no_str()
  output['max_message_no'] = postfile:get_max_message_no_str()
  output['size'] = postfile:get_size_str()

  return JSON:encode(output)
end

function newsgroup_as_json(newsgroup)
  local output = {}

  output['name'] = web_escape(newsgroup.name)
  output['min_message_no'] = newsgroup:get_min_message_no_str()
  output['max_message_no'] = newsgroup:get_max_message_no_str()
  output['size'] = newsgroup:get_size_str()
  if newsgroup.headers then
    output['num_headers']    = newsgroup.headers:size()
  end
  if newsgroup.authors then
    output['num_authors']    = newsgroup.authors:size()
  end
  if newsgroup.postsets then
    output['num_postsets']    = newsgroup.postsets:size()
  end
  if newsgroup.postfiles then
    output['num_postfiles']    = newsgroup.postfiles:size()
  end

  return JSON:encode(output)
  --return JSON:encode_pretty(output)
end

function header_as_json(header)
  local output = {}
  
  output['msg_id']  = header.msg_id
  output['subject'] = web_escape(header.subject)
  output['article_no'] = header:get_article_no_str()
  output['posted_by'] = web_escape(header.author.name)
  output['size'] = header.size

  return JSON:encode(output)
end

function web_response_authors(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
  local response_lines = {}
  local i;
  local max_i = newsgroup.authors:size() - 1
  local page_ipp = webrequest:paramn("page_ipp")
  local page_first = webrequest:paramn("page_first")
  if page_ipp   == 0 then page_ipp = 20 end
  local page_last = page_first + page_ipp
  if page_last > max_i then page_last = max_i end

  for i = page_first, page_last do
    local author = newsgroup.authors[i]
    table.insert(response_lines, author_as_json(author))
  end
  webresponse.body = "[\n" .. table.concat(response_lines, ",\n") .. "]\n"
end

--create_paged_handler("author", "authors", "Name|PostSets|PostFiles|Headers")

--function create_paged_handler(field_name, plural_field_name, headers)
  
--end

function rest_response_newsgroups(webrequest, match, webresponse)
  local response_lines = {}
  local i
  local max_i = Blackbeard.rackam.newsgroups:size() - 1
  for i = 0, max_i do
    local ng = Blackbeard.rackam.newsgroups[i]
    table.insert(response_lines, newsgroup_as_json(ng))
  end
  webresponse.body = "[" .. table.concat(response_lines, ",\n") .. "]\n"
end

WebRouter:add_route("/n", rest_response_newsgroups)

function rest_response_newsgroup_authors(webrequest, match, webresponse)
  local response_lines = {}
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(match.newsgroup)
  local i
  local max_i = Blackbeard.rackam.newsgroups:size() - 1
  for i = 0, max_i do
    local ng = Blackbeard.rackam.newsgroups[i]
    table.insert(response_lines, newsgroup_as_json(ng))
  end
  webresponse.body = "[" .. table.concat(response_lines, ",\n") .. "]\n"
end

WebRouter:add_route("/n/:newsgroup/authors", rest_response_newsgroup_authors)

function web_response_newsgroups(webresponse)
  local response_lines = {}
  local i
  local max_i = Blackbeard.rackam.newsgroups:size() - 1
  for i = 0, max_i do
    local ng = Blackbeard.rackam.newsgroups[i]
    table.insert(response_lines, newsgroup_as_json(ng))
  end
  webresponse.body = "[\n" .. table.concat(response_lines, ",\n") .. "]\n"
end

function web_response_filters(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
  webresponse.body = web_render(0, newsgroup.filters:size() - 1, newsgroup.filters, function(filter) return header_as_json(filter) end)
end

function web_response_headers(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
  local headers = newsgroup.headers

  if webrequest:has_param("author_id") then
    local author = newsgroup:author_for_id(webrequest:paramn("author_id"))
    headers = author.headers
  end

  webresponse.body = paged_web_render(webrequest, headers, function(header) return header_as_json(header) end)
end

function web_response_postfiles(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
  local items = newsgroup.postfiles

  if webrequest:has_param("author_id") then
    local author = newsgroup:author_for_id(webrequest:paramn("author_id"))
    items = author.postfiles
  end

  webresponse.body = paged_web_render(webrequest, items, function(postfile) return postfile_as_json(postfile) end)
end

function handle_web_request(webrequest, webresponse)
  full_path = table.concat({webrequest.path, webrequest.filename}, "/")

  if WebRouter:route(webrequest, webresponse) then
    return
  end

  if webrequest.path == "/" then
    if webrequest.filename == "authors.cgi" then
      web_response_authors(webrequest, webresponse)
      return
    end
    if webrequest.filename == "newsgroups.cgi" then
      web_response_newsgroups(webresponse)
      return
    end
    if webrequest.filename == "filters.cgi" then
      web_response_filters(webrequest, webresponse)
      return
    end
    if webrequest.filename == "headers.cgi" then
      web_response_headers(webrequest, webresponse)
      return
    end
    if webrequest.filename == "postfiles.cgi" then
      web_response_postfiles(webrequest, webresponse)
      return
    end
    if webrequest.filename == "author_postsets.cgi" then
      web_response_author_postsets(webrequest, webresponse)
      return
    end
    if webrequest.filename == "newsgroup_postsets.cgi" then
      web_response_newsgroup_postsets(webrequest, webresponse)
      return
    end
  end
end

local rackam = Blackbeard.rackam

rackam:newsgroup_for_name("alt.binaries.stuffyouwant")
local n = rackam:newsgroup_for_name("alt.binaries.multimedia.cartoons")
n:add_filter("(%e/%f) \"%a\"%d- yEnc (%p/%n)")
n:add_filter("%s [%e/%f] - \"%a\"%d yEnc (%p/%n)")
n:add_filter("%s[%e/%f] - \"%a\"%d yEnc (%p/%n)")
n:add_filter("%s[%e/%f] - yEnc \"%a\" (%p/%n)")
n:add_filter("%s [%e/%f] \"%a\"%d(%p/%n)")
n:add_filter("[%e/%f] - \"%a\" (%p/%n)")
n:add_filter("%d\"%a\" [%e/%f] yEnc (%p/%n)")
n:add_filter("%s - \"%a\" yEnc (%p/%n)")
n:add_filter("%a [%e/%f] yEnc (%p/%n)")
n:add_filter("\"%a\" (%p/%n) yEnc - %e of %f")
n:add_filter("%s - \"%a\" (%p/%n)")
n:add_filter("%d - [%s] - [%e/%f] - %a yEnc (%p/%n)")
n:add_filter("] - \"%a\" yEnc (%p/%n)")
n:add_filter("[%e/%f] - \"%a\"%d(%p/%n)")
n:add_filter("%a - [%e/%f] (%p/%n)")
-- this next one is /really/ broad
n:add_filter("%a (%p/%n)")

rackam:load_headers_from_file(n, "headers_snipper.log")

local webserver = rackam.webserver

file = webserver:register_file("index.html", "htdocs/index.haml", "text/html")
file:add_filter("haml -s")
webserver:register_file("favicon.ico", "htdocs/favicon.ico", "text/html")
webserver:register_file("jquery.js", "htdocs/vendor/jquery-1.11.0.min.js", "text/html")
webserver:register_file("bootstrap.min.css", "htdocs/vendor/bootstrap.min.css", "text/css")
file = webserver:register_file("rackam.js", "htdocs/rackam.coffee", "text/html")
file:add_filter("coffee -p -s")
file = webserver:register_file("rackam.css", "htdocs/rackam.scss", "text/css")
file:add_filter("scss")

print("Lua script finished.")
Blackbeard.rackam.still_running = true

