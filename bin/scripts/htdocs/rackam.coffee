rackam_pager = null

setup_initial_screen = ->
  $("#newsgroups").click ->
    $("#celery")
      .empty()
      .append("<ul id=\"newsgroups-list\"></ul>")

    $.getJSON 'newsgroups.cgi', (data) ->
      $.each data, (i, ng) ->
        $("#newsgroups-list")
          .append("<li>" + ng.name + "</li>")
          .click -> load_newsgroup_screen(ng)

$ ->
  `setup_initial_screen()`

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
    $.getJSON(@url + ";page_ipp=" + @items_per_page + ";page_first=" + @start, @render_func);

  create_ui: ->
    $("#pager")
      .empty()
      .append("<div id=\"pager-ui\"></div>")

    $('<input type="button" value="&lt;-"></input>')
      .css("font-size", "48px")
      .click(-> eval "rackam_pager.previous_page();")
      .appendTo("#pager-ui");

    $('<input type="button" value="-&gt;"></input>')
      .css("font-size", "48px")
      .css("margin-left", "100px")
      .click(-> eval "rackam_pager.next_page();")
      .appendTo("#pager-ui");


load_newsgroup_pager = (newsgroup) ->
  loader_func = (data) -> 
    $('#newsgroup-headers').empty()
    $.each data, (i, header) ->
      $("#newsgroup-headers").append "<tr><td>"+header.subject + "</td><td>" + header.posted_by + "</td><td>" + header.num_bytes + "</td></tr>"
  rackam_pager = new Page "/newsgroup_headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers, loader_func
  $("#celery").append "<div><table id=\"newsgroup-headers\"></table></div>"
  rackam_pager.create_ui();
  rackam_pager.load_page()



load_newsgroup_screen = (ng) ->
  $("#celery")
    .empty()
    .append("<div id=\"newsgroup\"><h1>" + ng.name + "</h1><ul id=\"newsgroup-items\"></ul></div>")
    .append("<div id=\"pager\"></div>")


  $("#newsgroup-items").append "<li id=\"ng-headers\">Headers</li>"
  $("#ng-headers").click -> load_newsgroup_pager(ng)

  $("#newsgroup-items").append "<li>PostSets</li><li>PostFiles</li><li>Authors</li></ul>"

