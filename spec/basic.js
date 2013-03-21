var clips = require('../lib/index');

var env = new clips.Environment();
var file = __dirname + '/animal.clp';
var start = new Date();

env.load(file, function(err) {
  var now = new Date();
  console.log(now-start);
  if (err) throw err;
  console.log('file loaded');
  env.reset(function(err) {
    if (err) throw err;
    console.log('environment reset');
    env.run(-1, function(err, numRules) {
      if (err) throw err;
      console.log(numRules + ' rules fired');
    });
  });
});
