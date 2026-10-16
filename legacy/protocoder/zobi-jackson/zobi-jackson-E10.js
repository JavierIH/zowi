//gui
ui.setScreenMode("immersive");
device.setScreenAlwaysOn(true);
ui.setScreenOrientation('landscape'); 
ui.allowScroll(false);
ui.setBackgroundColor("#ff5252")
ui.setBackgroundImage("fondo_rojo.png");

//video and layers 
var video = ui.addVideoView("Zobi.mp4", 100, 120, 720 * 2, 480 * 2);

ui.addImage("zobi.png", ui.screenWidth - 1200, ui.screenHeight - 340);
var playBack = ui.addImage("play_back.png", 140, 220);
var playImg = ui.addImage("play.png", 200, 240);

var loopPlayAlpha;
var countAlpha = 1;
loopPlayAlpha = util.loop(1500, function() {
    if (countAlpha++ % 2 == 0) {
        ui.alpha(playImg, 1);
    } else {
        ui.alpha(playImg, 0);
    }
}); 
loopPlayAlpha.pause(false);

util.delay(1000, function() {
    ui.alpha(playBack, 0); 
    ui.alpha(playImg, 0); 
});

var videPlaying = false;
var playBig = ui.addImageButton(650, 350, 400, 400,"play_big.png", false, function(val){ 
    video.play();
    network.sendBluetoothSerial("X");
    ui.jump(playBig);
    device.vibrate(200);
    ui.alpha(playBig, 0);
    ui.move(playBig, 2000, 350);
    ui.alpha(playBack, 1); 
    ui.alpha(playImg, 1); 
    loopPlayAlpha.pause(false);
    videoPlaying = true;
});
ui.alpha(playBig, 0.7);

network.connectBluetoothSerialByMac("98:D3:31:B2:DB:2D", function(m, data) {});

var videoInit = false;
video.onUpdate(function(q, ms, totalDuration) { 
    if(!videoInit){
        video.pause();
        video.setLoop(false);
        videoInit = true;
    } 
    
    if (ms >= totalDuration && videoPlaying) {
        videoPlaying = false;
        ui.alpha(playBig, 0.7);
        ui.move(playBig, 650, 350);
        ui.alpha(playBack, 0); 
        ui.alpha(playImg, 0); 
        loopPlayAlpha.pause(false);
    }
    console.log(ms + " " + totalDuration);
});

