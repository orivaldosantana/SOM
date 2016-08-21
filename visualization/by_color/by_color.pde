
// A Table object
Table table;

int r, g, b; 

void setup() {
  size(640, 360);
  loadData();
}

void draw() {
  background(230);

  showSOM(30,20); 
  
}

void showSOM(int initialXNode, int initialYNode) {

  int xNode, yNode, i, j;
  int nodeSize = 20; 
  int nodeSpacing = 5; 
  
  for (TableRow row : table.rows()) {
      // You can access the fields via their column name (or index)
      i = row.getInt("x"); 
      j = row.getInt("y"); 
      r = int(row.getFloat("r")*255);
      g = int(row.getFloat("g")*255);
      b = int(row.getFloat("b")*255);      
      xNode = initialXNode + i*(nodeSize + nodeSpacing); 
      yNode = initialYNode + j*(nodeSize + nodeSpacing);
      fill(r, g, b);
      ellipse(xNode, yNode, nodeSize, nodeSize);
      println("("+i+","+j+", "+r+","+g+","+b+")"); 
  }
  
}

void loadData() {
  // Load CSV file into a Table object
  // "header" option indicates the file has a header row
  table = loadTable("../../output/color_150.csv", "header");
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}