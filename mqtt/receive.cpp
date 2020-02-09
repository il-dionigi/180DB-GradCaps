//Defined Commands
class CommandHandler{
	CommandHandler::CommandHandler(){
		x = -1;
		y = -1;
		role_id = -1;
	}
	CommandHandler::CommandHandler(int x, int y, int role_id){
		this->x = x;
		this->y = y;
		this->role_id = role_id;
	}
	private:
		int x, y, role_id;
		std::map<std::string, std::string> commandsTable; 
		commandsTable["R"] = show_led(255, 0, 0);
		commandsTable["G"] = show_led(0, 255, 0);
		commandsTable["B"] = show_led(0, 0, 255);
		commandsTable["W"] = show_led(255, 255, 255);
		commandsTable["C"] = show_led(0, 0, 0);
		commandsTable["E"] = colorWipe(0, 0);
		commandsTable["X"] = blink();
		commandsTable["a"] = show_led_ptr;
		commandsTable["b"] = blink_color_ptr;
		commandsTable["c"] = color_wipe_ptr;
		commandsTable["d"] = theater_chase_ptr;
		commandsTable["e"] = rainbow_ptr;
		commandsTable["f"] = theater_chase_rainbow_ptr;

		void (*show_led_ptr)(int, int, int) = &show_led;
		void (*blink_color)(int, int, int) = &blink_color;
		//(*show_led_ptr)(arg1, arg2, arg3);
		void (*color_wipe_ptr)(uint32_t, int) = &colorWipe;
		void (*theater_chase_ptr)(uint32_t, int) = &theaterChase;
		void *(rainbow_ptr)(int) = &rainbow_ptr;
		void *(theater_chase_rainbow_ptr)(uint32_t, int) = &theaterChaseRainbow;

		void blink(){
			delay(0.5*role_id);
			this->show_led(255, 255, 255);
			delay(0.5);
			this->show_led(0, 0, 0);
		}
		void blink_color(int r, int b, int g){
			uint32_t mycolor = strip.color(r, b, g);
			delay(0.5*role_id);
			this->show_led(255, 255, 255);
			delay(0.5);
			this->show_led(0, 0, 0);
		}
		void show_led(int r, int b, int g){
			uint32_t mycolor = strip.color(r, b, g);
			strip.setpixelcolor(0, mycolor);
			strip.setpixelcolor(1, mycolor);
			strip.setpixelcolor(2, mycolor);
			strip.setpixelcolor(3, mycolor);
			strip.setpixelcolor(4, mycolor);
			strip.setpixelcolor(5, mycolor);
			strip.setpixelcolor(6, mycolor);
			strip.setpixelcolor(7, mycolor);
			strip.setpixelcolor(8, mycolor);
			strip.setpixelcolor(9, mycolor);
			strip.setpixelcolor(10, mycolor);
			strip.setpixelcolor(11, mycolor);
			strip.show();
		}
		void colorWipe(uint32_t color, int wait) {
			for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
				strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
				strip.show();                          //  Update strip to match
				delay(wait);                           //  Pause for a moment
			}
		}
		void theaterChase(uint32_t color, int wait) {
		  for(int a=0; a<10; a++) {  // Repeat 10 times...
			for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
			  strip.clear();         //   Set all pixels in RAM to 0 (off)
			  // 'c' counts up from 'b' to end of strip in steps of 3...
			  for(int c=b; c<strip.numPixels(); c += 3) {
				strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
			  }
			  strip.show(); // Update strip with new contents
			  delay(wait);  // Pause for a moment
			}
		  }
		}

		// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
		void rainbow(int wait) {
		  // Hue of first pixel runs 5 complete loops through the color wheel.
		  // Color wheel has a range of 65536 but it's OK if we roll over, so
		  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
		  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
		  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
			for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
			  // Offset pixel hue by an amount to make one full revolution of the
			  // color wheel (range of 65536) along the length of the strip
			  // (strip.numPixels() steps):
			  int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
			  // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
			  // optionally add saturation and value (brightness) (each 0 to 255).
			  // Here we're using just the single-argument hue variant. The result
			  // is passed through strip.gamma32() to provide 'truer' colors
			  // before assigning to each pixel:
			  strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
			}
			strip.show(); // Update strip with new contents
			delay(wait);  // Pause for a moment
		  }
		}

		// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
		void theaterChaseRainbow(int wait) {
		  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
		  for(int a=0; a<30; a++) {  // Repeat 30 times...
			for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
			  strip.clear();         //   Set all pixels in RAM to 0 (off)
			  // 'c' counts up from 'b' to end of strip in increments of 3...
			  for(int c=b; c<strip.numPixels(); c += 3) {
				// hue of pixel 'c' is offset by an amount to make one full
				// revolution of the color wheel (range 65536) along the length
				// of the strip (strip.numPixels() steps):
				int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
				uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
				strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
			  }
			  strip.show();                // Update strip with new contents
			  delay(wait);                 // Pause for a moment
			  firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
			}
		}
	}
};