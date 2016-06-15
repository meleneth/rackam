angular.module 'newUi'
  .controller 'RackamController', ($timeout, webDevTec, toastr, DataBroker) ->
    'ngInject'
    vm = this
    vm.newsgroups = DataBroker.Newsgroup.query()
    return
