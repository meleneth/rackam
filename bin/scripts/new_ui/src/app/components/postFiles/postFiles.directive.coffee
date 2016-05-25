angular.module 'newUi'
  .directive 'postFiles', ->

    postFilesController = ->
      'ngInject'
      vm = this
      # "vm.creation" is avaible by directive option "bindToController: true"
      return

    directive =
      restrict: 'E'
      templateUrl: 'app/components/postFiles/postFiles.html'
      scope: postFiles: '=files'
      controller: postFilesController
      controllerAs: 'vm'
      bindToController: true
