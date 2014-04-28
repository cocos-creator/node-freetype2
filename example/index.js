var fs = require('fs'),
    freetype = require('../build/Release/freetype2');

fs.readFile(process.argv[2], function(err, buffer) {
  if (!!err) throw err;
  var fontface = freetype.parse(buffer);
  console.log(fontface.kerning.length);

    if (!fontface.kerning) {
        console.log("NO KERNING!");
        return;
    }
  // console.log(fontface.kerning);
  console.log("----");
  for (var i=0; i<fontface.kerning.length; i++) {
    var kern = fontface.kerning[i];
    if (kern.value)
        console.log(kern);
  }

});


// kerning: [
//     { left: 250, right: 150, kern: 50 }
// ]