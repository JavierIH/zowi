/*
*   Client for the Oscillator server v2
*   
*   Control the oscillators with Sliders
*   
*   (c) Juan Gonzalez Gomez (Obijuan). Feb-2015
*   GPL v2 license
*   
*/

const MAC = "98:D3:31:B2:DB:76";

const CMD_PLAY = 'P';
const CMD_STOP = 'S';
const CMD_SET_A = 'A';
const CMD_SET_O = 'O';
const CMD_SET_Ph = 'H';
const CMD_SET_T = 'T';
const CMD_END = '\r';

//-- Create the oscillators
var a = new Oscillator('a');
var b = new Oscillator('b');
var c = new Oscillator('c');
var d = new Oscillator('d');

//-- configure the trim
a.trim = -18;
b.trim = 7;
c.trim = -6;
d.trim = -11;

//-- Setup the bluetooth connection
/*
network.connectBluetoothSerialByUi(
function(m, data) {
      console.log(data);
      console.log("Conectado")
});
*/

var connection = false;

network.connectBluetoothSerialByMac(MAC, function(data){ 
  console.log(data)
  console.log("Conectado")
  connection = true;
});


//--- Robot initialization
ui.addButton("Init", 20, 20, 300, 120, function() { 
	home();
});


//-- left keypad 
ui.addButton("F", 140, 120 * 2, 120, 120, function() { 
	walk_f();
});

ui.addButton("S", 140, 120 * 3, 120, 120, function() { 
	home();
});

ui.addButton("B", 140, 120 * 4, 120, 120, function() { 
	walk_b();
});

ui.addButton("<", 20, 120 * 3, 120, 120, function() { 
    turn_r();
});

ui.addButton(">", 140 * 2 - 20, 120 * 3, 110, 120, function() { 
    turn_l();
});


//-- right keypad 
ui.addButton("F", 140*4, 120 * 2, 120, 120, function() { 
	flap_f();
});

ui.addButton("S", 140*4, 120 * 3, 120, 120, function() { 
	home();
});

ui.addButton("B", 140*4, 120 * 4, 120, 120, function() { 
	flap_b();
});

ui.addButton("<", 140*3 + 20, 120 * 3, 120, 120, function() { 
    moonwalker_l();
});

ui.addButton(">", 140 * 3 + 140 * 2 - 20, 120 * 3, 110, 120, function() { 
    moonwalker_r();
});

//-- Robot home position
function home()
{
    console.log("Home");
    
    //-- Amplitudes
    a.set_A(0);  b.set_A(0); c.set_A(0); d.set_A(0);
    
    //-- Offsets
    a.set_O(a.trim); b.set_O(b.trim); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Play
    a.play();  b.play();  c.play();  d.play()
}

function walk_f()
{
    console.log("Walk f");
    
   
    //--Period
    a.set_T(1000); b.set_T(1000);  c.set_T(1000);  d.set_T(1000);
    
    //-- Offsets
    a.set_O(a.trim); b.set_O(b.trim); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(0);  c.set_Ph(90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(30); d.set_A(30);
}


function walk_b()
{
    console.log("Walk b");
    
   
    //--Period
    a.set_T(1000); b.set_T(1000);  c.set_T(1000);  d.set_T(1000);
    
    //-- Offsets
    a.set_O(a.trim); b.set_O(b.trim); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(0);  c.set_Ph(-90);  d.set_Ph(-90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(30); d.set_A(30);
}

function turn_l()
{
    console.log("turn-l");
    
   
    //--Period
    a.set_T(3000); b.set_T(3000);  c.set_T(3000);  d.set_T(3000);
    
    //-- Offsets
    a.set_O(a.trim); b.set_O(b.trim); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(0);  c.set_Ph(90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(30); d.set_A(10);
}

function turn_r()
{
    console.log("turn-r");
    
   
    //--Period
    a.set_T(3000); b.set_T(3000);  c.set_T(3000);  d.set_T(3000);
    
    //-- Offsets
    a.set_O(a.trim); b.set_O(b.trim); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(0);  c.set_Ph(90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(10); d.set_A(30);
}

function flap_f()
{
    console.log("flap f");
    
   
    //--Period
    a.set_T(1000); b.set_T(1000);  c.set_T(1000);  d.set_T(1000);
    
    //-- Offsets
    a.set_O(a.trim -5); b.set_O(b.trim+5); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(180);  c.set_Ph(90);  d.set_Ph(-90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(8); d.set_A(8);
}

function flap_b()
{
    console.log("flap b");
    
   
    //--Period
    a.set_T(1000); b.set_T(1000);  c.set_T(1000);  d.set_T(1000);
    
    //-- Offsets
    a.set_O(a.trim -5); b.set_O(b.trim+5); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(180);  c.set_Ph(-90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(8); d.set_A(8);
}

function moonwalker_r()
{
    console.log("Moonwalker r");
    
   
    //--Period
    a.set_T(1000); b.set_T(1000);  c.set_T(1000);  d.set_T(1000);
    
    //-- Offsets
    a.set_O(a.trim -15); b.set_O(b.trim+15); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(180 + 120);  c.set_Ph(90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(25);  b.set_A(25); c.set_A(0); d.set_A(0);
}

function moonwalker_l()
{
   console.log("Moonwalker l");
    
   
    //--Period
    a.set_T(1000); b.set_T(1000);  c.set_T(1000);  d.set_T(1000);
    
    //-- Offsets
    a.set_O(a.trim -15); b.set_O(b.trim+15); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(180 - 120);  c.set_Ph(90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(25);  b.set_A(25); c.set_A(0); d.set_A(0);
}


//--------- Oscillator Cass
function Oscillator(dir)
{
    this.dir = dir;    //-- Servo identificator
    this._A = 45;     //-- Current amplitude
    this._O = 0;
    this._Ph = 0;
    this._T = 2000;
    this.trim = 0;
    
    //-- Play
    this.play = function() {
        var frame = this.dir + CMD_PLAY + CMD_END;
        network.sendBluetoothSerial(frame);
        console.log(frame);
    }
    
    //-- Stop
    this.stop = function() {
        var frame = this.dir + CMD_STOP + CMD_END;
        network.sendBluetoothSerial(frame);
        console.log(frame);
    }
    
    //-- Set the amplitude
    this.set_A = function(A) {
        
        //-- Only integer values
        A = Math.round(A);
        
        //-- Update the servo only if there is a change
        if (A != this._A) {
            var frame = this.dir + CMD_SET_A + A + CMD_END
            network.sendBluetoothSerial(frame);
            this._A = A;
            console.log(frame);
        }
    }
    
    //-- Set the offset
    this.set_O = function(O) {
        
        //-- Only integer values
        O = Math.round(O);
        
        //-- Update the servo only if there is a change
        if (O != this._O) {
            var frame = this.dir + CMD_SET_O + O + CMD_END
            network.sendBluetoothSerial(frame);
            this._O = O;
            console.log(frame);
        }
    }
    
    //-- Set the offset
    this.set_Ph = function(Ph) {
        
        //-- Only integer values
        Ph = Math.round(Ph);
        
        //-- Update the servo only if there is a change
        if (Ph != this._Ph) {
            var frame = this.dir + CMD_SET_Ph + Ph + CMD_END
            network.sendBluetoothSerial(frame);
            this._Ph = Ph;
            console.log(frame);
        }
    }
    
    //-- Set the offset
    this.set_T = function(T) {
        
        //-- Only integer values
        T = Math.round(T);
        
        //-- Update the servo only if there is a change
        if (T != this._T) {
            var frame = this.dir + CMD_SET_T + T + CMD_END
            network.sendBluetoothSerial(frame);
            this._T = T;
            console.log(frame);
        }
    }

}


