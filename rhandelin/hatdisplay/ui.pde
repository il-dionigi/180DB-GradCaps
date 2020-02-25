void createUI(ControlP5 cp5, PFont font) {

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
    .setSize(40, 40)
    .setFont(createFont("arial", 20))
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
    .setPosition(400, 120)
    .setSize(300, 40)
    .setFont(createFont("arial", 20))
    .setAutoClear(false)
    ;
    
  cp5.addButton("SendMSG")
    .setLabel("SendMSG")
    .setBroadcast(true)
    .setValue(0)
    .setPosition(400, 180)
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
    .setPosition(70, 260)
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
