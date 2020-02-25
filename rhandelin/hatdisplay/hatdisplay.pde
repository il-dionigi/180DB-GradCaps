import controlP5.*;
import mqtt.*;

MQTTClient client;
ControlP5 cp5;

String textValue = "";
String[] messages = new String[5];

void setup() {
  size(800, 500);
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

void draw() {
  background(0);
  fill(255);
  drawUI();
  //text(cp5.get(Textfield.class,"input").getText(), 360,130);
  //text(textValue, 360,180);
}

public void clear() {
  cp5.get(Textfield.class, "textValue").clear();
}

void controlEvent(ControlEvent theEvent) {
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

void clientConnected() {
  println("client connected");

  client.subscribe("test_channel");
}

void messageReceived(String topic, byte[] payload) {
  String message = new String(payload);
  println("new message: " + topic + " - " + message);
    messages[4] = messages[3];
    messages[3] = messages[2];
    messages[2] = messages[1];
    messages[1] = messages[0];
    messages[0] = message;

}

void connectionLost() {
  println("connection lost");
}
