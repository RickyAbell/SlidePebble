#SlidePebble

![SlidePebbleScreenshot](http://i.imgur.com/XGZ1LYj.png)

Do you have a web-based presentation, for example something built on [reveal.js](http://lab.hakim.se/reveal-js/#/), that you want to control from your Pebble Smartwatch? Slide Pebble provides all of the components to give you that power.

##Design
SlidePebble is separated into 3 parts

###Pebble
The app that runs on your Pebble and allows you to select next or previous slide.

###Server
A node.js app that acts as the bridge between the Pebble app and the web-based client. It listens for HTTP POST requests from the Pebble app and immediately pushes those requests to the client through Web Sockets via socket.io. Multiple clients can have open socket connections at the same time and a message from the Pebble app will be broadcast to all of them, this allows you to open your presentation on multiple devices and have them all update when an action is selected on the Pebble.

###Client
A JavaScript file to include in your presentation that opens the socket connection and triggers callbacks on next slide and previous slide events.

##Installation
###Server
Install [Node](http://nodejs.org/download/)

Navigate to the folder *server*

Install dependencies `npm install`

Run it `node slidePebbleServer.js`

###Pebble
Install the [Pebble SDK](https://developer.getpebble.com/2/getting-started/)

Configure server details, open pebble/slide-pebble/src/js/pebble-app.js and update
```JavaScript
var SLIDE_CONTROLLER_URL = 'http://10.0.0.106:3030/SlideController';
```
to the address of your server.

Navigate to the folder pebble/slide-pebble

Build `pebble build`

Install `pebble install`

###Client
Add the following to your web-based presentation

Load the socket.io script
```HTML
<script src="http://x.x.x.x:3030/socket.io/socket.io.js"></script>
```
where x.x.x.x is the address that slidePebbleServer.js is running on

Load the slidePebble.js file
```HTML
<script src="slidePebble.js"></script>
```

Initialize slidePebble by passing the url of your server and callbacks for previous and next slide events.
```JavaScript
initSlidePebble('http://x.x.x.x:3030/SlideController/listen', previousSlide, nextSlide);
```

##Future work
Some potential features for the future are
* Move server url out of the Pebble app and let it be set by the Pebble iOS/Android app configuration window using Pebble JavaScript. This requires hosting for the configuration page.
* Display a timer in the Pebble app.
* Display slide number in the Pebble app.
* Display speaker notes in the Pebble app.