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

function setup_initial_screen() {
  $("#celery").append("<ul id=\"newsgroups-list\"></ul>")

  $("#newsgroups").click(function() {
    $.getJSON('newsgroups.cgi', function(data) {
      $.each(data, function(i, ng) {
        $("#newsgroups-list").append("<li>" + ng.name + "</li>");
      });
    });
  });
}

