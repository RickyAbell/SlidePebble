var statusElement = document.getElementById('slideStatus');
var currentSlide = 1;

function setSlideStatus() {
  statusElement.innerText = currentSlide;  
}

function previousSlide() {
  currentSlide--;
  setSlideStatus();
}

function nextSlide() {
  currentSlide++;
  setSlideStatus();
}

setSlideStatus();

initSlidePebble('http://10.0.0.106:3030/SlideController/listen', previousSlide, nextSlide);