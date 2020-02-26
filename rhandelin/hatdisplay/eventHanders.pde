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
  String theValue = cp5.get(ScrollableList.class, "dropdown").getItem(Value).get("name").toString();
  String COL_SIZE = "5";
  String ROW_SIZE = "5";
  String ID_INPUT  = (cp5.get(Textfield.class, "ID").getText());
  String ROW_INPUT = (cp5.get(Textfield.class, "ROW").getText());
  String COL_INPUT = (cp5.get(Textfield.class, "COL").getText());
  String R = cp5.get(Textfield.class, "R-value").getText();
  String G = cp5.get(Textfield.class, "G-value").getText();
  String B = cp5.get(Textfield.class, "B-value").getText();
  String WaitTime = cp5.get(Textfield.class, "Waittime").getText();
  String out = "";
  println(theValue);
  if(theValue == "UpdateWifi"){out = String.format("UpdateWifi/%s/%s/", COL_INPUT, ROW_INPUT);}
  else if(theValue == "ShowLED"){out = String.format("ShowLED/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, G, B);}
  else if(theValue == "ShowAllLEDs"){out = String.format("ShowAllLEDs", R, G, B);}
  else if(theValue == "Rainbow"){out = String.format("Rainbow/%s/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, G, B, WaitTime);}
  else if(theValue == "TheaterChase"){out = String.format("TheaterChase/%s/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, B, G, WaitTime);}
  else if(theValue == "TheaterChaseRainbow"){out = String.format("TheaterChaseRainbow/%s/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, G, B, WaitTime);}
  else if(theValue == "UpdateLoc"){out = String.format("UpdateLoc/%s/%s/%s/", ID_INPUT, COL_INPUT, ROW_INPUT);}
  else if(theValue == "BitmapGenMsgV"){out = String.format("BitmapGenMsgV/%s/%s/%s/" ,COL_INPUT, ROW_INPUT, "UCLA");}
  else if(theValue == "BitmapGenMsgH"){out = String.format("BitmapGenMsgH/%s/%s/%s/" ,COL_INPUT, ROW_INPUT, "UCLA");}
  else if(theValue == "BitmapGenSeq"){out = String.format("BitmapGenSeq/%s/", "2");}
  else if(theValue == "BitmapShowSeq"){out = String.format("BitmapGenMsgV/%s/%s/%s/" ,COL_INPUT, ROW_INPUT, "UCLA");}
  else if(theValue == "StoreFrame"){out = String.format("StoreFrame/%s/%s/%s/%s/%s/", COL_INPUT, ROW_INPUT, R, B, G);}
  else if(theValue == "StartFrames"){out = "StartFrames";}
  else if(theValue == "Auto"){out="Auto";}
  else if(theValue == "StopWifiUpdate"){out="StopWifiUpdate";}
  else if(theValue == "UpdateGridSize"){out=String.format("UpdateGridSize/%s/%s/", COL_SIZE, ROW_SIZE);}
  else if(theValue == "UpdateWifiAll"){out="UpdateWifiAll";}
  println(theValue);
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
