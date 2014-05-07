/**
* SlidePebbleServer acts as a bridge between the Pebble app and the client, web-based presentation.
* It handles HTTP POST requests from the Pebble app and pushes them to the client through a Web Socket.
*/
var express = require('express')(),
    http = require('http'),
    socketio = require('socket.io'),
    server = http.createServer(express),
	  io = socketio.listen(server),
	  config = {
	    port : 3030,
      previousSlideEvent : 'previousSlide',
      nextSlideEvent : 'nextSlide',
      listenPath : '/SlideController/listen',
      previousSlidePath : '/SlideController/previous',
      nextSlidePath : '/SlideController/next'
	  },
	  listenSockets = io.of(config.listenPath);

express.post(config.previousSlidePath, function(req, res) {
  console.log('POST ' + config.previousSlidePath);
  listenSockets.emit(config.previousSlideEvent);
  res.send();
});

express.post(config.nextSlidePath, function(req, res) {
  console.log('POST ' + config.nextSlidePath);
  listenSockets.emit(config.nextSlideEvent);
  res.send();
});


listenSockets.on('connection', function (socket) {
  console.log('Listen socket connected');
  
  socket.on('disconnect', function () {
    console.log('Listen socket disconnected');
  });
});

server.listen(config.port);

console.log('Listening on http://localhost:' + config.port + '/');