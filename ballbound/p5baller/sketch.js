let serial;
let portName = 'COM4'; 
let options = { baudRate: 9600}; 

let rxFlag = false;  
let firstContact = false; 
let sensors = [0, 0, 0, 0]; 
let pot1 = 0; 
let pot2 = 0; 
let button1 = 0;
let button2 = 0;

xval = 30;
xvel = 30;
yval = 30;
yvel = 0;


function setup() 
{
  
  createCanvas(500, 500);
  textAlign(CENTER, CENTER);
  rectMode(CENTER);
  textSize(24);
  strokeWeight(1);
  stroke(127);

  xval = width/2;
  yval = height/2;

  for(let i = 0; i < width ; i++)
  {
    let c = map(i, 0, width, 0, 255);  //map i to 0-255 range for color
    stroke(c * 2, c, 0);    //change stroke color for each x position, red is scaled to 2x
    line(i, 0, i, random(0,500));
  }

  
  serial = new p5.SerialPort();             
  serial.on('list', printList);             
  serial.on('connected', serverConnected);  
  serial.on('open', portOpen);              
  serial.on('data', serialEvent);           
  serial.on('error', serialError);          
  serial.on('close', portClose);            
  serial.list();                            
  serial.open(portName, options);           
}

function draw() 
{
  /*
  background(255);
  stroke(127);
  
  xvel = pot1;
  yvel = pot2;
  
  xval += xvel;
  if (xval < 0 || xval > width)
  {
    xvel = -xvel;
  }
  
  yval += yvel;
  if (yval < 0 || yval > width)
  {
    yvel = -yvel;
  }
  
  ellipse(xval, yval, 30);

  line(width/8, 0, width/8, 255);
  line(width-50, 0, width-50, 255);
  rect(width/8, pot1, 60, 20);
  rect(width-50, pot2, 60, 20);
  */
}

function mousePressed() 
{

    rxFlag = !rxFlag; 

      serial.write('A'); 

}

function portOpen() 
{
  print("SERIAL PORT OPEN");
}

function portClose() 
{
  print("SERIAL PORT CLOSED");
}

function printList(portList) 
{
  print("List of Available Serial Ports: ");
  for (var i = 0; i < portList.length; i++) 
  {
    print(i + portList[i]); 
  }
}

function serialEvent() 
{
  if (!firstContact)  
  {
    print("FIRST CONTACT");
    firstContact = true;  
  }
  
  if(rxFlag)  
  {
    let inString = serial.readStringUntil('\n'); 
    if (inString.length > 0) 
    {
      print("Rx String: " + inString); 
      sensors = split(inString, ','); 
    
      if(sensors.length >= 4) 
      {
        print(sensors); 

        button1 = Number(sensors[0]); 
        button1 = map(button1, 0, 1, 0, 255);

        button2 = Number(sensors[1]); 
        button2 = map(button2, 0, 1, 0, 255);
        
        pot1 = Number(sensors[2]); 
        pot1 = map(pot1, 0, 1023, 0, 255); 
        pot1 = floor(pot1);

        pot2 = Number(sensors[3]);
        pot2 = map(pot2, 0, 1023, 0, 255); 
        pot2 = floor(pot2); 
        
        print("Button 1: " + button1 + " Button 2: " + button2 + " Pot 1: " + pot1 + " Pot 2: " + pot2);

        
        serial.write('A');  
      }
    }
  }
  else
  {
    let inString = serial.readStringUntil('\n'); 
    print(inString); 
  }
}

function serialError(err) 
{
  print('SERIAL ERROR: ' + err);
}

function serverConnected() 
{
  print("CONNECTED TO SERIAL SERVER");
}