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
