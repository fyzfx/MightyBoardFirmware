/*
 * Copyright 2012 by Alison Leonard <alison@makerbot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
 
 #include "Interface.hh"
 #include <util/delay.h>
 
 #include "UtilityScripts.hh"
 #include <avr/pgmspace.h>
 
 static uint16_t Lengths[2]  PROGMEM = { 75, /// Home Axes
                            2032}; /// Level Plate(Startup)
                            

static uint8_t HomeAxes[] PROGMEM = { 131,  4,  136,  0,  0,  0,  20,  0,  140,  0,  0,  0,  0,  0,  0,  0,  0, 48,  248,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  87,  41,  4,  0,  24,  131,  4,  220,  5,  0,  0,  20,  0,  132,  3,  105,  1,  0,  0,  20,  0,  144,  31,  137,  31 };

static uint8_t LevelPlate[] PROGMEM = { 149,  0,  0,  0,  0,  70,  105,  110,  100,  32,  116,  104,  101,  32,  52,  32,  107,  110,  111,  98,  115,  32,  111,  110,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  98,  111,  116,  116,  111,  109,  32,  111,  102,  32,  116,  104,  101,  32,  32,  32,  0,  149,  1,  0,  0,  0,  112,  108,  97,  116,  102,  111,  114,  109,  32,  97,  110,  100,  32,  116,  117,  114,  110,  32,  116,  111,  0,  149,  7,  0,  0,  0,  116,  105,  103,  104,  116,  101,  110,  32,  99,  111,  109,  112,  108,  101,  116,  101,  108,  121,  46,  0,  149,  0,  0,  0,  0,  73,  39,  109,  32,  103,  111,  105,  110,  103,  32,  116,  111,  32,  109,  111,  118,  101,  32,  32,  32,  0,  149,  1,  0,  0,  0,  116,  104,  101,  32,  101,  120,  116,  114,  117,  100,  101,  114,  32,  116,  111,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  118,  97,  114,  105,  111,  117,  115,  32,  112,  111,  115,  105,  116,  105,  111,  110,  115,  32,  32,  32,  0,  149,  7,  0,  0,  0,  102,  111,  114,  32,  97,  100,  106,  117,  115,  116,  109,  101,  110,  116,  46,  46,  46,  0,  149,  0,  0,  0,  0,  73,  110,  32,  101,  97,  99,  104,  32,  112,  111,  115,  105,  116,  105,  111,  110,  44,  32,  32,  32,  0,  149,  1,  0,  0,  0,  119,  101,  32,  119,  105,  108,  108,  32,  110,  101,  101,  100,  32,  116,  111,  32,  32,  32,  32,  32,  0,  149,  1,  0,  0,  0,  97,  100,  106,  117,  115,  116,  32,  116,  119,  111,  32,  107,  110,  111,  98,  115,  32,  97,  116,  32,  0,  149,  7,  0,  0,  0,  116,  104,  101,  32,  115,  97,  109,  101,  32,  116,  105,  109,  101,  46,  46,  46,  0,  149,  0,  0,  0,  0,  78,  111,  122,  122,  108,  101,  115,  32,  97,  114,  101,  32,  97,  116,  32,  116,  104,  101,  32,  32,  0,  149,  1,  0,  0,  0,  114,  105,  103,  104,  116,  32,  104,  101,  105,  103,  104,  116,  32,  119,  104,  101,  110,  32,  32,  32,  0,  149,  1,  0,  0,  0,  121,  111,  117,  32,  99,  97,  110,  32,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  32,  97,  0,  149,  7,  0,  0,  0,  115,  104,  101,  101,  116,  32,  111,  102,  32,  112,  97,  112,  101,  114,  46,  46,  46,  0,  149,  0,  0,  0,  0,  98,  101,  116,  119,  101,  101,  110,  32,  116,  104,  101,  32,  110,  111,  122,  122,  108,  101,  32,  32,  0,  149,  1,  0,  0,  0,  97,  110,  100,  32,  116,  104,  101,  32,  112,  108,  97,  116,  102,  111,  114,  109,  46,  32,  32,  32,  0,  149,  1,  0,  0,  0,  71,  114,  97,  98,  32,  97,  32,  115,  104,  101,  101,  116,  32,  111,  102,  32,  32,  32,  32,  32,  0,  149,  7,  0,  0,  0,  112,  97,  112,  101,  114,  32,  116,  111,  32,  97,  115,  115,  105,  115,  116,  32,  117,  115,  46,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  131,  4,  136,  0,  0,  0,  20,  0,  140,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  132,  3,  105,  1,  0,  0,  20,  0,  140,  165,  49,  0,  0,  148,  27,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  0,  0,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  29,  71,  28,  0,  24,  142,  0,  0,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  192,  140,  13,  0,  24,  142,  0,  0,  0,  0,  201,  228,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  102,  114,  111,  110,  116,  32,  116,  119,  111,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  239,  34,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  32,  101,  17,  0,  24,  142,  240,  34,  0,  0,  201,  228,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  114,  105,  103,  104,  116,  32,  116,  119,  111,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  239,  34,  0,  0,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  246,  219,  255,  255,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  224,  86,  35,  0,  24,  142,  246,  219,  255,  255,  201,  228,  255,  255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  108,  101,  102,  116,  32,  116,  119,  111,  32,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  247,  219,  255,  255,  202,  228,  255,  255,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  0,  0,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  138,  50,  32,  0,  24,  142,  0,  0,  0,  0,  122,  26,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  98,  97,  99,  107,  32,  116,  119,  111,  32,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  0,  0,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  239,  34,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  32,  101,  17,  0,  24,  142,  239,  34,  0,  0,  122,  26,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  114,  105,  103,  104,  116,  32,  116,  119,  111,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  149,  2,  0,  0,  0,  80,  108,  101,  97,  115,  101,  32,  119,  97,  105,  116,  0,  142,  240,  34,  0,  0,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  84,  220,  255,  255,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  40,  35,  0,  24,  142,  84,  220,  255,  255,  122,  26,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  116,  104,  101,  32,  108,  101,  102,  116,  32,  116,  119,  111,  32,  0,  149,  1,  0,  0,  0,  107,  110,  111,  98,  115,  32,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  32,  32,  0,  149,  1,  0,  0,  0,  106,  117,  115,  116,  32,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  0,  142,  85,  220,  255,  255,  122,  26,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  142,  0,  0,  0,  0,  0,  0,  0,  0,  208,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  145,  30,  22,  0,  24,  142,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13,  69,  3,  0,  24,  149,  0,  0,  0,  0,  65,  100,  106,  117,  115,  116,  32,  97,  108,  108,  32,  107,  110,  111,  98,  115,  44,  32,  32,  32,  0,  149,  1,  0,  0,  0,  102,  105,  114,  115,  116,  32,  116,  104,  101,  32,  102,  114,  111,  110,  116,  32,  116,  119,  111,  44,  0,  149,  1,  0,  0,  0,  116,  104,  101,  110,  32,  116,  104,  101,  32,  98,  97,  99,  107,  32,  116,  119,  111,  44,  32,  32,  0,  149,  7,  0,  0,  0,  117,  110,  116,  105,  108,  32,  112,  97,  112,  101,  114,  32,  106,  117,  115,  116,  46,  46,  46,  0,  149,  0,  0,  0,  0,  115,  108,  105,  100,  101,  115,  32,  98,  101,  116,  119,  101,  101,  110,  32,  116,  104,  101,  32,  32,  0,  149,  7,  0,  0,  0,  110,  111,  122,  122,  108,  101,  32,  97,  110,  100,  32,  112,  108,  97,  116,  102,  111,  114,  109,  46,  0,  137,  31 };

 namespace utility {
	 
	 volatile bool is_playing;
	 int build_index = 0;
	 int build_length = 0;
	 uint8_t * buildFile;
	  
 /// returns true if script is running
 bool isPlaying(){
	 return is_playing;		
 }
 void reset(){
	 int build_index = 0;
	 int build_length = 0;
	 is_playing = false;
 
 }
 
 /// returns true if more bytes are available in the script
 bool playbackHasNext(){
	return (build_index < build_length);
 }
 
 /// gets next byte in script
 uint8_t playbackNext(){
	 
	 uint8_t byte;
	 
	 if(build_index < build_length)
	 {
		 byte = pgm_read_byte(buildFile + build_index++);
		return byte;
	}

	else 
		return 0;
 }
 
 /// begin buffer playback
 bool startPlayback(uint8_t build){
	 
	 
	 is_playing = true;
	 build_index = 0;

     // get build file
	switch (build){
        case HOME_AXES:
			buildFile = HomeAxes;		
			break;
		case LEVEL_PLATE_SECOND:
			buildFile = LevelPlate;
			build = LEVEL_PLATE_STARTUP;
			getSecondLevelOffset();
			break;
		case LEVEL_PLATE_STARTUP:
			buildFile = LevelPlate;
			break;
		default:
			return false;
	}
	
     // get build length
	 build_length = pgm_read_word(Lengths + build);
	 return is_playing;
 }
     
 void getSecondLevelOffset(){
	 // find the homeing command (after all the intro text)
	 uint8_t messageCount = 0;
	 while(messageCount < 5){
		 while(pgm_read_byte(buildFile + build_index) != 149)
			build_index++;
		build_index++;
		messageCount++;
	 }
	 build_index--;
	
 }
 
 /// updates state to finished playback
 void finishPlayback(){

	is_playing = false;
 }

};
