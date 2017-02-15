 
var table;
var tables; 
var initialXNode;   
var initialYNode;
var nodeSpacing;
var nodeSize; 
var countFrame; 
var snapshotNumber = 140; 

function preload() {

  table = loadTable("data/color_1.csv","csv", "header");
  tables = [table]; 
  for (i=0; i < snapshotNumber; i++) {
    table = loadTable("data/color_"+i+".csv","csv", "header");
    tables.push(table); 
  }
}

function setup() {
  createCanvas(400, 400); 
  background(240); 
  sizeSOM = 10; 
  countFrame = 1;
  
  
  // calculando o tamanho do nodo em relação ao tamanho do canvas 
  nodeDrawSize = (width/sizeSOM); 
  nodeSpacing = (nodeDrawSize*20)/100;   
  nodeSize = nodeDrawSize - nodeSpacing;

  initialXNode = nodeDrawSize/2;
  initialYNode = nodeDrawSize/2; 
  
  //count the columns
  print(table.getRowCount() + " total rows in table");
  print(table.getColumnCount() + " total columns in table");


}

function draw() { 
  frameRate(1); 
  

  countFrame = countFrame + 1;  
  if (countFrame > snapshotNumber )
    countFrame = 0; 
  
  
  for (var r = 0; r < tables[countFrame].getRowCount(); r++) {
    /////////////////////////////
    // desenho do nó da rede 
    table = tables[countFrame]; 
    i = table.getNum(r, 0);
    j = table.getNum(r, 1);
    cr = table.getNum(r, 2)*255;
    cg = table.getNum(r, 3)*255;
    cb = table.getNum(r, 4)*255;
    xNode = initialXNode + i*(nodeSize + nodeSpacing); 
    yNode = initialYNode + j*(nodeSize + nodeSpacing);
    fill(cr, cg, cb);
    ellipse(xNode, yNode, nodeSize, nodeSize);
    /////////////////////////////
    
  }
  
 
  
}