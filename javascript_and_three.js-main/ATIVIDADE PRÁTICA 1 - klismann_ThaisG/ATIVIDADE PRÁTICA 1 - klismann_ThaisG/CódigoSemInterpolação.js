let color_buffer = new Canvas("canvas");
color_buffer.clear();

function MidPointLineAlgorithm(x0, y0, x1, y1, color_0,color_1) {
	// Escreva seu código aqui!
 var x, y, dx1, dy1, dx0, dy0, ix, iy, x_aux, y_aux, i; 
        
        //Calculando o delta das linhas
        dx1 = x1 - x0;
        dy1 = y1 - y0;  
  
       //Ajustando para sempre inteiro positivo. 
        dx0 = Math.abs(dx1);
        dy0 = Math.abs(dy1); 
  
        //Calculando intervalos para ambos os eixos.
        ix = 2 * dy0 - dx0;
        iy = 2 * dx0 - dy0;   
  
              
        // Se a linha for  do dominio de X, passar pelas proximas condições,
        if (dy0 <= dx0) {  // para saber por onde começar a desenhar.
            if (dx1 >= 0) { // trocando as coordenadas
                x = x0;
                y = y0;
                x_aux = x1;
            } else { 
                x = x1; 
                y = y1; x_aux = x0;
            }        
            color_buffer. putPixel(x, y, color_0); // desenhando o primeiro pixel
          
           //rasterizando nos octantes 
            for (i = 0; x < x_aux; i++) {
                x = x + 1;  
              
                if (ix < 0) {
                    ix = ix + 2 * dy0;
                } else {
                    if ((dx1 < 0 && dy1 < 0) || (dx1 > 0 && dy1 > 0)) {
                        y = y + 1;
                    } else {
                        y = y - 1;
                    }
                    ix = ix + 2 * (dy0 - dx0);
                }            
               
                color_buffer. putPixel(x, y, color_0);
              
              
            }
          
            } else {  // aqui é o else do primeiro if, se a linha estiver no dominio de Y, 
            if (dy1 >= 0) {// ocorre o mesmo processo agora tratando pelo Y.
                x = x0; 
                y = y0; 
                y_aux = y1;
            } else { 
                x = x1; 
                y = y1; 
                y_aux = y0;
            }     
             
              color_buffer. putPixel(x, y, color_0, color_1);
            
              // Rasterizando 
              for (i = 0; y < y_aux; i++) {
                y = y + 1;           
                if (iy <= 0) {
                    iy = iy + 2 * dx0;
                } else {
                    if ((dx1 < 0 && dy1<0) || (dx1 > 0 && dy1 > 0)) {
                        x = x + 1;
                    } else {
                        x = x - 1;
                    }
                    iy = iy + 2 * (dx0 - dy0);
                }            
                color_buffer. putPixel(x, y, color_0, color_1); // saída de redenrização
            }
        } 
   
     }

  
 
function DrawTriangle(x0, y0, x1, y1, x2, y2, color_0, color_1, color_2) {
  // O que foi feito aqui? Apenas chamei a MidPointLineAlgorithm
  //e organizei as coordenadas para desenhar o triangulo.
  MidPointLineAlgorithm(x0, y0, x1, y1, color_0, color_1);
  MidPointLineAlgorithm(x1,y1, x2,y2, color_1, color_2);
  MidPointLineAlgorithm(x2,y2, x0,y0, color_2, color_0);
  
  
	
}

//MidPointLineAlgorithm(64,64,64,64,[255,0,0,255],[255,255,0,255]); // desenhando um pixel

//MidPointLineAlgorithm(25,30,100,80,[255,0,0,255],[255,255,0,255]); // linha exemplo

//Testes sugeridos por um colega.
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