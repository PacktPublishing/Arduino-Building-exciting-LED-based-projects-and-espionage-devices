// touch_pad_pro by Adith Jagadish Boloor

// Libraries
import processing.serial.*;
import matrixMath.*;

// Variables
Serial myPort;  // Create object from Serial class
String val = "hi";     // Data received from the serial port
char[] conv_text = new char[15];
char conv_char;
int text_ctr = 1;

int l1, newval;
int xpos = 1;
int ypos = 1;
int [][] grid_matrix = new int[9][13]; // matrix variable
int countingBeginning = 0; // timer variable
int countingEnd = 0; 
float record=0; 
int status =0;
int pixel_count = 0;

int rowTOP = 0;
int rowBOT = 0;
int rowHOR = 0; // horizontal (middle)
int colLEF = 0;
int colRIG = 0;
int colVER = 0; // vertical (middle)

void setup()
{
  // create new port identifier
  myPort = new Serial(this, Serial.list()[0], 57600); 
  myPort.clear();
  
  // sets the background and creates draw box
  background(200);
  size(420, 680);
  draw_grid(); // function to create the touch pad 'grid'
  
  // set each value of the matrix to 0
  for(int j = 0; j <= 12; j++)
  for(int i = 0; i <= 8; i++)
  grid_matrix[i][j]=0;
  
}

void draw()
{
  while ( myPort.available() > 0) 
  {  // If data is available,
  status = 0;
  
  val = myPort.readString(); // get XY coordinates from Serial port and store in val
  l1 = val.length(); // length of val
  countingBeginning=millis(); // begin timer
  // Note: timer is used to know when the user has finished all the strokes he/she wanted to create;
  // The program waits for four seconds of inactivity and then only begins to intepret the input

  // get back the X & Y positions from the single value in val
  if(l1>1)
  {
    xpos_temp = xpos;
    ypos_temp = ypos;
    newval = parseInt(val); // convert string to int
    if(l1==3){
      xpos = newval/100;
      ypos = newval-xpos*100;
      // print the x & y positions for debugging
      println("xpos ypos");
      print(xpos);
      print(" ");
      print(ypos);
    }
    if(l1==2){
      xpos = newval/10;
      ypos = newval-xpos*10;
      // print the x & y positions for debugging
      println("xpos ypos");
      print(xpos);
      print(" ");
      print(ypos);
    }
  }
  // safety if statement to make sure program does not crash if random 0's show up for xpos & y pos
  if(xpos>0&&ypos>0)
  grid_matrix[xpos-1][ypos-1]=1; // touched grid pads' corresponding matrix element is changed to 1
  fill(200, 27, 27);
  ellipse(xpos*40+10,ypos*40+50,25,25); // changes the colour of eclipses to represent touched pads in real time
  pixel_count++; // increments the counter
}
countingEnd=millis(); // ends timer
record=(countingEnd-countingBeginning)*.001;  // calculates time elapsed since inactivity

// if the inactivity time is greater than 4 seconds and more than 10 pixels have been 'touched', 
// begin intepreting the data as a whole
if((record > 4)&&(status==0)&&(pixel_count>10))
{
  status = 1;
  // calculate the sums of the extremes and middle/central rows and columns based on 1's in matrix
  for(int j = 0;j <= 12; j++)
  {
    colLEF = colLEF + grid_matrix[0][j];
    colRIG = colRIG + grid_matrix[8][j];
    colVER = colVER + grid_matrix[4][j];
    colVER = colVER + grid_matrix[3][j];
    colVER = colVER + grid_matrix[5][j];
    print("\n");
    for(int i = 0; i <= 8; i++)
    {
      print(grid_matrix[i][j]);
      print("  ");
      rowTOP = rowTOP + grid_matrix[i][0];
      rowBOT = rowBOT + grid_matrix[i][12];
      rowHOR = rowHOR + grid_matrix[i][7];
      rowHOR = rowHOR + grid_matrix[i][5];
      rowHOR = rowHOR + grid_matrix[i][6];
    }
  }
  // Some adjacent elements are removed to decrease errors
  rowHOR = rowHOR - grid_matrix[0][7] - grid_matrix[0][5] - grid_matrix[8][7] - grid_matrix[8][5] - grid_matrix[7][7] - grid_matrix[8][7] ;
  colVER = colVER - grid_matrix[5][0] - grid_matrix[3][0] - grid_matrix[5][12] - grid_matrix[3][12] - grid_matrix[5][11] - grid_matrix[3][11];
  rowTOP = rowTOP/13;
  rowBOT = rowBOT/13;
  rowHOR = rowHOR/13;
  
  // debugging lines depicting the summations
  print("\nrowTOP: ");
  print(rowTOP);
  print("\nrowBOT: ");
  print(rowBOT);
  print("\nrowHOR: ");
  print(rowHOR);
  print("\ncolLEF: ");
  print(colLEF);
  print("\ncolRIG: ");
  print(colRIG);
  print("\ncolVER: ");
  println(colVER);
  
  // function to check what alphabet has been 'written'
  conv_char = check_char(rowTOP, rowBOT, rowHOR, colLEF, colRIG, colVER, conv_char);
 
  // debugging line to show what the alphabet is that has been written
  print("\nChar: ");
  println(conv_char);
  
  // displays the character on the draw box as the final result
  textSize(40);
  fill(200, 27, 27);
  textAlign(CENTER);
  text(conv_char, 200, 650);

}
}

// function to process and return what alphabet has been input
char check_char(int T, int B, int H, int L, int R, int V, char letter)
{
  // Convert the sums to simple 1,0 and 2 depending on stroke lengths
  // 1 -> line exists
  // 0 -> no line exists
  // 2 -> half line exists
  if(T >= 7)
    T = 1;
  else if(T>=4)
    T = 2;
  else T = 0;
  
  if(B >= 7)
    B = 1;
  else if(B>=4)
    B = 2;
  else B = 0;
  
  if(H >= 7)
    H = 1;
  else if(H >=5)
    H = 2;
  else H = 0;
  
  if(L >= 10)
    L = 1;
  else if(L >= 5)
    L = 2;
  else L = 0;
  
  if(R >= 10)
    R = 1;
  else if(R >= 5)
    R = 2;
  else R = 0;
  
  if(V >= 10)
    V = 1;
  else if(V >= 7)
    V = 2;
  else V = 0;
  
  // debugging line to show the T, B, H, L, R , V values
  println("\nT  B  H  L  R  V");
  print(T);
  print("  ");
  print(B);
  print("  ");
  print(H);
  print("  ");
  print(L);
  print("  ");
  print(R);
  print("  ");
  println(V);
  
  // checks with the characteristics of each alphabet
  if((T==1)&&(B==0)&&(H==1)&&(L==1)&&(R==1)&&(V==0))
  letter = 'A';
  else if((T==1)&&(B==1)&&(H==1)&&(L==1)&&(R==1)&&(V==0))
  letter = 'B';
  else if((T==1)&&(B==1)&&(H==0)&&(L==1)&&(R==0)&&(V==0))
  letter = 'C';
  else if((T==2)&&(B==2)&&(H==0)&&(L==1)&&(R==0)&&(V==0))
  letter = 'D';
  else if((T==1)&&(B==1)&&(H==1)&&(L==1)&&(R==0)&&(V==0))
  letter = 'E';
  else if((T==1)&&(B==0)&&(H==1)&&(L==1)&&(R==0)&&(V==0))
  letter = 'F';
  else if((T==1)&&(B==1)&&(H==0)&&(L==1)&&(R==2)&&(V==0))
  letter = 'G';
  else if((T==0)&&(B==0)&&(H==1)&&(L==1)&&(R==1)&&(V==0))
  letter = 'H';
  else if((T==0)&&(B==0)&&(H==0)&&(L==0)&&(R==0)&&(V==1))
  letter = 'I';
  else if((T==1)&&(B==2)&&(H==0)&&(L==0)&&(R==0)&&(V==1))
  letter = 'J';
  else if((T==0)&&(B==0)&&((H==1)||(H==2))&&(L==1)&&(R==0)&&((V==0)||(V==2))
  letter = 'K';
  else if((T==0)&&(B==1)&&(H==0)&&(L==1)&&(R==0)&&(V==0))
  letter = 'L';
  else if((T==1)&&(B==0)&&(H==1)&&(L==1)&&(R==1)&&(V==1))
  letter = 'M';
  else if((T==2)&&(B==2)&&(H==0)&&(L==1)&&(R==1)&&(V==0))
  letter = 'N';
  else if((T==1)&&(B==1)&&(H==0)&&(L==1)&&(R==1)&&(V==0))
  letter = 'O';
  else if((T==1)&&(B==0)&&(H==1)&&(L==1)&&(R==2)&&(V==0))
  letter = 'P';
  else if((T==1)&&(B==1)&&(H==2)&&(L==1)&&(R==1)&&(V==0))
  letter = 'Q';
  else if((T==1)&&(B==0)&&(H==1)&&(L==1)&&(R==2)&&(V==2))
  letter = 'R';
  else if((T==2)&&(B==1)&&(H==2)&&(L==2)&&(R==0)&&(V==2))
  letter = 'S';
  else if((T==1)&&(B==0)&&(H==0)&&(L==0)&&(R==0)&&(V==1))
  letter = 'T';
  else if((T==0)&&(B==1)&&(H==0)&&(L==1)&&(R==1)&&(V==0))
  letter = 'U';
  else if((T==0)&&(B==0)&&((H==0)||(H==2))&&(L==2)&&(R==2)&&(V==0)||(V==2))
  letter = 'V';
  else if((T==0)&&(B==1)&&(H==1)&&(L==1)&&(R==1)&&(V==1))
  letter = 'W';
  else if((T==2)&&(B==2)&&(H==1)&&(L==2)&&(R==2)&&(V==1))
  letter = 'O';
  else if((T==0)&&(B==0)&&(H==1)&&(L==2)&&(R==2)&&(V==2))
  letter = 'Y';
  else if((T==1)&&(B==1)&&(H==1)&&(L==2)&&(R==2)&&(V==0))
  letter = 'Z';
  else letter = '?'; // if none of them match, sets it as a question mark
  
  return letter; // returns the alphabet
}

// function to draw the grid pixels
void draw_grid()
{
  // draws all the circles
  fill(250, 250, 250);
  noStroke();
  for(int i = 1; i < 10; i++)
  for(int j = 1; j < 14; j++)
  ellipse(i*40+10,j*40+50,27,27);
  rect(175, 610, 50, 50, 7);
  
  // creates the title
  textSize(36);
  fill(165, 27, 27);
  text("Capacitive Touch Grid", 20, 45);
}
  
  
