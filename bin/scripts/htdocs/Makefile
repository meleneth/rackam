all : rackam.js index.html rackam.css

rackam.js : rackam.coffee
	coffee -c rackam.coffee

index.html : index.haml
	haml index.haml > index.html

rackam.css : rackam.scss
	scss rackam.scss > rackam.css
