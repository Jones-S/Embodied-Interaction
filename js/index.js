(function ($) { // iief = Immediately-Invoked Function Expression, mainly useful to limit scope
    $(function() { // Shorthand for $( document ).ready()

        // required when running on node.js
        // var mqtt = require('mqtt'); // only for node.js

        var client = mqtt.connect('mqtt://try:try@broker.shiftr.io', {
            clientId: 'jones-macbook.js'
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

            console.log('New Message:', topic, message.toString());
            $('.arduino-values').append(message.toString() + "<br>");

        });

    });
}(jQuery));