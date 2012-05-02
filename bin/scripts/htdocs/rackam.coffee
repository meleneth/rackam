rackam_pager = null

load_newsgroup_list_screen = ->
  $("#celery")
    .empty()
    .append("<ul id=\"newsgroups-list\"></ul>")

  $("#breadcrumbs")
    .empty()

  $("<li>Newsgroups</li>")
    .click -> load_newsgroup_list_screen()
    .appendTo("#breadcrumbs")

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

readable_storage = (number) ->
  length = number.length
  return number.slice(0, -12) + "TB" if length > 12
  return number.slice(0, -9) + "GB" if length > 9
  return number.slice(0, -6) + "MB" if length > 6
  return number.slice(0, -3) + "kB" if length > 6
  return number

load_authors_pager = (newsgroup) ->
  loader_func = (data) ->
    $("#pager-data")
      .empty()
      .append("<tr><th>Name</th><th>PostSets</th><th>PostFiles</th><th>Headers</th><th>Bytes Posted</th></tr>")
    for author in data
      do (author) ->
        row = $("<tr></tr>")
        cell = $("<td>" + author.name + "</td>")
        cell.click -> load_author_screen(newsgroup, author)
        row.append(cell)
        
        $("<td>" + author.num_postsets + "</td>")
          .appendTo(row)
        $("<td>" + author.num_postfiles + "</td>")
          .appendTo(row)
        $("<td>" + author.num_headers + "</td>")
          .appendTo(row)
        $("<td>" + readable_storage(author.size) + "</td>")
          .appendTo(row)

        row
          .appendTo("#pager-data")

  rackam_pager = new Page("/authors.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_authors, loader_func)
  rackam_pager.create_ui()
  rackam_pager.load_page()
  
load_author_headers_pager = (newsgroup, author) ->
  loader_func = (data) ->
    $('#pager-data')
      .empty()
      .append("<tr><th>Subject</th><th>Author</th><th># bytes</th></tr>")
    for header in data
      do (header) ->
        $(html_tr(header.subject, header.posted_by, readable_storage(header.size)))
          .appendTo("#pager-data")

  url = "/headers.cgi?ng=" + newsgroup.name + ";author_id=" + author.id
  rackam_pager = new Page url, 0, 30, newsgroup.num_headers, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_headers_pager = (newsgroup) ->
  loader_func = (data) ->
    $('#pager-data')
      .empty()
      .append("<tr><th>Subject</th><th>Author</th><th># bytes</th></tr>")
    for header in data
      do (header) ->
        $(html_tr(header.subject, header.posted_by, readable_storage(header.size)))
          .appendTo("#pager-data")

  rackam_pager = new Page "/headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_postfiles_pager = (newsgroup) ->
  load_func = (data) ->
    $('#pager-data')
      .empty()
      .append("<tr><th>PostFile Name</th><th>Author</th><th># bytes</th></tr>")
    for postfile in data
      do (postfile) ->
        $(html_tr(postfile.name, postfile.posted_by, readable_storage(postfile.size)))
          .appendTo("#pager-data")
  rackam_pager = new Page "/newsgroup_postfiles.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_postfiles, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()
    
load_newsgroup_screen = (ng) ->
  $("#celery")
    .empty()
    .append("<div id=\"newsgroup\"><h1>" + ng.name + "</h1><ul id=\"newsgroup-items\"></ul></div>")
    .append("<div id=\"pager\"></div>")

  $("<li id=\"ng-headers\">Headers</li>")
    .click(-> load_headers_pager(ng))
    .appendTo("#newsgroup-items")

  $("#newsgroup-items")
    .append "<li>PostSets</li><li>PostFiles</li>"

  $("<li>Authors</li>")
    .click(-> load_authors_pager(ng))
    .appendTo("#newsgroup-items")

load_author_screen = (ng, author) ->
  $("#celery")
    .empty()
    .append("<div id=\"author\"><h1>" + author.name + "</h1><ul id=\"author-items\"></ul></div>")
    .append("<div id=\"pager\"></div>")

  $("#breadcrumbs")
    .empty()

  $("<li>" + ng.name + "</li>")
    .click(-> load_newsgroup_screen(ng))
    .appendTo("#breadcrumbs")

  $("<li>Authors</li>")
    .click(-> load_authors_pager(ng))
    .appendTo("#breadcrumbs")

  $("<li>" + author.num_headers + " Headers</li>")
    .click(-> load_author_headers_pager(ng, author))
    .appendTo("#author-items")

  $("<li>" + author.num_postsets + " PostSets</li>")
    .click(-> load_author_postsets_pager(ng, author))
    .appendTo("#author-items")

  $("<li>" + author.num_postfiles + " PostFiles</li>")
    .click(-> load_author_postfiles_pager(ng, author))
    .appendTo("#author-items")


