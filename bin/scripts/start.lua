JSON = (loadfile "JSON.lua")() -- one-time load of the routines

function newsgroup_as_json(newsgroup)
  output = {}

  output['name'] = newsgroup.name
  output['min_message_no'] = newsgroup:get_min_message_no_str()
  output['max_message_no'] = newsgroup:get_max_message_no_str()

  return JSON:encode_pretty(output)
end

function handle_web_request(webrequest, webresponse)

--  local ng = Blackbeard.rackam.newsgroups[1]
--  print("Newsgroup retrieved")
--  local response_text = newsgroup_as_json(ng)
--
--  webresponse.body = "<html><head></head><body>" .. response_text .. "</body></html>"
--  return
--end

  response_text = ""
  local i;
  local max_i = Blackbeard.rackam.newsgroups:size()
  for i = 0, max_i - 1 do
    local ng = Blackbeard.rackam.newsgroups[i]
    response_text = response_text .. newsgroup_as_json(ng)
  end
  webresponse.body = "<html><head></head><body>" .. response_text .. "</body></html>"
end

Blackbeard.rackam:newsgroup_for_name("alt.binaries.movies.divx")
Blackbeard.rackam:newsgroup_for_name("alt.binaries.erotica.divx")
Blackbeard.rackam:newsgroup_for_name("alt.binaries.multimedia")

print("Lua script finished.")

