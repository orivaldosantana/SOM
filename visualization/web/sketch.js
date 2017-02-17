
var table;
var tables;
var initialXNode;
var initialYNode;
var nodeSpacing;
var nodeSize;
var countFrame;


const selectionData = 1;

// Objeto para guardar configurações sobre a base de dados cores
var dataSourceColor = {
  sizeSOM: 10,
  snapshotNumber: 140,
  dataName: "color",
  drawColorNodes: function(r,table) {
    i = table.getNum(r, 0);
    j = table.getNum(r, 1);
    cr = table.getNum(r, 2)*255;
    cg = table.getNum(r, 3)*255;
    cb = table.getNum(r, 4)*255;
    xNode = initialXNode + i*(nodeSize + nodeSpacing);
    yNode = initialYNode + j*(nodeSize + nodeSpacing);
    fill(cr, cg, cb);
    ellipse(xNode, yNode, nodeSize, nodeSize);
  }
};
// Objeto para guardar configurações sobre base de dados do braço
// dados usados beta e gamma
var dataSourceArm = {
  sizeSOM: 12,
  snapshotNumber: 240,
  dataName: "arm_in_line",
  drawColorNodes: function(r,table) {
    i = table.getNum(r, 0);
    j = table.getNum(r, 1);
    alphaJoint = table.getNum(r, 2);
    betaJoint = table.getNum(r, 3);
    xNode = nodeSpacing/2 + i*(nodeSize + nodeSpacing);
    yNode = nodeSpacing/2 + j*(nodeSize + nodeSpacing);
    //rect(xNode, yNode, nodeSize, nodeSize, 5, 5, 5, 5);
    rect(xNode, yNode, nodeSize, nodeSize);
    //alphaJoint = 0.6;
    //betaJoint = 0.6;
    linkA = nodeSize/2;
    linkB = linkA;
    xBase = xNode;
    yBase = yNode + nodeSize;
    x1 = xBase + linkA* Math.cos(alphaJoint);
    y1 = yBase - linkA* Math.sin(alphaJoint);
    x2 = x1 + linkB*Math.cos(alphaJoint+betaJoint);
    y2 = y1 - linkB*Math.sin(alphaJoint+betaJoint);
    line(xBase,yBase,x1,y1);
    line(x1,y1,x2,y2);
  }
};

//var dataSource = dataSourceColor;
var dataSource = dataSourceArm;

function preload() {
  table = loadTable("data/"+dataSource.dataName+"_0.csv","csv", "header");
  tables = [table];
  for (i=0; i < dataSource.snapshotNumber; i++) {
    table = loadTable("data/"+dataSource.dataName+"_"+i+".csv","csv", "header");
    tables.push(table);
  }
}


function setup() {
  createCanvas(500, 500);
  background(240);
  countFrame = 1;


  // calculando o tamanho do nodo em relação ao tamanho do canvas
  nodeDrawSize = (width/dataSource.sizeSOM);
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
  if (countFrame > dataSource.snapshotNumber )
    countFrame = 0;


  for (var r = 0; r < tables[countFrame].getRowCount(); r++) {
    /////////////////////////////
    // desenho do nó da rede
    table = tables[countFrame];
    dataSource.drawColorNodes(r,table);
    /////////////////////////////

  }



}
