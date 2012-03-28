(function() {
  var Page, load_newsgroup_pager, load_newsgroup_screen, rackam_pager, setup_initial_screen;

  rackam_pager = null;

  setup_initial_screen = function() {
    return $("#newsgroups").click(function() {
      $("#celery").empty().append("<ul id=\"newsgroups-list\"></ul>");
      return $.getJSON('newsgroups.cgi', function(data) {
        return $.each(data, function(i, ng) {
          return $("#newsgroups-list").append("<li>" + ng.name + "</li>").click(function() {
            return load_newsgroup_screen(ng);
          });
        });
      });
    });
  };

  $(function() {
    return setup_initial_screen();
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
      $("#pager").empty().append("<div id=\"pager-ui\"></div>");
      $('<input type="button" value="&lt;-"></input>').css("font-size", "48px").click(function() {
        return eval("rackam_pager.previous_page();");
      }).appendTo("#pager-ui");
      return $('<input type="button" value="-&gt;"></input>').css("font-size", "48px").css("margin-left", "100px").click(function() {
        return eval("rackam_pager.next_page();");
      }).appendTo("#pager-ui");
    };

    return Page;

  })();

  load_newsgroup_pager = function(newsgroup) {
    var loader_func;
    loader_func = function(data) {
      $('#newsgroup-headers').empty();
      return $.each(data, function(i, header) {
        return $("#newsgroup-headers").append("<tr><td>" + header.subject + "</td><td>" + header.posted_by + "</td><td>" + header.num_bytes + "</td></tr>");
      });
    };
    rackam_pager = new Page("/newsgroup_headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers, loader_func);
    $("#celery").append("<div><table id=\"newsgroup-headers\"></table></div>");
    rackam_pager.create_ui();
    return rackam_pager.load_page();
  };

  load_newsgroup_screen = function(ng) {
    $("#celery").empty().append("<div id=\"newsgroup\"><h1>" + ng.name + "</h1><ul id=\"newsgroup-items\"></ul></div>").append("<div id=\"pager\"></div>");
    $("#newsgroup-items").append("<li id=\"ng-headers\">Headers</li>");
    $("#ng-headers").click(function() {
      return load_newsgroup_pager(ng);
    });
    return $("#newsgroup-items").append("<li>PostSets</li><li>PostFiles</li><li>Authors</li></ul>");
  };

}).call(this);
