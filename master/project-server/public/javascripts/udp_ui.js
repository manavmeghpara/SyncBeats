"use strict";
// Client-side interactions with the browser.

var errorTimer ;

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	socket.on('commandReply', function(result) {
		clearTimeout(errorTimer);
		$('#err').hide();
		var reply = result.split(" ");
	
		if(reply[0] === "Volume")
			setVolume(reply[1]);
		else if(reply[0] === "update")
		{
			setVolume(reply[1]);
			setTempo(reply[2]);
			setMode(reply[3]);
			updateUptime(reply[4]);
		}

	});

})

document.addEventListener("DOMContentLoaded", function() {
    const audioPlayer = document.getElementById("audioPlayer");
    const playBtn = document.getElementById("playBtn");
    const pauseBtn = document.getElementById("pauseBtn");
    const prevBtn = document.getElementById("prevBtn");
    const nextBtn = document.getElementById("nextBtn");
    const volumeControl = document.getElementById("volumeControl");

    playBtn.addEventListener("click", function() {
        audioPlayer.play();
        sendCommandViaUDP("play");
    });

    pauseBtn.addEventListener("click", function() {
        audioPlayer.pause();
        sendCommandViaUDP("pause");
    });

    prevBtn.addEventListener("click", function() {
        sendCommandViaUDP("previous");
    });

    nextBtn.addEventListener("click", function() {
        sendCommandViaUDP("next");
    });

    volumeControl.addEventListener("input", function() {
        var v = (this.value).toString();
        console.log(v);
        audioPlayer.volume = this.value / 100;
		var str = "volume " + v; 
		sendCommandViaUDP(str);
    });
});

function sendCommandViaUDP(message) {
	
	socket.emit('daUdpCommand', message);
	errorTimer = setTimeout(()=>{
		$('#err').show();
	}, 2000)
};

