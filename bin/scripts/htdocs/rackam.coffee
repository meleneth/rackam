rackam_pager = null

rackam_setup = ->
  $("#newsgroups-link").click -> load_newsgroup_list_screen()
  load_newsgroup_list_screen()

reset_pager = ->
  $('#pager-data thead').empty()
  $('#pager-data tbody').empty()

reset_ui = ->
  $("#newsgroup-list-screen").hide()
  $('#newsgroups-list').empty()
  $("#breadcrumbs").empty()
  $('#filter-info').hide()
  $('#pager').hide()
  reset_pager()

load_newsgroup_list_screen = ->
  reset_ui()

  $("#newsgroup-list-screen").show()

  $.getJSON 'newsgroups.cgi', (data) ->
    for ng in data
      do (ng) ->
        $("#newsgroups-list")
          .append("<li>" + ng.name + "</li>")
          .click -> load_newsgroup_screen(ng)

$ ->
  `rackam_setup()`

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
    $('#prev-page-button').click(-> eval "rackam_pager.previous_page();")
    $('#next-page-button').click(-> eval "rackam_pager.next_page();")
    $('#pager').show()

html_tr = (elements...) ->
  result = []
  for element in elements
    do (element) ->
      result.push "<td>"
      result.push element
      result.push "</td>"
  result_row = $(document.createElement("tr"))
  $(result.join("")).appendTo(result_row)
  result_row


html_trh = (elements...) ->
  result = []
  result.push "<tr>"
  for element in elements
    do (element) ->
      result.push "<th>"
      result.push element
      result.push "</th>"
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
  $("#newsgroup-name").text(newsgroup.name)
  
  loader_func = (data) ->
    $("#pager-data thead")
      .empty()
      .append(html_trh("Name", "PostSets", "PostFiles", "Headers", "Bytes Posted"))

    for author in data
      do (author) ->
        row = html_tr(author.name, author.num_postsets, author.num_postfiles, author.num_headers, readable_storage(author.size))
        row.first().click(-> load_author_screen(newsgroup, author))
        row.appendTo("#pager-data tbody")

  rackam_pager = new Page("/authors.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_authors, loader_func)
  rackam_pager.create_ui()
  rackam_pager.load_page()
  
load_author_headers_pager = (newsgroup, author) ->
  $('#pager-data thead')
    .empty()
    .append(html_trh("Subject", "Author", "# bytes"))

  loader_func = (data) ->
    for header in data
      do (header) ->
        $(html_tr(header.subject, header.posted_by, readable_storage(header.size)))
          .appendTo("#pager-data tbody")

  url = "/headers.cgi?ng=" + newsgroup.name + ";author_id=" + author.id
  rackam_pager = new Page url, 0, 30, newsgroup.num_headers, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_headers_pager = (newsgroup) ->
  reset_ui()
  $('#pager').show()

  loader_func = (data) ->
    $('#pager-data thead')
      .append(html_trh("Subject", "Author", "# Bytes"))

    for header in data
      do (header) ->
        $(html_tr(header.subject, header.posted_by, readable_storage(header.size)))
          .appendTo("#pager-data tbody")

  rackam_pager = new Page "/headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_postfiles_pager = (newsgroup) ->
  reset_pager()
  $('#pager-data thead')
    .append(html_trh("PostFile Name", "Author", "# bytes"))

  loader_func = (data) ->
    for postfile in data
      do (postfile) ->
        $(html_tr(postfile.name, postfile.posted_by, readable_storage(postfile.size)))
          .appendTo("#pager-data tbody")

  rackam_pager = new Page "/newsgroup_postfiles.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_postfiles, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_filters_pager = (ng) ->
  reset_ui()
  $('#filter-info').show()
  $('#pager').show()
  $('#pager-data thead').empty().append(html_trh("Filter", "# Matches"))
  $('#pager-data tbody').empty()

  loader_func = (data) ->
    for filter in data
      do (filter) ->
        $(html_tr(filter.text, filter.num_matched))
          .appendTo("#pager-data tbody")

  rackam_pager = new Page "/filters.cgi?ng=" + ng.name, 0, 30, ng.num_postfiles, loader_func
  rackam_pager.create_ui()
  rackam_pager.load_page()

load_newsgroup_screen = (ng) ->
  reset_ui()

  $("#newsgroup-name").text(ng.name)

  $("#newsgroup-screen-headers").click(-> load_headers_pager(ng))
  $("#newsgroup-screen-filters").click(-> load_filters_pager(ng))
  $("#newsgroup-screen-authors").click(-> load_authors_pager(ng))
  $("#newsgroup-screen-authors-count").text(ng.num_authors)
  $("#authors-link").click(-> load_authors_pager(ng))

  $("#newsgroup-screen").show()

load_author_screen = (ng, author) ->
  reset_ui()
  $("#author-screen-name").text(author.name)

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
    .click(-> load_author_postfiles_pager(ng, outho ))
    .appendTo("#author-items")
