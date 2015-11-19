// These values need to move to Pebble iOS/Android app configuration window using Pebble JavaScript
var SLIDE_CONTROLLER_URL = 'http://192.168.0.9:3030/SlideController';
var PREVIOUS_SLIDE_URL = SLIDE_CONTROLLER_URL + '/previous';
var NEXT_SLIDE_URL = SLIDE_CONTROLLER_URL + '/next';

function requestSlideChange(url) {
  var req = new XMLHttpRequest();
  req.open('POST', url, true);

  req.onload = function(e) {
    if (req.readyState === 4) {
      if(req.status === 200) {
        console.log('Slide change request successful');
      } else {
        console.log('Request returned error code ' + req.status.toString());
      }
    }
  };

  req.send(null);
}

function onPebbleMessage(e) {
  if (e.payload.previousSlide) {
    requestSlideChange(PREVIOUS_SLIDE_URL);
  }
  else if (e.payload.nextSlide) {
    requestSlideChange(NEXT_SLIDE_URL);
  }
}

//Fired when the Pebble app is ready
Pebble.addEventListener('ready',
                        function(e) {
                          console.log('pebble js ready ' + e.ready);
                        });

//Messages triggered by the Pebble app
Pebble.addEventListener('appmessage', onPebbleMessage);
