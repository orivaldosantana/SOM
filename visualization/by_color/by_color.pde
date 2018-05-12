
SomVisualizer som;  

Button button; 

int iterationView; 

int contFrames; 

boolean playState; 

void setup() { 
  playState = false; 
  contFrames = 0; 
  iterationView = 0; 
  size(880, 1000);
  frameRate(30); 
  int somFrameSize = 800;
  int iniYSomFrame = 80; 
  int iniXSomFrame = 80; 
  som = new SomVisualizer( iniXSomFrame, iniYSomFrame , somFrameSize,3); 
  button = new Button("Play",iniXSomFrame - 25, somFrameSize + iniYSomFrame, somFrameSize, 50);  
}

void draw() {
  background(230);
  som.Draw(); 
  button.Draw(); 
  
  contFrames++; 
  if (contFrames > 5 && playState) {
    contFrames = 0;
   
  if ( som.loadData(iterationView) ) { 
     button.SetLabel("Stop - it "+iterationView);
     iterationView++;
  }
  else { 
     playState = false; 
     iterationView = 0;
     button.SetLabel("Finished");
   }
 }

  
}

void mouseClicked() {
  if (button.MouseIsOver()) {
     println("click");  
     playState = true; 
     button.SetLabel("Stop"); 
     som.loadData(0);
  }
  
}

void keyPressed() {
   if (key == 'p') {
      playState = true; 
      println("Executing"); 
   }
  
}
