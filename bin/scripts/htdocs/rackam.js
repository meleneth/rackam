(function() {
  var Page, html_tr, load_author_headers_pager, load_author_screen, load_authors_pager, load_headers_pager, load_newsgroup_list_screen, load_newsgroup_screen, rackam_pager, readable_storage,
    __slice = Array.prototype.slice;

  rackam_pager = null;

  load_newsgroup_list_screen = function() {
    $("#celery").empty().append("<ul id=\"newsgroups-list\"></ul>");
    $("#breadcrumbs").empty();
    $("<li>Newsgroups</li>").click(function() {
      return load_newsgroup_list_screen().appendTo("#breadcrumbs");
    });
    return $.getJSON('newsgroups.cgi', function(data) {
      var ng, _i, _len, _results;
      _results = [];
      for (_i = 0, _len = data.length; _i < _len; _i++) {
        ng = data[_i];
        _results.push((function(ng) {
          return $("#newsgroups-list").append("<li>" + ng.name + "</li>").click(function() {
            return load_newsgroup_screen(ng);
          });
        })(ng));
      }
      return _results;
    });
  };

  $(function() {
    return load_newsgroup_list_screen();
  });

  Page = (function() {

    function Page(url, start, items_per_page, num_items, render_func) {
      this.url = url;
      this.start = start;
      this.items_per_page = items_per_page;
      this.num_items = num_items;
      this.render_func = render_func;
    }

    Page.prototype.get_num_pages = function() {
      return this.num_items / this.items_per_page;
    };

    Page.prototype.previous_page = function() {
      this.start = this.start - this.items_per_page;
      if (this.start < 0) this.start = 0;
      return this.load_page();
    };

    Page.prototype.next_page = function() {
      this.start = this.start + this.items_per_page;
      if (this.start > (this.num_items - this.items_per_page)) {
        this.start = this.num_items - this.items_per_page;
      }
      return this.load_page();
    };

    Page.prototype.load_page = function() {
      return $.getJSON(this.url + ";page_ipp=" + this.items_per_page + ";page_first=" + this.start, this.render_func);
    };

    Page.prototype.create_ui = function() {
      $("#pager").empty().append("<div id=\"pager-ui\"></div>").append("<div><table id=\"pager-data\"></table></div>");
      $('<input type="button" value="&lt;-"></input>').css("font-size", "48px").click(function() {
        return eval("rackam_pager.previous_page();");
      }).appendTo("#pager-ui");
      return $('<input type="button" value="-&gt;"></input>').css("font-size", "48px").css("margin-left", "100px").click(function() {
        return eval("rackam_pager.next_page();");
      }).appendTo("#pager-ui");
    };

    return Page;

  })();

  html_tr = function() {
    var element, elements, result, _fn, _i, _len;
    elements = 1 <= arguments.length ? __slice.call(arguments, 0) : [];
    result = [];
    result.push("<tr>");
    _fn = function(element) {
      result.push("<td>");
      result.push(element);
      return result.push("</td>");
    };
    for (_i = 0, _len = elements.length; _i < _len; _i++) {
      element = elements[_i];
      _fn(element);
    }
    result.push("</tr>");
    return result.join("");
  };

  readable_storage = function(number) {
    var length;
    length = number.length;
    if (length > 12) return number.slice(0, -12) + "TB";
    if (length > 9) return number.slice(0, -9) + "GB";
    if (length > 6) return number.slice(0, -6) + "MB";
    if (length > 6) return number.slice(0, -3) + "kB";
    return number;
  };

  load_authors_pager = function(newsgroup) {
    var loader_func;
    loader_func = function(data) {
      var author, _i, _len, _results;
      $("#pager-data").empty().append("<tr><th>Name</th><th>PostSets</th><th>PostFiles</th><th>Headers</th><th>Bytes Posted</th></tr>");
      _results = [];
      for (_i = 0, _len = data.length; _i < _len; _i++) {
        author = data[_i];
        _results.push((function(author) {
          var cell, row;
          row = $("<tr></tr>");
          cell = $("<td>" + author.name + "</td>");
          cell.click(function() {
            return load_author_screen(newsgroup, author);
          });
          row.append(cell);
          $("<td>" + author.num_postsets + "</td>").appendTo(row);
          $("<td>" + author.num_postfiles + "</td>").appendTo(row);
          $("<td>" + author.num_headers + "</td>").appendTo(row);
          $("<td>" + readable_storage(author.size) + "</td>").appendTo(row);
          return row.appendTo("#pager-data");
        })(author));
      }
      return _results;
    };
    rackam_pager = new Page("/authors.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_authors, loader_func);
    rackam_pager.create_ui();
    return rackam_pager.load_page();
  };

  load_author_headers_pager = function(newsgroup, author) {
    var loader_func, url;
    loader_func = function(data) {
      var header, _i, _len, _results;
      $('#pager-data').empty().append("<tr><th>Subject</th><th>Author</th><th># bytes</th></tr>");
      _results = [];
      for (_i = 0, _len = data.length; _i < _len; _i++) {
        header = data[_i];
        _results.push((function(header) {
          return $(html_tr(header.subject, header.posted_by, readable_storage(header.size))).appendTo("#pager-data");
        })(header));
      }
      return _results;
    };
    url = "/author_headers.cgi?ng=" + newsgroup.name + ";author_id=" + author.id;
    rackam_pager = new Page(url, 0, 30, newsgroup.num_headers, loader_func);
    rackam_pager.create_ui();
    return rackam_pager.load_page();
  };

  load_headers_pager = function(newsgroup) {
    var loader_func;
    loader_func = function(data) {
      var header, _i, _len, _results;
      $('#pager-data').empty().append("<tr><th>Subject</th><th>Author</th><th># bytes</th></tr>");
      _results = [];
      for (_i = 0, _len = data.length; _i < _len; _i++) {
        header = data[_i];
        _results.push((function(header) {
          return $(html_tr(header.subject, header.posted_by, readable_storage(header.size))).appendTo("#pager-data");
        })(header));
      }
      return _results;
    };
    rackam_pager = new Page("/newsgroup_headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers, loader_func);
    rackam_pager.create_ui();
    return rackam_pager.load_page();
  };

  load_newsgroup_screen = function(ng) {
    $("#celery").empty().append("<div id=\"newsgroup\"><h1>" + ng.name + "</h1><ul id=\"newsgroup-items\"></ul></div>").append("<div id=\"pager\"></div>");
    $("<li id=\"ng-headers\">Headers</li>").click(function() {
      return load_headers_pager(ng);
    }).appendTo("#newsgroup-items");
    $("#newsgroup-items").append("<li>PostSets</li><li>PostFiles</li>");
    return $("<li>Authors</li>").click(function() {
      return load_authors_pager(ng);
    }).appendTo("#newsgroup-items");
  };

  load_author_screen = function(ng, author) {
    $("#celery").empty().append("<div id=\"author\"><h1>" + author.name + "</h1><ul id=\"author-items\"></ul></div>").append("<div id=\"pager\"></div>");
    $("#breadcrumbs").empty();
    $("<li>" + ng.name + "</li>").click(function() {
      return load_newsgroup_screen(ng);
    }).appendTo("#breadcrumbs");
    $("<li>Authors</li>").click(function() {
      return load_authors_pager(ng);
    }).appendTo("#breadcrumbs");
    $("<li>" + author.num_headers + " Headers</li>").click(function() {
      return load_author_headers_pager(ng, author);
    }).appendTo("#author-items");
    $("<li>" + author.num_postsets + " PostSets</li>").click(function() {
      return load_author_postsets_pager(ng, author);
    }).appendTo("#author-items");
    return $("<li>" + author.num_postfiles + " PostFiles</li>").click(function() {
      return load_author_postfiles_pager(ng, author);
    }).appendTo("#author-items");
  };

}).call(this);
