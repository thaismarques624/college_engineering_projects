let color_buffer = new Canvas("canvas");
color_buffer.clear();

function MidPointLineAlgorithm(x0, y0, x1, y1, color_0,color_1) {
  // Escreva seu código aqui!
  let x, y, dx1, dy1, dx0, dy0, px, py, x_aux, y_aux, i; 
  let color = [255,255,255,255];
  var dx, dy;
  var dr, dg, db;

  dx1 = x1 - x0;
  dy1 = y1 - y0;    
  dx0 = Math.abs(dx1);
  dy0 = Math.abs(dy1);    
  px = 2 * dy0 - dx0;
  py = 2 * dx0 - dy0;    

  if(dx0 < dy0){    
	  dr = (color_1[0] - color_0[0])/dy;
 	  dg = (color_1[1] - color_0[1])/dy;
    db = (color_1[2] - color_0[2])/dy;
  }
  else{
    dr = (color_1[0] - color_0[0])/dx;
    dg = (color_1[1] - color_0[1])/dx;
    db = (color_1[2] - color_0[2])/dx;
  }
  
  if (dy0 <= dx0) {        
    if (dx1 >= 0) {
      x = x0; y = y0; x_aux = x1;
    } else { 
      x = x1; y = y1; x_aux = x0;
    }        

    //rasterizando 
    for (i = 0; x < x_aux; i++) {
      x = x + 1;
      if(dy0 <= dx0){
        dx = x_aux - x;
        dr = parseInt((color_1[0] - color_0[0])/dx);
        dg = parseInt((color_1[1] - color_0[1])/dx);
        db = parseInt((color_1[2] - color_0[2])/dx);
        color_0[0] = color_0[0] + dr;
        color_0[1] = color_0[1] + dg;
        color_0[2] = color_0[2] + db;
      }

      if (px < 0) {
        px = px + 2 * dy0;
      } else {
        if ((dx1 < 0 && dy1 < 0) || (dx1 > 0 && dy1 > 0)) {
          y = y + 1;
          d_y = y0 - y;
        } else {
          y = y - 1;
          d_y = y0 - y;
        }
        px = px + 2 * (dy0 - dx0);
      }            
      
      color_buffer.putPixel(x, y, color_0);
    }

  } else { 
    if (dy1 >= 0) {
      x = x0; y = y0; y_aux = y1;
    } else { 
      x = x1; y = y1; y_aux = y0;
    }     

    // Rasterizando 
    for (i = 0; y < y_aux; i++) {
      if(dx0 <= dy0){
        dy = y_aux - y;
        dr = parseInt((color_1[0] - color_0[0])/dy);
        dg = parseInt((color_1[1] - color_0[1])/dy);
        db = parseInt((color_1[2] - color_0[2])/dy);
        
        color_0[0] = color_0[0] + dr;
        color_0[1] = color_0[1] + dg;
        color_0[2] = color_0[2] + db;
      }
      y = y + 1;
      if (py <= 0) {
        py = py + 2 * dx0;
      } else {
        if ((dx1 < 0 && dy1<0) || (dx1 > 0 && dy1 > 0)) {
          x = x + 1;
          d_x = x1 - x;
        } else {
          x = x - 1;
          d_x = x0 - x;
        }
        py = py + 2 * (dx0 - dy0);
      }            

      color_buffer.putPixel(x, y, color_0);
    }
  } 

}



function DrawTriangle(x0, y0, x1, y1, x2, y2, color_0, color_1, color_2) {
  const initial_zero = color_0;
  const initial_one = color_1;
  const initial_two = color_2;
  
  MidPointLineAlgorithm(x0, y0, x1, y1, initial_zero, initial_one);
  MidPointLineAlgorithm(x1,y1, x2,y2, color_2, color_1);
  MidPointLineAlgorithm(x2,y2, x0,y0, color_0, color_2);

}


MidPointLineAlgorithm(64,66,64,96,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(66,66,81,96,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(66,66,96,96,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(66,66,96,81,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(66,64,96,64,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(66,62,96,47,[255,0,0,255],[255,255,0,255]); 
MidPointLineAlgorithm(66,62,96,32,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(66,62,81,32,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(64,62,64,32,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,62,47,32,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,62,32,32,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,62,32,32,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,62,32,47,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,64,32,64,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,66,32,81,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,66,32,96,[255,0,0,255],[255,255,0,255]);
MidPointLineAlgorithm(62,66,47,96,[255,0,0,255],[255,255,0,255]);



DrawTriangle(25,30,50,100,100,15,[255,0,0,255],[0,0,255,255],[0,255,0,255]);
