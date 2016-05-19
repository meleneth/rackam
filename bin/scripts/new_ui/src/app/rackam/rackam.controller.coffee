angular.module 'newUi'
  .controller 'RackamController', ($timeout, webDevTec, toastr, DataBroker) ->
    'ngInject'
    vm = this
    activate = ->
      getWebDevTec()
      $timeout (->
        vm.classAnimation = 'rubberBand'
        return
      ), 4000
      return

    showToastr = ->
      toastr.info 'Fork <a href="https://github.com/Swiip/generator-gulp-angular" target="_blank"><b>generator-gulp-angular</b></a>'
      vm.classAnimation = ''
      return

    getWebDevTec = ->
      vm.awesomeThings = webDevTec.getTec()
      angular.forEach vm.awesomeThings, (awesomeThing) ->
        awesomeThing.rank = Math.random()
        return
      return

    vm.awesomeThings = []
    vm.hotness = 9001 # yes, it's over 9000
    vm.newsgroups = DataBroker.Newsgroup.query()
    console.log vm.newsgroups
    vm.classAnimation = ''
    vm.creationDate = 1463383974342
    vm.showToastr = showToastr
    activate()
    return
