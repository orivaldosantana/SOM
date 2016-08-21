
// A Table object
Table table;

int r, g, b; 

void setup() {
  size(640, 360);
  loadData();
}

void draw() {
  background(255);
  int x = 30; 
  for (TableRow row : table.rows()) {
    // You can access the fields via their column name (or index)
    r = row.getInt("r");
    g = row.getInt("g");
    b = row.getInt("b");
    println("("+r+","+g+","+b+")"); 
    fill(r, g, b);
    rect(x, 20, 20, 20);
    x = x + 30; 
  }
  
  
}

void loadData() {
  // Load CSV file into a Table object
  // "header" option indicates the file has a header row
  table = loadTable("data.csv", "header"); 

  // You can access iterate over all the rows in a table
 

}