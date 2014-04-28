var fs = require('fs'),
    freetype = require('../build/Release/freetype2');

fs.readFile(process.argv[2], function(err, buffer) {
  if (!!err) throw err;
  var fontface = freetype.parse(buffer);
  
  if (fontface.kerning) {
    console.log("Found", fontface.kerning.length, "kerning pairs");
  }
});