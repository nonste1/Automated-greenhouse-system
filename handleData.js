/*
handleData.js 
Author: Stefano Gregis 329936 Giorgio Ajmone 329846
Date: 18/11/2022
*/



// Establishing connection with server
var socket = io.connect(); /* global io */
var updateInterval;


//Handler function called when an event 'sensorTH' is received. Updates the front page with the values
//contained in the JSON object given as a parameter
//Input:  JSON object given by the server
//Returned values: none  
socket.on('sensorTH', function(data) {
    var myData = JSON.parse(data);
    document.getElementById("currentTH0").innerHTML="Humitidy: "+myData.humidity+" %";
    document.getElementById("currentTH1").innerHTML="Temperature: " +myData.temperature+" C";
});
//Handler function called when an event 'sensorLight' is received. Updates the front page with the values
//contained in the JSON object given as a parameter
//Input:  JSON object given by the server
//Returned values: none  
socket.on('sensorLight', function(data) {
    var myData = JSON.parse(data);
    document.getElementById("currentL").innerHTML=  myData.light;
});


//changeStateLight: function called when the submit button is clicked
function changeStateLight(){
    let value=document.getElementById('inputL').textContent
    console.log("Light:" + value + " %");
    socket.emit("changeL", value);
    document.getElementById("plants").value=0;
    handlePlants(0);

}

//changeStateHeater: function called when the "on" or "off" buttons are clicked.
//Sends a message to the server containing the desired state for the heater
//updates the mode to manual
//Input: 0 or 1 (values corresponding to open or closed)
//Returned values: none
function changeStateHeater(value){
        if (value==1) {
            socket.emit('changeH', '{"state":"on"}');
            document.getElementById("currentH").innerHTML = "ON";
            document.getElementById("plants").value=0;
            handlePlants(0);
        } else  {
            socket.emit('changeH', '{"state":"off"}');
            document.getElementById("currentH").innerHTML = "OFF";
            document.getElementById("plants").value=0;
            handlePlants(0);
        }
}
//changeStateWindow: function called when the "open" or "closed" buttons are clicked.
//Sends a message to the server containing the desired state for the window
//updates the mode to manual
//Input: 0 or 180 (values corresponding to open or closed)
//Returned values: none
function changeStateWindow(value){
        if (value) {
            socket.emit('changeW', '{"state":"180"}');
            document.getElementById("currentW").innerHTML = "OPEN";
            document.getElementById("plants").value=0;
            handlePlants(0);
        } else{
            socket.emit('changeW', '{"state":"1"}');
            document.getElementById("currentW").innerHTML = "CLOSED";
            document.getElementById("plants").value=0;
            handlePlants(0);
        }
}
//setText: function called when the user selects a value with the range tool.
//Updates the text corresponding to the currently selected value
//Input: none
//Returned values: none
function setText(){
    let range = document.getElementById("setLight").value;
    console.log("Light:" + range + " %");
    document.getElementById("inputL").innerHTML=range;
}
//uppdate: calls readFromServer every second
//input values: none
//Returned values: none
function update() {
    updateInterval = setInterval(readFromServer, 1000);
}

//readFromServer: every time os called, emits an update message  every second
//input values: none
//Returned values: none
function readFromServer(){
    // Emit message to get data
    socket.emit('update');
}

//handlePlants: when a new plant is chose, the image is updated and the number of the plant selected is passed to the server
//input values: none
//Returned values: none
function handlePlants(){
var plant = document.getElementById("plants");
var value = plant.options[plant.selectedIndex].value;
if (value == 0) {  
    document.getElementById("imgPlant").src="questionmark.jpg"
    console.log(" nessuna pianta mod manuale");
}
if (value == 1) {  
    console.log(" cactus ");
    document.getElementById("imgPlant").src="cactus.jpg"
    socket.emit("plantSelection", 0);
    document.getElementById("currentW").innerHTML = "-";
    document.getElementById("currentH").innerHTML = "-";
    document.getElementById("inputL").innerHTML="-";
}
if (value == 2) {  
    console.log(" basil ");
    document.getElementById("imgPlant").src="healthy-basil.jpg"
    socket.emit('plantSelection', 1);
    document.getElementById("currentW").innerHTML = "-";
    document.getElementById("currentH").innerHTML = "-";
    document.getElementById("inputL").innerHTML="-";
}
if (value == 3) {
    console.log(" bonsai "); 
    document.getElementById("imgPlant").src="bonsai.jpg"
    socket.emit('plantSelection', 2);
    document.getElementById("currentW").innerHTML = "-";
    document.getElementById("currentH").innerHTML = "-";
    document.getElementById("inputL").innerHTML="-";
}
if (value == 4) { 
    console.log(" strawberry "); 
    document.getElementById("imgPlant").src="fragole.jpg"
    socket.emit('plantSelection', 3);
    document.getElementById("currentW").innerHTML = "-";
    document.getElementById("currentH").innerHTML = "-";
    document.getElementById("inputL").innerHTML="-";
}
}
