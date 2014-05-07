/**
* This will setup the socket.io connection and call the provided callbacks when appropriate
* @method initSlidePebble
* @param {String} url The url to slidePebbleServer
* @param {Object} previousSlideCallback Will be called on a previous slide event
* @param {Object} nextSlideCallback Will be called on a next slide event
*/
function initSlidePebble(url, previousSlideCallback, nextSlideCallback) {
  if (typeof io === 'undefined') {
    throw 'SlidePebble requires socket.io to have been loaded but io is undefined.';
  }

  var socket = io.connect(url);

  socket.on('previousSlide', function (data) {
    previousSlideCallback();
  });

  socket.on('nextSlide', function (data) {
    nextSlideCallback();
  });
}