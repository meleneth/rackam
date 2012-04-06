JSON = (loadfile "JSON.lua")() -- one-time load of the routines

function web_escape(s)
  s = string.gsub(s, "&", "&amp;")
  s = string.gsub(s, ">", "&gt;")
  s = string.gsub(s, "<", "&lt;")
  return s
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
  output['name'] = web_escape(postfile.subject)
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

function web_response_newsgroups(webresponse)
  local response_lines = {}
  local i;
  local max_i = Blackbeard.rackam.newsgroups:size() - 1
  for i = 0, max_i do
    local ng = Blackbeard.rackam.newsgroups[i]
    table.insert(response_lines, newsgroup_as_json(ng))
  end
  webresponse.body = "[\n" .. table.concat(response_lines, ",\n") .. "]\n"
end

function web_response_newsgroup_author_headers(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
  local author = newsgroup:author_for_id(webrequest:paramn("author_id"))
  local response_lines = {}
  local i;
  local max_i = author.headers:size() - 1
  local page_ipp = webrequest:paramn("page_ipp")
  local page_first = webrequest:paramn("page_first")
  if page_ipp   == 0 then page_ipp = 20 end
  local page_last = page_first + page_ipp
  if page_last > max_i then page_last = max_i end

  for i = page_first, page_last do
    local header = author.headers[i]
    table.insert(response_lines, header_as_json(header))
  end
  webresponse.body = "[\n" .. table.concat(response_lines, ",\n") .. "]\n"
end

function web_response_newsgroup_headers(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))

  local response_lines = {}
  local i;
  local max_i = newsgroup.headers:size() - 1
  local page_ipp = webrequest:paramn("page_ipp")
  local page_first = webrequest:paramn("page_first")
  if page_ipp   == 0 then page_ipp = 20 end
  local page_last = page_first + page_ipp
  if page_last > max_i then page_last = max_i end

  for i = page_first, page_last do
    local header = newsgroup.headers[i]
    table.insert(response_lines, header_as_json(header))
  end
  webresponse.body = "[\n" .. table.concat(response_lines, ",\n") .. "]\n"
end

function handle_web_request(webrequest, webresponse)
  if webrequest.path == "/" then
    if webrequest.filename == "authors.cgi" then
      web_response_authors(webrequest, webresponse)
      return
    end
    if webrequest.filename == "newsgroups.cgi" then
      web_response_newsgroups(webresponse)
      return
    end
    if webrequest.filename == "author_headers.cgi" then
      web_response_newsgroup_author_headers(webrequest, webresponse)
      return
    end
    if webrequest.filename == "newsgroup_headers.cgi" then
      web_response_newsgroup_headers(webrequest, webresponse)
      return
    end
  end
end

local n = Blackbeard.rackam:newsgroup_for_name("alt.binaries.multimedia.cartoons")
n:add_filter("(%e/%f) \"%a\"%d- yEnc (%p/%n)")
n:add_filter("%s [%e/%f] - \"%a\"%d yEnc (%p/%n)")

Blackbeard.rackam:load_headers_from_file(n, "headers_snipper.log")

Blackbeard.rackam.webserver:register_file("index.html", "htdocs/index.html")
Blackbeard.rackam.webserver:register_file("favicon.ico", "htdocs/favicon.ico")
Blackbeard.rackam.webserver:register_file("jquery.js", "htdocs/jquery-1.7.1.min.js")
Blackbeard.rackam.webserver:register_file("rackam.js", "htdocs/rackam.js")
Blackbeard.rackam.webserver:register_file("rackam.css", "htdocs/rackam.css")


print("Lua script finished.")
Blackbeard.rackam.still_running = false

