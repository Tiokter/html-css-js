 var images = [
    'img/slider/1.png', 
    'img/slider/2.png',
    'img/slider/3.png',
    'img/slider/4.png',
    'img/slider/5.png', 
    'img/slider/6.png'
];
var num = 0;
function next() {
    var slider = document.getElementById('slider');
    num++;
    if(num >= images.length) {
        num = 0;
    }
    slider.src = images[num];
}
function prev() {
    var slider = document.getElementById('slider');
    num--;
    if(num < 0) {
        num = images.length-1;
    }
    slider.src = images[num];
}
var nextPic = setInterval (next, 4000);