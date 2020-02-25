public void publish(int theValue) {
  int ID_input  = PApplet.parseInt(cp5.get(Textfield.class, "ID").getText());
  int ROW_input = PApplet.parseInt(cp5.get(Textfield.class, "ROW").getText());
  int COL_input = PApplet.parseInt(cp5.get(Textfield.class, "COL").getText());

  String tx = "UpdateLoc/" + ID_input + "/" + ROW_input + "/"  + COL_input + "/";

  //println("Sent: " + tx);
  //client.publish("test_channel", tx);

  //cp5.get(Textfield.class,"ID").clear();
  //cp5.get(Textfield.class,"ROW").clear();
  //cp5.get(Textfield.class,"COL").clear();
}

public void CustomMSG(String theValue){
client.publish("test_channel", theValue);
}

public void SendMSG(int theValue){
 String msg = cp5.get(Textfield.class, "CustomMSG").getText();
 client.publish("test_channel", msg);
}

public void HardSyncAll(int theValue){
  String tx;
  tx = "UpdateLoc/0/0/0/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/1/1/0/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/2/2/0/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/3/3/0/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/4/4/0/";
  delay(100);
  client.publish("test_channel", tx);
  
  tx = "UpdateLoc/5/0/1/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/6/1/1/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/7/2/1/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/8/3/1/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/9/4/1/";
  delay(100);
  client.publish("test_channel", tx);
  
  tx = "UpdateLoc/10/0/2/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/11/1/2/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/12/2/2/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/13/3/2/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/14/4/2/";
  delay(100);
  client.publish("test_channel", tx);
  
  tx = "UpdateLoc/15/0/3/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/16/1/3/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/17/2/3/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/18/3/3/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/19/4/3/";
  delay(100);
  client.publish("test_channel", tx);

  tx = "UpdateLoc/20/0/4/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/21/1/4/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/22/2/4/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/23/3/4/";
  delay(100);
  client.publish("test_channel", tx);
  tx = "UpdateLoc/24/4/4/";
  delay(100);
  client.publish("test_channel", tx);
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
