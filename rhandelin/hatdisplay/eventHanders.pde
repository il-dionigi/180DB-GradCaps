int GLOBAL_CURR_DROP_INDEX = 0;

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

public void CommandsList(int Value){
  //String theValue = cp5.get(ScrollableList.class, "dropdown").getItem(Value).get("name").toString();
  String COL_SIZE = "5";
  String ROW_SIZE = "5";
  String ID_INPUT  = (cp5.get(Textfield.class, "ID").getText());
  String ROW_INPUT = (cp5.get(Textfield.class, "ROW").getText());
  String COL_INPUT = (cp5.get(Textfield.class, "COL").getText());
  String R = cp5.get(Textfield.class, "R-value").getText();
  String G = cp5.get(Textfield.class, "G-value").getText();
  String B = cp5.get(Textfield.class, "B-value").getText();
  String FUNC = cp5.get(Textfield.class, "Func").getText();
  String WaitTime = cp5.get(Textfield.class, "WaitTime").getText();
  String out = "";
  println(Value);
  if(Value == 0){out = String.format("UpdateWifi/%s/%s/", COL_INPUT, ROW_INPUT);}
  else if(Value == 1){out = String.format("ShowLED/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, G, B);}
  else if(Value == 2){out = String.format("ShowAllLEDs", R, G, B);}
  else if(Value == 3){out = String.format("Rainbow/%s/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, G, B, WaitTime);}
  else if(Value == 4){out = String.format("TheaterChase/%s/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, B, G, WaitTime);}
  else if(Value == 5){out = String.format("TheaterChaseRainbow/%s/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, G, B, WaitTime);}
  else if(Value == 6){out = String.format("UpdateLoc/%s/%s/%s/", ID_INPUT, COL_INPUT, ROW_INPUT);}
  else if(Value == 7){out = String.format("BitmapGenMsgV/%s/%s/%s/" ,COL_INPUT, ROW_INPUT, "UCLA");}
  else if(Value == 8){out = String.format("BitmapGenMsgH/%s/%s/%s/" ,COL_INPUT, ROW_INPUT, "UCLA");}
  else if(Value == 9){out = String.format("BitmapGenSeq/%s/", "2");}
  else if(Value == 10){out = String.format("BitmapGenMsgV/%s/%s/%s/" ,COL_INPUT, ROW_INPUT, "UCLA");}
  else if(Value == 11){out = String.format("StoreFrame/%s/%s/%s/%s/%s/%s/", FUNC, COL_INPUT, ROW_INPUT, R, B, G);}
  else if(Value == 12){out = "StartFrames/";}
  else if(Value == 13){out = "ResetFrames/";}
  else if(Value == 14){out=String.format("Auto/%s/%s/%s/%s/%s/", R, B, G, FUNC, WaitTime);}
  else if(Value == 15){out="StopWifiUpdate/";}
  else if(Value == 16){out=String.format("UpdateGridSize/%s/%s/", COL_SIZE, ROW_SIZE);}
  else if(Value == 17){out="UpdateWifiAll/";}
  else if(Value == 18){out="StopWifiAll/";}
  println(Value);
  GLOBAL_CURR_DROP_INDEX = Value;
  client.publish("test_channel", out);
}

public void SendMSG(int theValue){
 String msg = cp5.get(Textfield.class, "CustomMSG").getText();
 client.publish("test_channel", msg);
}

public void HardSyncAll(int theValue){
  String tx;
  tx = "UpdateLoc/0/0/0/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/1/1/0/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/2/2/0/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/3/3/0/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/4/4/0/";
  
  client.publish("test_channel", tx);
  
  tx = "UpdateLoc/5/0/1/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/6/1/1/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/7/2/1/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/8/3/1/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/9/4/1/";
  
  client.publish("test_channel", tx);
  
  tx = "UpdateLoc/10/0/2/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/11/1/2/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/12/2/2/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/13/3/2/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/14/4/2/";
  
  client.publish("test_channel", tx);
  
  tx = "UpdateLoc/15/0/3/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/16/1/3/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/17/2/3/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/18/3/3/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/19/4/3/";
  
  client.publish("test_channel", tx);

  tx = "UpdateLoc/20/0/4/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/21/1/4/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/22/2/4/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/23/3/4/";
  
  client.publish("test_channel", tx);
  tx = "UpdateLoc/24/4/4/";
  
  client.publish("test_channel", tx);
}

public void DropSND(int theValue) {
  println("DROPSND");
  CommandsList(GLOBAL_CURR_DROP_INDEX);
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
