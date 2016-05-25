angular.module 'newUi'
  .directive 'postFiles', ->

    postFilesController = (moment) ->
      'ngInject'
      vm = this
      # "vm.creation" is avaible by directive option "bindToController: true"
      vm.relativeDate = moment(vm.creationDate).fromNow()
      return

    directive =
      restrict: 'E'
      templateUrl: 'app/components/postfiles/postfiles.html'
      scope: creationDate: '='
      controller: postFilesController
      controllerAs: 'vm'
      bindToController: true
