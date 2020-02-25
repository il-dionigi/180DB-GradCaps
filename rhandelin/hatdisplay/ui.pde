void createUI(ControlP5 cp5, PFont font) {
int publish_height = 280;
int row_col_height = 120;
DropdownList droplist = cp5.addDropdownList("CommandsList").setPosition(460 , 210);
 
  // add items to the dropdownlist
  
  droplist.addItem("WifiUpdate", 0);
  droplist.addItem("ShowLED", 1);
  droplist.addItem("ShowAllLEDs", 2);
  droplist.addItem("Rainbow", 3);
  droplist.addItem("TheaterChase", 4);
  droplist.addItem("TheaterChaseRainbow", 5);
  droplist.addItem("UpdateLoc", 6);
  droplist.addItem("BitmapGenMsgV", 7);
  droplist.addItem("BitmapGenMsgH", 8);
  droplist.addItem("BitmapGenSeq", 9);
  droplist.addItem("BitmapShowSeq", 10);
  droplist.addItem("StoreFrame", 11);
  droplist.addItem("StartFrames", 12);
  droplist.addItem("Auto", 13);
  droplist.addItem("StopWifiUpdate", 14);
  droplist.addItem("UpdateGridSize", 15);
  droplist.addItem("UpdateWifiAll", 16);
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
    .setPosition(30, row_col_height)
    .setSize(100, 40)
    .setFont(createFont("arial", 20))
    ;

  cp5.addTextfield("COL")
    .setPosition(160, row_col_height)
    .setSize(40, 40)
    .setFont(createFont("arial", 20))
    ;
  cp5.addTextfield("#Rows")
    .setPosition(220, row_col_height)
    .setSize(40, 40)
    .setFont(createFont("arial", 14))
    ;
  cp5.addTextfield("#Cols")
    .setPosition(280, row_col_height)
    .setSize(40, 40)
    .setFont(createFont("arial", 14))
    ;
  
  cp5.addTextfield("R-value")
    .setPosition(20, 200)
    .setSize(40, 40)
    .setFont(createFont("arial", 10))
    ;
   cp5.addTextfield("B-value")
    .setPosition(80, 200)
    .setSize(40, 40)
    .setFont(createFont("arial", 10))
    ;
  cp5.addTextfield("G-value")
    .setPosition(140, 200)
    .setSize(40, 40)
    .setFont(createFont("arial", 10))
    ;
  cp5.addTextfield("WaitTime")
    .setPosition(200, 200)
    .setSize(40, 40)
    .setFont(createFont("arial", 10))
    ;
  
  cp5.addTextfield("CustomMSG")
    .setPosition(400, row_col_height)
    .setSize(300, 40)
    .setFont(createFont("arial", 20))
    .setAutoClear(false)
    ;
    
  cp5.addButton("SendMSG")
    .setLabel("SendMSG")
    .setBroadcast(true)
    .setValue(0)
    .setPosition(400, 210)
    .setSize(40, 40)
    .setVisible(true)
    .setBroadcast(true);
    
  
  cp5.addButton("HardSyncAll")
    .setLabel("HardSync")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(400, 60)
    .setSize(40, 40)
    .setVisible(true)
    .setBroadcast(true)
    ;   
    
  cp5.addButton("publish")
    .setLabel("Publish")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(10, publish_height)
    .setSize(100, 40)
    .setVisible(true)
    .setBroadcast(true)
    ;   

  cp5.addButton("red_button")
    .setLabel("R")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(120, publish_height)
    .setSize(40, 40)
    .setColorForeground(color(255, 0, 0))
    .setColorBackground(color(255, 0, 0))
    .setColorActive(color(255, 0, 0))
    .setVisible(true)
    .setBroadcast(true)
    ;   

  cp5.addButton("DropSND")
    .setLabel("DropSND")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(280, publish_height)
    .setSize(80, 40)
    .setColorForeground(color(100, 0, 100))
    .setColorBackground(color(100, 0, 100))
    .setColorActive(color(100, 0, 100))
    .setVisible(true)
    .setBroadcast(true)
    ;   
  cp5.addButton("green_button")
    .setLabel("G")
    .setBroadcast(false)
    .setValue(0)
    .setPosition(170, publish_height)
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
    .setPosition(220, publish_height)
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
