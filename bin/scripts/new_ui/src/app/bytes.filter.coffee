angular.module 'newUi'
  .filter 'bytes', ->
    (bytes, precision) ->
      return '-' if isNaN(parseFloat bytes) || !isFinite bytes

      precision = 1 if typeof(precision) == 'undefined'
      units = ['bytes', 'kB', 'MB', 'GB', 'TB', 'PB']

      number = Math.floor(Math.log(bytes) / Math.log(1024))
      value = Math.floor number
      value = Math.pow 1024, value
      value = bytes / value
      value = value.toFixed precision
      "#{value} #{units[number]}"

