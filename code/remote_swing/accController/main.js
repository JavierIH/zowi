var ax, ay;
var raw_x, raw_y, raw_z;

var command;

sensors.startAccelerometer(function(x, y, z) {
    raw_x=x;
    raw_y=y;
    raw_z=z;
    ax=parseInt((raw_x+10)*5);
    ay=parseInt((raw_y+10)*5);
});

ui.addButton("Conectar bluetooth", 10, 10, function() {
    network.connectBluetoothSerialByMac("98:D3:31:B2:DB:76", function(m, data) { //zob
    });
})

ui.addButton("Desconectar", 10, 120, function() {
    network.disconnectBluetooth();
})

function setup() {
    util.loop(10, loop);
} 

function loop() { 
    command=String.fromCharCode(0);
    command+=String.fromCharCode(ax);
    command+=String.fromCharCode(ay);
    network.sendBluetoothSerial(command);
    console.log(command);
} 

