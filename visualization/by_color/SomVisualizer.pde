class SomVisualizer {

  // A Table object
  Table table;
  
  int nodeSize; 
  int nodeSpacing;
  int xFrame; 
  int yFrame; 
  int initialXNode;   
  int initialYNode; 
  int frameSize; 
  String dataPath; 
  String fileDataName; 
  int rowNumber;
  int dataScale; 
  
  SomVisualizer(int iXNode, int iYNode, int fSize, int dScale) {
    dataScale = dScale; 
    dataPath = "../../output/";
    fileDataName = "ura"; 
    rowNumber = 0;
    if ( loadData(0) ) {
      rowNumber = table.getRowCount();
    }
    initialXNode = iXNode; 
    initialYNode = iYNode;
    frameSize = fSize; 
    
    
     
    float sizeSOM = sqrt(rowNumber);
    int nodeDrawSize = int(frameSize/sizeSOM); 
    nodeSpacing = (nodeDrawSize*20)/100;   
    nodeSize = nodeDrawSize - nodeSpacing;
    
    xFrame = initialXNode - (nodeSize + nodeSpacing)/2; 
    yFrame = initialYNode - (nodeSize + nodeSpacing)/2;  
    
 
  }
    
  void Draw(){
    int r, g, b; 
    int xNode, yNode, i, j;
    fill(255);
    stroke(200); 
    rect( xFrame, yFrame, frameSize, frameSize,10); 
    
    //if ( rowNumber > 0) {
      for (TableRow row : table.rows()) {
          // You can access the fields via their column name (or index)
          i = row.getInt("x"); 
          j = row.getInt("y"); 
          r = int(row.getFloat("r")*dataScale);
          g = int(row.getFloat("g")*dataScale);
          b = int(row.getFloat("b")*dataScale);      
          xNode = initialXNode + i*(nodeSize + nodeSpacing); 
          yNode = initialYNode + j*(nodeSize + nodeSpacing);
          fill(r, g, b);
          ellipse(xNode, yNode, nodeSize, nodeSize);
          //println("("+i+","+j+", "+r+","+g+","+b+")"); 
      }
    //}
  }
  boolean loadData(int n) {
    boolean r = false; 
    // Load CSV file into a Table object
    // "header" option indicates the file has a header row
    String fullFileName = dataPath + fileDataName + "_"+n+".csv"; 
    println(fullFileName);
    //table = loadTable("../../output/color_100.csv", "header");
    
    
    try {
      table = loadTable(fullFileName, "header");
      rowNumber =  table.getRowCount();
      if (rowNumber > 0)
        r = true;  
    } catch (Exception e) {
       println("Nao foi possível abrir o arquivo para leitura: "+e);
       fullFileName = dataPath + fileDataName + "_"+(n-1)+".csv";
       table = loadTable(fullFileName, "header");
       rowNumber = 0;
       return false; 
    }
    
    
    return r; 
  }
}
  
