// Libraries
import processing.serial.*; // imports the Serial library that allows communication with Arduino
import matrixMath.*; // imports the matrix library which allows the use of matrices

Serial myPort; // creates a serial object that will be used as an identifier for the port

// Variables
int[][] tic = { {4, 4 , 4}, {4, 4 , 4}, {4, 4 , 4} }; // initiate a 3x3 matrix filled with 4's
String val = "start"; // variable to store the incoming data in form of string type
int newval;  // stores string converted to integer type
int counter = 0; // counter that is used to change the turn (O -> X -> O and so on)
// sums of each row, column & diagonal with defaults being 12 because the matrix has only 4's
int row1sum = 12;
int row2sum = 12;
int row3sum = 12;
int col1sum = 12;
int col2sum = 12;
int col3sum = 12;
int diag1sum = 12;
int diag2sum = 12;
int winner = 2; // winner status to know when to stop (0 is O & 1 is X & 3 is draw)

// setup function
void setup()
{
  size(400, 400); // creates a 'draw' window where the tic tac toe program will be implemented
  background(200); // sets the background colour
  myPort = new Serial(this, Serial.list()[0], 19200); // listens to data on baud 19200
  myPort.clear(); // clears any buffer values
  tile(); // function to create the tic-tac-toe 'grid' layout
}

// draw function
void draw()
{
  // checks if X has won
  if(((col1sum==0)||(col2sum==0)||(col3sum==0)||(row1sum==0)||(row2sum==0)||(row3sum==0)||(diag1sum==0)||(diag2sum==0))&&(winner==2))
  {
    Xwins(col1sum, col2sum, col3sum, row1sum, row2sum, row3sum, diag1sum, diag2sum); // outputs X winner message
    winner = 1; // sets X as winner
  }
  // checks if O hsa won
  else if(((col1sum==3)||(col2sum==3)||(col3sum==3)||(row1sum==3)||(row2sum==3)||(row3sum==3)||(diag1sum==3)||(diag2sum==3))&&(winner==2))
  {
    Owins(col1sum, col2sum, col3sum, row1sum, row2sum, row3sum, diag1sum, diag2sum); // outputs O winner message
    winner = 0; // sets O as winner
  }
  // checks if the game is drawn
  else if((counter == 9)&&(winner==2))
  {
    GameDrawn(); // outputs game drawn message
    winner = 3; // sets the game as draw
  }
  else if(winner==2) // if no result proceed with seeking input
  {
  while ( myPort.available() > 0) // checks if any data is coming through
  {  
  // if data is available,
  val = myPort.readString(); // stores the value in val
  //println(val); // debug line to show what key has been pressed
  newval = parseInt(val); // converts string to integer type and stores in newval
  }
  
  // Logic switch statement to check if the key pressed has already been pressed before.
  // If it has, go back to input without changing the counte, the matrix or the interface.
  // If it hasn't: if counter is even, save it as an O and change the corresponding matrix
    // element to 1 and draw the O on the respective tile and the same goes for when
    // the counter is odd and X is drawn while the matrix element is set to 0
  switch(newval)
  {
    case 1:
    if(tic[0][0]==4) // checks if matrix element has been changed
    {
      if(counter%2==0) // if it hasn't, checks if counter is even
      {
        tic[0][0]=1; // saves the corresponding matrix element as 1 to represent O
        fill(0, 102,153); // colours the going to be drawn 'O' to blue
        text("O",90,110); // draws the O in the respective box
      }
      else
      {
        tic[0][0]=0; // saves the corresponding matrix element as 0 to represent X
        fill(165, 27, 27); // colours the going to be drawn 'X' to red
        text("X",90,110); // draws the X in the respective box
      }
      counter++; // increments counter to go to next turn
    }
    break; // breaks out of switch statement
    case 2:
    if(tic[0][1]==4)
    {
      if(counter%2==0)
      {
        tic[0][1]=1;
        fill(0, 102,153);
        text("O",190,110);
      }
      else
      {
        tic[0][1]=0;
        fill(165, 27, 27);
        text("X",190,110);
      }
      counter++;
    }
    break;
    case 3:
    if(tic[0][2]==4)
    {
      if(counter%2==0)
      {
        tic[0][2]=1;
        fill(0, 102,153);
        text("O",290,110);
      }
      else
      {
        tic[0][2]=0;
        fill(165, 27, 27);
        text("X",290,110);
      }
      counter++;
    }
    break;
    case 4:
    if(tic[1][0]==4)
    {
      if(counter%2==0)
      {
        tic[1][0]=1;
        fill(0, 102,153);
        text("O",90,210);
      }
      else
      {
        tic[1][0]=0;
        fill(165, 27, 27);
        text("X",90,210);
      }
      counter++;
    }
    break;
    case 5:
    if(tic[1][1]==4)
    {
      if(counter%2==0)
      {
        tic[1][1]=1;
        fill(0, 102,153);
        text("O",190,210);
      }
      else
      {
        tic[1][1]=0;
        fill(165, 27, 27);
        text("X",190,210);
      }
      counter++;
    }
    break;
    case 6:
    if(tic[1][2]==4)
    {
      if(counter%2==0)
      {
        tic[1][2]=1;
        fill(0, 102,153);
        text("O",290,210);
      }
      else
      {
        tic[1][2]=0;
        fill(165, 27, 27);
        text("X",290,210);
      }
      counter++; 
    }
    break;
    case 7:
    if(tic[2][0]==4)
    {
      if(counter%2==0)
      {
        tic[2][0]=1;
        fill(0, 102,153);
        text("O",90,310);
      }
      else
      {
        tic[2][0]=0;
        fill(165, 27, 27);
        text("X",90,310);
      }
      counter++;
    }
    break;
    case 8:
    if(tic[2][1]==4)
    {
      if(counter%2==0)
      {
        tic[2][1]=1;
        fill(0, 102,153);
        text("O",190,310);
      }
      else
      {
        tic[2][1]=0;
        fill(165, 27, 27);
        text("X",190,310);
      }
      counter++;
    }
    break;
    case 9:
    if(tic[2][2]==4)
    {
      if(counter%2==0)
      {
        tic[2][2]=1;
        fill(0, 102,153);
        text("O",290,310);
      }
      else
      {
        tic[2][2]=0;
        fill(165, 27, 27);
        text("X",290,310);
      }
      counter++; 
    }
    default: break; // default break statement if number is garbage value
  }
  
  // updates the row, column and diagonal sums
  row1sum = tic[0][0] + tic[0][1] + tic[0][2];
  row2sum = tic[1][0] + tic[1][1] + tic[1][2];
  row3sum = tic[2][0] + tic[2][1] + tic[2][2];
  col1sum = tic[0][0] + tic[1][0] + tic[2][0];
  col2sum = tic[0][1] + tic[1][1] + tic[2][1];
  col3sum = tic[0][2] + tic[1][2] + tic[2][2];
  diag1sum = tic[0][0] + tic[1][1] + tic[2][2];
  diag2sum = tic[2][0] + tic[1][1] + tic[0][2];
  }
}
  
// draws the X & O's tile grid
void tile()
{
  textSize(32);
  fill(27, 27, 27); // colours the text
  text("Tic-Tac-Toe",width/4,35); // title text
  
  // grid lines
  strokeWeight(3); 
  stroke(126);
  line(50,150,350,150);
  line(50,250,350,250);
  line(150,50,150,350);
  line(250,50,250,350);
}

// Xwins function
void Xwins(int col1sum, int col2sum, int col3sum, int row1sum, int row2sum, int row3sum, int diag1sum, int diag2sum)
{
    //println("X wins!"); // debug X Wins print statement
    // displays textual message that X won
    textSize(40);
    fill(165, 27, 27);
    text("X WINS!" ,width/3, 385);
    
    // draws the respective 'strike throughs' for the respective winning row/col/diagonal
    stroke(165, 27, 27);
    if(row1sum==0)
    line(70,98,330,98);
    if(row2sum==0)
    line(70,198,330,198);
    if(row3sum==0)
    line(70,298,330,298);
    if(col1sum==0)
    line(100,60,100,320);
    if(col2sum==0)
    line(200,60,200,320);
    if(col3sum==0)
    line(300,60,300,320);
    if(diag1sum==0)
    line(75,75,325,320);
    if(diag2sum==0)
    line(75,325,325,75);
}
  
// Owins function
void Owins(int col1sum, int col2sum, int col3sum, int row1sum, int row2sum, int row3sum, int diag1sum, int diag2sum)
{
    //println("O wins!");  // debug X Wins print statement
    // displays textual message that O won
    textSize(40);
    fill(0, 102,153);
    text("O WINS!", width/3,385);
    
    // draws the respective 'strike throughs' for the respective winning row/col/diagonal
    stroke(0, 102,153);
    if(row1sum==3)
    line(70,98,330,98);
    if(row2sum==3)
    line(70,198,330,198);
    if(row3sum==3)
    line(70,298,330,298);
    if(col1sum==3)
    line(100,60,100,320);
    if(col2sum==3)
    line(200,60,200,320);
    if(col3sum==3)
    line(300,60,300,320);
    if(diag1sum==3)
    line(75,75,325,320);
    if(diag2sum==3)
    line(75,325,325,75);
}

void GameDrawn()
{
    //println("Game Drawn!");  // debug Game Drawn print statement
    // displays textual message that game was drawn
    textSize(40); // sets text size to 40 pixels
    fill(27, 27, 27); // changes text colour
    text("Game Drawn!", width/5, 385); // outputs result as game drawn
}
