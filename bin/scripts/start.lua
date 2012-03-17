JSON = (loadfile "JSON.lua")() -- one-time load of the routines

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
  output['posted_by'] = header.posted_by
  output['num_bytes'] = header.num_bytes

  return JSON:encode(output)
end

function web_response_newsgroups(webresponse)
  local response_lines = {}
  local i;
  local max_i = Blackbeard.rackam.newsgroups:size() - 2
  for i = 0, max_i do
    local ng = Blackbeard.rackam.newsgroups[i]
    table.insert(response_lines, newsgroup_as_json(ng))
  end
  webresponse.body = "<html><head></head><body>" .. table.concat(response_lines, "\n") .. "</body></html>"
end

function web_response_newsgroup_headers(newsgroup, webresponse)
  local response_lines = {}
  local i;
  local max_i = newsgroup.headers:size() - 2

  for i = 0, max_i do
    local header = newsgroup.headers[i]
    table.insert(response_lines, header_as_json(header))
  end
  webresponse.body = "<html><head></head><body>" .. table.concat(response_lines, "<br />\n") .. "</body></html>"
end

function handle_web_request(webrequest, webresponse)
  if webrequest.path == "/" then
    if webrequest.filename == "newsgroup_headers.cgi" then
      local ng = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
      web_response_newsgroup_headers(ng, webresponse)
      return
    end
    if webrequest.filename == "newsgroups.cgi" then
      local ng = Blackbeard.rackam:newsgroup_for_name(webrequest:param("ng"))
      web_response_newsgroups(webresponse)
      return
    end
  end
end

Blackbeard.rackam:newsgroup_for_name("alt.binaries.movies.divx")
Blackbeard.rackam:newsgroup_for_name("alt.binaries.erotica.divx")
Blackbeard.rackam:newsgroup_for_name("alt.binaries.multimedia")

local n = Blackbeard.rackam:newsgroup_for_name("alt.binaries.multimedia.cartoons")

Blackbeard.rackam:load_headers_from_file(n, "headers_snipper.log")

Blackbeard.rackam.webserver:register_file("index.html", "htdocs/index.html")
Blackbeard.rackam.webserver:register_file("favicon.ico", "htdocs/favicon.ico")
Blackbeard.rackam.webserver:register_file("jquery.js", "htdocs/jquery-1.7.1.min.js")
Blackbeard.rackam.webserver:register_file("rackam", "htdocs/rackam.js")

print("Lua script finished.")

