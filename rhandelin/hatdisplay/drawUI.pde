void drawUI() {
  text("ID: ", 175, 50);
  text("Row: ", 175, 70);
  text("Col: ", 175, 90);

  //text(ID_input, 240, 50);
  //text(ROW_input, 240, 70);
  //text(COL_input, 240, 90);
  text(cp5.get(Textfield.class, "ID").getText(), 240, 50);
  text(cp5.get(Textfield.class, "ROW").getText(), 240, 70);
  text(cp5.get(Textfield.class, "COL").getText(), 240, 90);

  text(" " + messages[0], 50, 350);
  text(" " + messages[1], 50, 370);
  text(" " + messages[2], 50, 390);
  text(" " + messages[3], 50, 410);
  text(" " + messages[4], 50, 430);
}
