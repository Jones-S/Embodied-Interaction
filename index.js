// required when running on node.js
var mqtt = require('mqtt');

var client = mqtt.connect('mqtt://try:try@broker.shiftr.io', {
  clientId: 'jones.js'
});

client.on('connect', function(){
  console.log('client has connected!');

  client.subscribe('/jones-channel.n');
  // client.unsubscribe('/example');

  setInterval(function(){
    client.publish('/hello', 'world');
  }, 1000);
});

client.on('message', function(topic, message) {
  console.log('new message:', topic, message.toString());
});