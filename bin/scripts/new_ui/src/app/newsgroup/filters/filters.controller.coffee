angular.module 'newUi'
  .controller 'FiltersController', ($timeout, DataBroker, $routeParams, $scope) ->
    'ngInject'
    vm = this

    vm.newsgroup_name = $routeParams["newsgroup_name"]
    DataBroker.NewsgroupFilters.query {newsgroupName: vm.newsgroup_name, page_ipp: 200}, (data) ->
      $scope.filters = data
    return
