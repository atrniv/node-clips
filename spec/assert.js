var clips = require('../lib/index');
var util = require('util');
var env = new clips.Environment();

env.initialize(function(){
  env.build('(deftemplate duck (multislot var))', function(){
    console.log(util.inspect(env.facts(), { depth: 6, colors: true }));
    env.assert(['duck', [['var', ['x', 'y']]]], function(err, fact){
      console.log(util.inspect(env.facts(), { depth: 6, colors: true }));
      env.dispose(function(){
        console.log('environment disposed');
      });
    });
  });
});
