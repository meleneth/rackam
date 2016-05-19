angular.module 'newUi'
  .factory 'DataBroker', ($resource) ->
    DataBroker = {}
    DataBroker.Newsgroup = $resource('http://rinzler:4242/n/:newsgroupName')
    return DataBroker
