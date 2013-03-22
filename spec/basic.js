var clips = require('../lib/index');
var util = require('util');
var env = new clips.Environment();
var file = __dirname + '/animal.clp';
var start = new Date();

console.log(process.memoryUsage());
env.initialize(function() {
  console.log('Initialized');
  env.load(file, function(err) {
    var now = new Date();
    console.log(now-start);
    if (err) throw err;
    console.log('file loaded');
    env.reset(function(err) {
      if (err) throw err;
      console.log('environment reset');
      env.facts();
      //console.log(util.inspect(env.facts(), { depth: 6 }));
      console.log(process.memoryUsage());
      env.evaluate('(run)', function(err, numRules) {
        if (err) throw err;
        //console.log(util.inspect(env.facts(), { depth: 6 }));
        console.log(util.inspect(numRules, { depth: 6, colors: true }));
        env.dispose(function(){
          console.log(process.memoryUsage());
          console.log('environment disposed');
        });
      });
    });
  });
});

