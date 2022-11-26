/*
 back.js 
 Author: Stefano Gregis 329936 Giorgio Ajmone 329846
 Date: 18/11/2022
*/

//Loading modules
const execFile = require('child_process').execFile;
var http = require('http');
var fs = require('fs');
var path = require('path');

//global variable to save the type of plant
// 4 -> manual mode
// 0,1,2,3 -> a specific kind of plant with specific parameters
let plant = 4;
//matrix with parameters for each plant
const plantList = [
    [15, 25, 40, 70, 40],
    [10, 20, 40, 80, 10],
    [18, 20, 20, 30, 80],
    [25, 70, 10, 120, 5]
] // temperature, light, humidity

// Initialize the server on port 8888
var server = http.createServer(function (req, res) {
    // requesting files
    let file = '.'+((req.url=='/')?'/front.html':req.url);
    let fileExtension = path.extname(file);
    let contentType = 'text/html';

    if(fileExtension == '.css'){
        contentType = 'text/css';
    }
    fs.exists(file, function(exists){
        if(exists){
            fs.readFile(file, function(error, content){
                if(!error){
                    // Page found, write content
                    res.writeHead(200,{'content-type':contentType});
                    res.end(content);
                }
            });
        }
        else{
            // Page not found
            res.writeHead(404);
            res.end('Page not found');
        }
    });
}).listen(8888, console.log("Server Running ..."));

// Loading socket io module.
var io = require('socket.io')(server);

//when connection is established
io.on('connection', function (socket) {
    //catch event generated
    socket.on('changeH',  (data) => {
        plant = 4;
        let newData = JSON.parse(data);
        console.log("HEATER =" + newData.state);
        //turns heater on or off
        Heater(newData.state);
    });
    socket.on('changeW',  (data) => {
        plant = 4;
        let newData = JSON.parse(data);
        console.log("WINDOW = " + newData.state);
        // OPEN OR CLOSES WINDOW
        Window(newData.state);
    });
    socket.on('changeL', (data) => {
        plant = 4;
        console.log("LIGHT = " + data +" %");
        //SET light to a specific value
        Light(data);
    });

    // On call from Browser execute files
    socket.on('update', function handleSensor() {
        //execute humidity and temperature script
        THSensor();
        //execute script to read light level
        LightSensor();
    });
    socket.on('plantSelection', (data) => {
        plant = data;
        console.log("MODE: " + data);
    });
});

let updateInterval = setInterval(automate, 10000);

//Window: function to run the executable that controls servo motor
//Input:  0 or 180
//Returned values: none
function Window(state) {
    const window = execFile('sudo',['./servoControl', state],{cwd: '/home/debian/greenhouse'} , (error, stdout, stderr) => {
        if(error) {
            console.error('stderr', stderr);
            throw error;
        }
    });
}
//Light: function to run the executable that controls the LED module
//Input:  value between 0 and 100
//Returned values: none
function Light(intensity) {
    const lightLevelexec=execFile('sudo',['./LEDcontrol', intensity],{cwd: '/home/debian/greenhouse'},(error, stdout, stderr) => {
        if(error) {
            console.error('stderr', stderr);
            throw error;
        }
    });
}

//Light: function to run the executable that controls the LED module
//Input: "on" or "off"
//Returned values: none
function Heater(state){
    const heater = execFile('sudo',['./HeaterControl', state],{cwd: '/home/debian/greenhouse'},(error, stdout1, stderr) => {
        if(error) {
            console.error('stderr', stderr);
            throw error;
        }
    });
}

//LightSensor: function to run the executable that reads the light value
//Input:  none
//Returned values: none, emits an event called 'sensorLight' that will give to the client a JSON object containing the measures
function LightSensor(){
    const lightLevel = execFile('./LightSensor',{cwd: '/home/debian/greenhouse'}, (error, stdout1, stderr) => {
		if(error) {
			console.error('stderr', stderr);
			throw error;
		}
        var data = {light:stdout1};
        var dataJSON = JSON.stringify(data);
		io.emit('sensorLight', dataJSON);
    });
}

//THSensor: function to run the executable that reads the values for Temperature and Humidity
//Input:  none
//Returned values: none, emits an event called 'sensorTH' that will give to the client a JSON object containing the measures
function THSensor(){
    const tempHum = execFile('./readTempHum',{cwd: '/home/debian/greenhouse'}, (error, stdout, stderr) => {
		if(error) {
			console.error('stderr', stderr);
			throw error;
		}

        var stdoutNew=stdout.split(' ');
        var data = {humidity: parseInt(stdoutNew[0]),temperature:parseInt(stdoutNew[1])};
        var dataJSON = JSON.stringify(data);
		io.emit('sensorTH', dataJSON);
    });
}


//Water: function to run the executable that controls the 2nd servo
//Input:  "0" or "180"
//Returned values: none
function Water(state) {
    const water = execFile('sudo',['./waterControl', state],{cwd: '/home/debian/greenhouse'} , (error, stdout, stderr) => {
        if(error) {
            console.error('stderr', stderr);
            throw error;
        }
    });
}
//automate: function called every 10 seconds that checks if the measures are inside the boundaries (if one of the plants is chosen, therefore when plant is not 4)
//if the value is out of the boundaries the executables to open/close window, turn on/off the heater and so on are called.
//Input:  none
//Returned values: none
function automate() {
    const lightLevel = execFile('./LightSensor',{cwd: '/home/debian/greenhouse'}, (error, stdout1, stderr) => {
		if(error) {
			console.error('stderr', stderr);
			throw error;
		}
        var data = parseFloat(stdout1);
        if(plant !== 4) {
            if (plantList[plant][2] > data) {
                Light(100);
            }
            if (plantList[plant][3] < data) {
                Light(0);
            }
        }
    });

    const tempHum = execFile('./readTempHum',{cwd: '/home/debian/greenhouse'}, (error, stdout, stderr) => {
		if(error) {
			console.error('stderr', stderr);
			throw error;
		}

        var stdoutNew=stdout.split(' ');
        var data1 = parseFloat(stdoutNew[0]);
        var data2 = parseFloat(stdoutNew[1]);
        if(plant !== 4) {
            if (plantList[plant][0] > data2) {
                Heater(1);
            }
            if (plantList[plant][1] < data2) {
                Heater(0);
            }
            if (plantList[plant][4] > data1){
                Water(1);
                setTimeout(Water, 1000, 0);
            }
        }
    });
}
