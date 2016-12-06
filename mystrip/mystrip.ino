#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM 40
#define BUFFS 1024

//for LIGHT
#define M_PI acos(-1.0)
#define MIN_LIGHT 2
#define MAX_LIGHT 5
#define STEP 0.5

// strip controller
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

uint32_t red = strip.Color(80,0,0);

void set_color(double rad = 0,double d =0){
  
  //set default
  for(int i=0;i<NUM;i++)
    strip.setPixelColor(i, red);
    
  strip.show();
}

void set_color_by_array(int p = 0,int r =0){
  
  //set default
  for(int i=0;i<NUM;i++)
    strip.setPixelColor(i, red);
    
  strip.show();
}


char* read_cmd(){
  char cmd[BUFFS];
  memset(cmd,0,BUFFS);
  int ind=0;
  cmd[0]='\0';
  while(true){
    if(Serial.available()>0){
      cmd[ind] = Serial.read();
      Serial.print(cmd[ind]);
      if(cmd[ind] == '\n' || cmd[ind]=='\r'){
        cmd[ind] = '\0';
        break;
      }
      
      cmd[++ind] = '\0';
    }
  }
  return cmd;
}

const char sep[8] = "- (),[]";
void decode_and_set(char* cmd){
  
  set_color();
  char* token;
  int r,g,b;
  
  for(int i=0;i<NUM;i++){
    token = strtok(cmd,sep);
    Serial.print(token);
    Serial.print("\n");
    
    r = atoi(token);
    
    token = strtok(cmd,sep);
    Serial.print(token);
    Serial.print("\n");
    
    g = atoi(token);
    
    token = strtok(cmd,sep);
    Serial.print(token);
    Serial.print("\n");
    
    b = atoi(token);
    
    if(token[0] == '\0')
      break;
      
    strip.setPixelColor(i, r,g,b);
  }
  
  strip.show();
}

//String str;
void setup(){
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop(){
  set_color();
  
  char* cmd_in = read_cmd();
  decode_and_set(cmd_in);
}

