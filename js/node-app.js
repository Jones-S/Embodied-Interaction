// required when running on node.js
var mqtt = require('mqtt'); // only for node.js
var csv = require('csv');



var fs = require("fs");
var path = "data.txt";
var data = "GSR Data: \n";

fs.writeFile(path, data, function(error) {
     if (error) {
       console.error("write error:  " + error.message);
     } else {
       console.log("Successful Write to " + path);
     }
});




// var info = [
//     ["foo", "bar"],
//     ["hello", "world"]
// ];

// info.forEach(function(line) {
//   csv.from(line).to(fs.createWriteStream(path, {flags: 'a'}))
// });






var client = mqtt.connect('mqtt://try:try@broker.shiftr.io', {
    clientId: 'jones-macbook.js'
});

client.on('connect', function(){
    console.log('client has connected!');

    client.subscribe('/jones-channel.n');
    // client.unsubscribe('/example');

    setInterval(function(){
        client.publish('/jones-macbook-output', 'http://csv.adaltas.com/\'s documentation is shit!');
    }, 10000);
});

client.on('message', function(topic, message) {

    console.log('New Message:', topic, message.toString());
    var currentdate = new Date();
    var datetime = currentdate.getDate() + "/"
                + (currentdate.getMonth()+1)  + "/"
                + currentdate.getFullYear() + " @ "
                + currentdate.getHours() + ":"
                + currentdate.getMinutes() + ":"
                + currentdate.getSeconds();
    fs.appendFile('data.txt',  datetime + ": \t" + message.toString().trim() + "\n", function (err) {

    });

});
