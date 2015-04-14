/*
*	
*	Description: With this code you can control Scopum with your phone and Protocoder
*	by Hacklab UPM Bq Madrid
*
*/

const MAC = "98:D3:31:B2:DB:15"; 

const CMD_PLAY = 'P';
const CMD_STOP = 'S';
const CMD_SET_A = 'A';
const CMD_SET_O = 'O';
const CMD_SET_Ph = 'H';
const CMD_SET_T = 'T';
const CMD_END = '\r';

const CMD_UP = 'U';
const CMD_DOWN = 'D';
const CMD_SHOT = 'I';
const CMD_PNT_ON = '1';
const CMD_PNT_OFF = '0';

//-- Gaits comands
const GREEN_F = '1';
const GREEN_B = '2';
const GREEN_L = '3';
const GREEN_R = '4';

const BLUE_U = '10';//Weapon up
const BLUE_D = '20';//Weapon down
const RED_U = '30';//Arm up
const RED_D = '40';//Arm down

const STOP = '100';
const SHOT = '101';//Shot
const PNT_ON = '102';//Pointer on
const PNT_OFF = '103';//Pointer off
const DEGREES = '5';//Degrees moved by the command
const SHOT_TIME = '500';//Shot time in miliseconds

//-- Setup the bluetooth connection


network.connectBluetoothSerialByUi(
function(m, data) {
      console.log(data);
      console.log("Conectado")
});

//console.log(ui.screenWidth, ui.screenHeight)

var bluetoothOn = false;
var connection = false;

/*network.connectBluetoothSerialByMac(MAC, function(data){ 
  console.log(data);
  console.log("Conectado");
  bluetoothOn = true;
});*/

util.delay(8000, function(){
  console.log("Delay...");
  console.log("bluettothOn: " + bluetoothOn);
  connection = true;
  home();
  init_gui();
});


ui.setBackgroundColor("#FFFFFF");
ui.setScreenMode("immersive");
device.setScreenAlwaysOn(true);
ui.setScreenOrientation('landscape');

ui.addImage("fondo.png",0, 0, 1280, 720);

w = h = 130;
x = 120; y = 400;

function addMyButton(mx, my, mimage, cmd)
{
  var btn = ui.addImageButton(mx, my, w, h, mimage, false, function(val)
  {
    console.log(cmd);
    device.vibrate(200);
    ui.jump(btn);
    switch(cmd) {
        case GREEN_F:
            walk_f();
            break;
        case GREEN_B:
            walk_b();
            break;
        case GREEN_R:
            turn_r();
            break;
        case GREEN_L:
            turn_l();
            break;
        case BLUE_D:
            weapon_up();
            break;
        case BLUE_U:
            weapon_down();
            break;
        case RED_U:
            arm_up();
            break;
        case RED_D:
            arm_down();
            break;
        case SHOT:
            shot();
            break;
        case PNT_ON:
            pointerOn();
            break;
        case PNT_OFF:
            pointerOff();
            break;
        case STOP:
            home();
            break;
    }
    
  }); 
  
  
  
  return btn;
}

//-- Create the oscillators
var a = new Oscillator('a');
var b = new Oscillator('b');
var c = new Oscillator('c');
var d = new Oscillator('d');

//-- Create the servos
var sWeapon = 'e';
var sArm = 'f';
var sHead = 'g';
var weapon = 'w';

//-- configure the trim
a.trim = -2;
b.trim = 3;
c.trim = -2;
d.trim = -11;

function init_gui() {
    
    var btnGF = addMyButton(x + w, y + h, "mover_hacia_atras.png", GREEN_B);
    var btnGL = addMyButton(x, y, "mover_izquierda.png", GREEN_R);
    var btnGR = addMyButton(x + 2*w, y, "mover_derecha.png", GREEN_L);
    var btnGB = addMyButton(x + w, y - h, "mover_hacia_delante.png", GREEN_F);

    var btnBF = addMyButton(2.5 * x + 3*w + 20, y - h, "izquierdo_arriba.png", BLUE_U);//BLUE_UP weapon up 
    var btnBB = addMyButton(2.5 * x + 3*w + 20, y + h, "izquierdo_abajo.png", BLUE_D);//BLUE_DOWN weapon down
    var btnRF = addMyButton(2.5 * x + 5*w + 80, y - h, "derecho_arriba.png", RED_U);//RED_UP arm up 
    var btnRB = addMyButton(2.5 * x + 5*w + 80, y + h, "derecho_abajo.png", RED_D);//RED_DOWN arm down

    var btnShot = addMyButton(2.5 * x + 4*w + 50, y, "disparo.png", SHOT);
    //var btnPntOn = addMyButton(2.5 * x + 4*w + 50, y + h, "laser_on.png", PNT_ON);
    //var btnPntOff = addMyButton(2.5 * x + 4*w + 50, y - h, "laser_off.png", PNT_OFF);

    var btnStop = addMyButton(525, 240,  "stop.png", STOP);
}


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
    a.set_T(2000); b.set_T(2000);  c.set_T(2000);  d.set_T(2000);
    
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
    a.set_T(2000); b.set_T(2000);  c.set_T(2000);  d.set_T(2000);
    
    //-- Offsets
    a.set_O(a.trim); b.set_O(b.trim); c.set_O(c.trim); d.set_O(d.trim);
    
    //-- Phases
    a.set_Ph(0);  b.set_Ph(0);  c.set_Ph(90);  d.set_Ph(90);
    
     //-- Amplitudes
    a.set_A(15);  b.set_A(15); c.set_A(10); d.set_A(30);
}

function weapon_up()
{
    var frame = sWeapon + CMD_UP + DEGREES + CMD_END;
    network.sendBluetoothSerial(frame); 
}

function weapon_down()
{
    var frame = sWeapon + CMD_DOWN + DEGREES + CMD_END;
    network.sendBluetoothSerial(frame); 
}

function arm_up()
{
    var frame = sArm + CMD_UP + DEGREES + CMD_END;
    network.sendBluetoothSerial(frame); 
}

function arm_down()
{
    var frame = sArm + CMD_DOWN + DEGREES + CMD_END;
    network.sendBluetoothSerial(frame); 
}

function shot(){
    var frame = weapon + CMD_SHOT + SHOT_TIME + CMD_END;
    network.sendBluetoothSerial(frame);
}

function pointerOn(){
    var frame = weapon + CMD_PNT_ON + CMD_END;
    network.sendBluetoothSerial(frame);
}

function pointerOff(){
    var frame = weapon + CMD_PNT_OFF + CMD_END;
    network.sendBluetoothSerial(frame);
}

//--------- Oscillator Class
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
            var frame = this.dir + CMD_SET_A + A + CMD_END;
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
            var frame = this.dir + CMD_SET_O + O + CMD_END;
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
            var frame = this.dir + CMD_SET_Ph + Ph + CMD_END;
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
            var frame = this.dir + CMD_SET_T + T + CMD_END;
            network.sendBluetoothSerial(frame);
            this._T = T;
            console.log(frame);
        }
    }

}



