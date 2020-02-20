import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import mqtt.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class hatdisplay extends PApplet {




MQTTClient client;
ControlP5 cp5;

String textValue = "";




public void setup() {
  
  PFont font = createFont("arial", 20);
  textFont(font);
  cp5 = new ControlP5(this);
  client = new MQTTClient(this);
  createUI(cp5, font);
  try {
    client.connect("mqtt://192.168.0.100", "processing");
  }
  catch(Exception e) {
    
  }
}

public void draw() {
  background(0);
  fill(255);
  drawUI();
  //text(cp5.get(Textfield.class,"input").getText(), 360,130);
  //text(textValue, 360,180);
}

public void clear() {
  cp5.get(Textfield.class, "textValue").clear();
}

public void controlEvent(ControlEvent theEvent) {
  if (theEvent.isAssignableFrom(Textfield.class)) {
    println("controlEvent: accessing a string from controller '"
      +theEvent.getName()+"': "
      +theEvent.getStringValue()
      );
  }
}

public void input(String theText) {
  println("a textfield event for controller 'input' : "+theText);
}

public void clientConnected() {
  println("client connected");

  client.subscribe("test_channel");
}

public void messageReceived(String topic, byte[] payload) {
  println("new message: " + topic + " - " + new String(payload));
}

public void connectionLost() {
  println("connection lost");
}
public void drawUI() {
  text("ID: ", 175, 50);
  text("Row: ", 175, 70);
  text("Col: ", 175, 90);

  //text(ID_input, 240, 50);
  //text(ROW_input, 240, 70);
  //text(COL_input, 240, 90);
  text(cp5.get(Textfield.class, "ID").getText(), 240, 50);
  text(cp5.get(Textfield.class, "ROW").getText(), 240, 70);
  text(cp5.get(Textfield.class, "COL").getText(), 240, 90);

  text("msg1: ", 50, 350);
  text("msg2: ", 50, 370);
  text("msg3: ", 50, 390);
  text("msg4: ", 50, 410);
  text("msg5: ", 50, 430);
}
public void publish(int theValue) {
  int ID_input  = PApplet.parseInt(cp5.get(Textfield.class, "ID").getText());
  int ROW_input = PApplet.parseInt(cp5.get(Textfield.class, "ROW").getText());
  int COL_input = PApplet.parseInt(cp5.get(Textfield.class, "COL").getText());

  String tx = "UpdateLoc/" + ID_input + "/" + ROW_input + "/"  + COL_input + "/";
  println("Sent: " + tx);
  client.publish("test_channel", tx);
  
  cp5.get(Textfield.class,"ID").clear();
  cp5.get(Textfield.class,"ROW").clear();
  cp5.get(Textfield.class,"COL").clear();
  
}

public void red_button(int theValue) {
  println("Red");
  client.publish("test_channel", "R");
}

public void green_button(int theValue) {
  println("Green");
  client.publish("test_channel", "G");
}

public void blue_button(int theValue) {
  println("Blue");
  client.publish("test_channel", "B");
}

public void ID(String theText) {
}
public void ROW(String theText) {
}
public void COL(String theText) {
}
public void createUI(ControlP5 cp5, PFont font) {

  cp5.addTextfield("ID")
    .setBroadcast(false)
    .setPosition(30, 30)
    .setValue(0)
    .setSize(100, 40)
    .setFont(font)
    .setFocus(true)
    .setBroadcast(true)
    ;

  cp5.addTextfield("ROW")
    .setPosition(30, 120)
    .setSize(100, 40)
    .setFont(createFont("arial", 20))
    ;

  cp5.addTextfield("COL")
    .setPosition(160, 120)
    .setSize(100, 40)
    .setFont(createFont("arial", 20))
    ;

  cp5.addButton("publish")
    .setLabel("Publish")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(70, 200)
    .setSize(150, 40)
    .setVisible(true)
    .setBroadcast(true)
    ;   

  cp5.addButton("red_button")
    .setLabel("R")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(60, 280)
    .setSize(40, 40)
    .setColorForeground(color(255, 0, 0))
    .setColorBackground(color(255, 0, 0))
    .setColorActive(color(255, 0, 0))
    .setVisible(true)
    .setBroadcast(true)
    ;   

  cp5.addButton("green_button")
    .setLabel("G")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(120, 280)
    .setSize(40, 40)
    .setColorForeground(color(0, 255, 0))
    .setColorBackground(color(0, 255, 0))
    .setColorActive(color(0, 255, 0))
    .setVisible(true)
    .setBroadcast(true)
    ;   

  cp5.addButton("blue_button")
    .setLabel("B")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(180, 280)
    .setSize(40, 40)
    .setColorForeground(color(0, 0, 255))
    .setColorBackground(color(0, 0, 255))
    .setColorActive(color(0, 0, 255))
    .setVisible(true)
    .setBroadcast(true)
    ;   


  //cp5.addTextfield("default")
  //   .setPosition(20,350)
  //   .setAutoClear(false)
  //   ;
}
  public void settings() {  size(300, 500); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "hatdisplay" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
