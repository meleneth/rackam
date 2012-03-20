/*
this.$OuterDiv = $('<div></div>')
  .hide()
  .append($('<table></table>')
    .attr({ cellSpacing : 0 })
    .addClass("text")
  )
);
*/

function Page(url, start, items_per_page, num_items) {
  this.url = url;
  this.start = start;
  this.items_per_page = items_per_page;
  this.num_items = num_items;
}

Page.prototype.get_num_pages = function () {
  return this.num_items / this.items_per_page;
};

Page.prototype.previous_page = function() {
  this.start = this.start - this.items_per_page;
  if(this.start < 0) {
    this.start = 0;
  }
  this.load_page();
}

Page.prototype.next_page = function() {
  this.start = this.start + this.items_per_page;
  if(this.start > (this.num_items - this.items_per_page)) {
    this.start = this.num_items - this.items_per_page;
  }
  this.load_page();
}

Page.prototype.load_page = function() {
  $.getJSON(this.url + ";page_ipp=" + this.items_per_page + ";page_first=" + this.start, function(data) {
    $('#newsgroup-headers').empty();

    $.each(data, function(i, header) {
      $("#newsgroup-headers")
        .append("<li>"+header.subject+"</li>")
        .css("text-decoration", "underline");
    });
  });
}

/*
$.getJSON('ajax/test.json', function(data) {
  var items = [];

  $.each(data, function(key, val) {
    items.push('<li id="' + key + '">' + val + '</li>');
  });

  $('<ul/>', {
    'class': 'my-new-list',
    html: items.join('')
  }).appendTo('body');
});
*/

rackam_pager = null;

function load_newsgroup_pager(newsgroup) {
  $("#celery").empty();
  $("#celery").append("<div id=\"newsgroup-pager\"></div><div><ul id=\"newsgroup-headers\"></ul></div>");

  rackam_pager = new Page("/newsgroup_headers.cgi?ng=" + newsgroup.name, 0, 30, newsgroup.num_headers);

  $('<a>&lt;-</a>').click(function() {
    rackam_pager.previous_page();
  }).appendTo("#newsgroup-pager");

  $('<a>-&gt;</a>').click(function() {
    rackam_pager.next_page();
  }).appendTo("#newsgroup-pager");

  rackam_pager.load_page();

}

function setup_initial_screen() {
  $("#newsgroups").click(function() {
    $("#celery").empty();
    $("#celery").append("<ul id=\"newsgroups-list\"></ul>")

    $.getJSON('newsgroups.cgi', function(data) {
      $.each(data, function(i, ng) {
        $("#newsgroups-list")
          .append("<li>" + ng.name + "</li>")
          .css("text-decoration", "underline")
          .click(function() {
            load_newsgroup_pager(ng)
          });
      });
    });
  });
}

