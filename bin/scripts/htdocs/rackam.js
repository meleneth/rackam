/*
this.$OuterDiv = $('<div></div>')
  .hide()
  .append($('<table></table>')
    .attr({ cellSpacing : 0 })
    .addClass("text")
  )
);

function Page(url, start, items_per_page, num_items) {
  this.url = url;
  this.start = start;
  this.items_per_page = items_per_page;
  this.num_items = num_items;
}

Page.prototype.get_num_pages = function () {
  return this.num_items / this.items_per_page;
};

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

function load_newsgroup_pager(newsgroup) {
  $("#celery").empty();
  $("#celery").append("<div></div><div><ul id=\"newsgroup-headers\"></ul></div>")
  $.getJSON("newsgroup_headers.cgi?ng=" + newsgroup + ";pager_ipp=30", function(data) {
    $.each(data, function(i, header) {
      $("#newsgroup-headers").append("<li>"+header.subject+"</li>");
    });
  });
}

function setup_initial_screen() {
  $("#newsgroups").click(function() {
    $("#celery").empty();
    $("#celery").append("<ul id=\"newsgroups-list\"></ul>")

    $.getJSON('newsgroups.cgi', function(data) {
      $.each(data, function(i, ng) {
        $("#newsgroups-list")
          .append("<li>" + ng.name + "</li>")
          .click(function() {
            load_newsgroup_pager(ng.name)
          });
      });
    });
  });
}

