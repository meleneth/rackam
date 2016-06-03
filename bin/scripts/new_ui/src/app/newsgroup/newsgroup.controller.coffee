angular.module 'newUi'
  .controller 'NewsgroupController', ($timeout, DataBroker, $routeParams, $scope) ->
    'ngInject'
    vm = this

    $scope.load_postfiles = ->
      console.log "your wish, my want"

    $scope.posted_files = {filename: "BIG BADA BOOM"}

    vm.awesomeThings = []
    vm.hotness = 9001 # yes, it's over 9000
    vm.newsgroups = DataBroker.Newsgroup.query()
    vm.newsgroup_name = $routeParams["newsgroup_name"]
    DataBroker.NewsgroupPostfiles.query {newsgroupName: vm.newsgroup_name, page_ipp: 200}, (data) ->
      vm.postfiles = data
    console.log $routeParams
    console.log vm.newsgroup_name
    return
