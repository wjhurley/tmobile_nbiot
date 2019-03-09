(function() {
  Pusher.logToConsole = true;

  var serverUrl = '/';
  var commands = [];
  var pusher = new Pusher('975919367ecae063ed32', {
    cluster: 'us3',
    encrypted: true
  });
  var channel = pusher.subscribe('m2m-commands');
  var boxCapacity = 12;

  channel.bind('new_command', newCommandReceived);

  function newCommandReceived(data) {
    console.log(data);
    var selectedBox = document.querySelector('#box-' + data.box);
    var selectedBoxCapacity = document.querySelector('#boxCapacity-' + data.box);
    var begin = data.command.indexOf('[') + 1;
    var end = data.command.indexOf(']');
    var boxSpaceRemaining = Number(data.command.substring(begin, end));
    var p = document.createElement('p');
    p.innerText = boxSpaceTaken;
    p.style.textAlign = 'center';
    // Our test box is 15cm and we want a 3cm buffer (max height of 12cm),
    // so if space remaining is greater than 3, we're good.
    if (boxSpaceRemaining > 3) {
      selectedBoxCapacity.innerText = boxSpaceTaken;
      selectedBox.style.backgroundColor = '#0F0';
    } else if (boxSpaceRemaining === 3) { // It fits, but barely...
      selectedBoxCapacity.innerText = boxSpaceTaken;
      selectedBox.style.backgroundColor = '#FF0';
    } else { // Sorry, box won't fit with the buffer we want
      selectedBox.style.backgroundColor = '#F00';
      alert('Box is too large for this location!');
    }
  }
})();
