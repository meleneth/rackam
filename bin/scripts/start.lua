JSON = (loadfile "JSON.lua")() -- one-time load of the routines

function author_as_json(author)
  local output = {}

  output['name'] = author.name
  output['newsgroup'] = author.newsgroup.name
  if author.headers then
    output['num_headers'] = author.headers:size()
  end

  return JSON:encode(output)
end

function newsgroup_as_json(newsgroup)
  local output = {}

  output['name'] = newsgroup.name
  output['min_message_no'] = newsgroup:get_min_message_no_str()
  output['max_message_no'] = newsgroup:get_max_message_no_str()
  if newsgroup.headers then
    output['num_headers']    = newsgroup.headers:size()
  end

  return JSON:encode(output)
  --return JSON:encode_pretty(output)
end

function header_as_json(header)
  local output = {}
  
  output['msg_id']  = header.msg_id
  output['subject'] = header.subject
  output['article_no'] = header:get_article_no_str()
  output['posted_by'] = header.author.name
  output['num_bytes'] = header.num_bytes

  return JSON:encode(output)
end

function web_response_authors(webrequest, webresponse)
  local newsgroup = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
  local response_lines = {}
  local i;
  local max_i = newsgroup.authors:size() - 1
  for i = 0, max_i do
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
    if webrequest.filename == "newsgroup_headers.cgi" then
      web_response_newsgroup_headers(webrequest, webresponse)
      return
    end
  end
end

local n = Blackbeard.rackam:newsgroup_for_name("alt.binaries.multimedia.cartoons")

Blackbeard.rackam:load_headers_from_file(n, "headers_snipper.log")

Blackbeard.rackam.webserver:register_file("index.html", "htdocs/index.html")
Blackbeard.rackam.webserver:register_file("favicon.ico", "htdocs/favicon.ico")
Blackbeard.rackam.webserver:register_file("jquery.js", "htdocs/jquery-1.7.1.min.js")
Blackbeard.rackam.webserver:register_file("rackam.js", "htdocs/rackam.js")

print("Lua script finished.")

