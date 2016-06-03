angular.module 'newUi'
  .factory 'DataBroker', ($resource) ->
    DataBroker = {}
    DataBroker.Newsgroup = $resource('http://rinzler:4242/n/:newsgroupName')
    DataBroker.NewsgroupAuthors = $resource('http://rinzler:4242/n/:newsgroupName/authors')
    DataBroker.NewsgroupPostfiles = $resource('http://rinzler:4242/n/:newsgroupName/postfiles')
    return DataBroker
