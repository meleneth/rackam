rackam_pager = null

load_newsgroup_list_screen = ->
  $("#celery")
    .empty()
    .append("<ul id=\"newsgroups-list\"></ul>")

  $("#breadcrumbs")
    .append("<li>Newsgroups</li>")

  $.getJSON 'newsgroups.cgi', (data) ->
    for ng in data
      do (ng) ->
        $("#newsgroups-list")
          .append("<li>" + ng.name + "</li>")
          .click -> load_newsgroup_screen(ng)

$ ->
  `load_newsgroup_list_screen()`

class Page
  constructor: (url, start, items_per_page, num_items, render_func) ->
    @url = url
    @start = start
    @items_per_page = items_per_page
    @num_items = num_items
    @render_func = render_func

  get_num_pages: ->
    @num_items / @items_per_page

  previous_page: ->
    @start = @start - @items_per_page
    @start = 0 if @start < 0
    @load_page()

  next_page: ->
    @start = @start + @items_per_page
    @start = @num_items - @items_per_page if @start > (@num_items - @items_per_page)
    @load_page()

  load_page: ->
    $.getJSON(@url + ";page_ipp=" + @items_per_page + ";page_first=" + @start, @render_func)

  create_ui: ->
    $("#pager")
      .empty()
      .append("<div id=\"pager-ui\"></div>")
      .append("<div><table id=\"pager-data\"></table></div>")

    $('<input type="button" value="&lt;-"></input>')
      .css("font-size", "48px")
      .click(-> eval "rackam_pager.previous_page();")
      .appendTo("#pager-ui")

    $('<input type="button" value="-&gt;"></input>')
      .css("font-size", "48px")
      .css("margin-left", "100px")
      .click(-> eval "rackam_pager.next_page();")
      .appendTo("#pager-ui")

html_tr = (elements...) ->
  result = []
  result.push "<tr>"
  for element in elements
    do (element) ->
      result.push "<td>"
      result.push element
      result.push "</td>"
  result.push "</tr>"
  result.join ""
      

load_authors_pager = (newsgroup) ->
  loader_func = (data) ->
    $('#pager-data').empty()
    $("#pager-data").append("<tr><th>Name</th><th>PostSets</th><th>PostFiles</th><th>Headers</th><th>Bytes Posted</th></tr>")
    for author in data
      do (author) ->
        $(html_tr(author.name, author.num_postsets, author.num_postfiles, author.num_headers, author.size))
          .appendTo("#pager-data")
  rackam_pager = new Page("/authors.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_authors, loader_func)
  rackam_pager.create_ui()
  rackam_pager.load_page()
  
load_headers_pager = (newsgroup) ->
  loader_func = (data) ->
    $('#pager-data').empty()
    $("#pager-data").append("<tr><th>Subject</th><th>Author</th><th># bytes</th></tr>")
    for header in data
      do (header) ->
        $(html_tr(header.subject, header.posted_by, header.size))
          .appendTo("#pager-data")

  rackam_pager = new Page "/newsgroup_headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_newsgroup_screen = (ng) ->
  $("#celery")
    .empty()
    .append("<div id=\"newsgroup\"><h1>" + ng.name + "</h1><ul id=\"newsgroup-items\"></ul></div>")
    .append("<div id=\"pager\"></div>")

  $("#newsgroup-items").append
  $("<li id=\"ng-headers\">Headers</li>")
    .click(-> load_headers_pager(ng))
    .appendTo("#newsgroup-items")

  $("#newsgroup-items").append "<li>PostSets</li><li>PostFiles</li>"
  $("<li>Authors</li>")
    .click(-> load_authors_pager(ng))
    .appendTo("#newsgroup-items")

