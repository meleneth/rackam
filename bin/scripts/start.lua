JSON = (loadfile "JSON.lua")() -- one-time load of the routines

function newsgroup_as_json(newsgroup)
  output = {}

  output['name'] = newsgroup.name
  output['min_message_no'] = newsgroup.min_message_no
  output['max_message_no'] = newsgroup.max_message_no

  return JSON:encode_pretty(output)
end

n = Blackbeard.Newsgroup()

n.name = "alt.binaries.divx"
n.min_message_no = 42
n.max_message_no = 400000004

print(newsgroup_as_json(n))

