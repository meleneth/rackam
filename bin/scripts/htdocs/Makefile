all : rackam.js index.html

rackam.js : rackam.coffee
	coffee -c rackam.coffee

index.html : index.haml
	haml index.haml > index.html
