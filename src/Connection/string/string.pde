import processing.serial.*;
import java.io.*;
int mySwitch=0;
int counter=0;
String [] subtext;
Serial myPort;

void setup(){
 mySwitch=1;
 myPort = new Serial(this, "/dev/cu.usbmodem1461", 9600);
 myPort.bufferUntil('\n');
}
void draw() {
 if(mySwitch>0){
 readData("/Users/andywang/string/string.txt");
 mySwitch=0;
 }
 delay(2000);
 //myPort.write("Andy");
 if(counter<subtext.length){
   //println(subtext.length);
 //println("test");
 myPort.write(subtext[counter]);
 //int i = (int) subtext[counter];
 //println(counter);
 println(subtext[counter]);
 delay(1000);
 counter++;
 } 
 else{
 delay(1000);
 mySwitch=1;
 }
} 


void readData(String myFileName){
 File file=new File(myFileName);
 BufferedReader br=null;
 try{
 br=new BufferedReader(new FileReader(file));
 String text=null;
 while((text=br.readLine())!=null){
   subtext = splitTokens(text,"\n");
 }
 }catch(FileNotFoundException e){
 e.printStackTrace();
 }catch(IOException e){
 e.printStackTrace();
 }finally{
 try {
 if (br != null){
 br.close();
 }
 } catch (IOException e) {
 e.printStackTrace();
 }
 }
}