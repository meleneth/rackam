angular.module 'newUi'
  .config ($routeProvider) ->
    'ngInject'
    $routeProvider
      .when '/',
        templateUrl: 'app/main/main.html'
        controller: 'MainController'
        controllerAs: 'main'
      .when '/rackam',
        templateUrl: 'app/rackam/rackam.html'
        controller: 'RackamController'
        controllerAs: 'rackam'
      .otherwise
        redirectTo: '/'
