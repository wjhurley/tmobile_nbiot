var express = require('express');
var path = require('path');
var bodyParser = require('body-parser');
var Pusher = require('pusher');

var pusher = new Pusher({
  appId: '731735',
  key: '975919367ecae063ed32',
  secret: 'b40382cbff64629bc32e',
  cluster: 'us3',
  encrypted: true
});

var app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: false
}));

app.use(express.static(path.join(__dirname, 'public')));

app.post('/fromSIM', function(req, res) {
  console.log(req.body);
  var randomBox = Math.floor(Math.random() * 6) + 1;
  var newCommand = {
    box: randomBox,
    command: req.body.Command
  };
  pusher.trigger('m2m-commands', 'new_command', newCommand);
  res.json({
    created: true
  });
});

app.listen(9050, function() {
  console.log('Example app listening on port 9050!');
});

module.exports = app;
