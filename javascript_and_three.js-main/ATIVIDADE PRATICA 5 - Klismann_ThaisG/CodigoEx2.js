///////////////////////////////////////////////////////////////////////////////
// Funcao que desenha um pixel colorido no canvas.
// Entrada: 
//   x, y: Coordenadas de tela do pixel.
//   color: Cor do pixel no formato RGB (THREE.Vector3).
// Retorno:
//   Sem retorno.
///////////////////////////////////////////////////////////////////////////////
function PutPixel(x, y, color) {
  let c = document.getElementById("canvas");
  let ctx = c.getContext("2d");
  let r = Math.min(255, Math.max(0, Math.round(color.x * 255)));
  let g = Math.min(255, Math.max(0, Math.round(color.y * 255)));
  let b = Math.min(255, Math.max(0, Math.round(color.z * 255)));
  ctx.fillStyle = 'rgb(' + r + ',' + g + ',' + b + ')';
  ctx.fillRect(x, y, 1, 2);
}

///////////////////////////////////////////////////////////////////////////////
// Classe que representa um raio de luz.
// Construtor: 
//   origem: Ponto de origem do raio (THREE.Vector3).
//   direcao: Vetor unitario que indica a direcao do raio (THREE.Vector3).
///////////////////////////////////////////////////////////////////////////////
class Raio {
  constructor(origem, direcao) {
    this.origem = origem;
    this.direcao = direcao;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Classe que representa a camera.
// Construtor: 
//   Sem parametros. Os atributos da camera estao 'hard coded' no construtor.
///////////////////////////////////////////////////////////////////////////////
class Camera {
  constructor() {
    this.resolucaoX = 512; // Resolucao do sensor em X.
    this.resolucaoY = 512; // Resolucao do sensor em Y.
    this.d = 1.0;          // Distancia do sensor em relacao a posicao da camera.
    this.xMin = -1.0;      // Extremidade esquerda do sensor.
    this.xMax =  1.0;      // Extremidade direita do sensor.
    this.yMin = -1.0;      // Extremidade inferior do sensor.
    this.yMax =  1.0;      // Extremidade superior do sensor.
    this.k = new THREE.Vector3(this.xMin, this.yMax, -this.d);   // Canto superior esquerdo do sensor.
    this.a = new THREE.Vector3(this.xMax - this.xMin, 0.0, 0.0); // Vetor para calculo de um ponto sobre o sensor.
    this.b = new THREE.Vector3(0.0, this.yMin - this.yMax, 0.0); // Vetor para calculo de um ponto sobre o sensor.
  }

  ///////////////////////////////////////////////////////////////////////////////
  // Metodo que converte coordenadas (x,y) de tela para um raio 
  // primario que passa pelo centro do pixel no espaco do universo.
  // Entrada: 
  //   x, y: Coordenadas de tela do pixel.
  // Retorno:
  //   Um objeto do tipo Raio.
  ///////////////////////////////////////////////////////////////////////////////
  raio(x, y) {
    let u = (x + 0.5) / this.resolucaoX;
    let v = (y - 0.5) / this.resolucaoY;
    let p = ((this.a.clone().multiplyScalar(u)).add(this.b.clone().multiplyScalar(v))).add(this.k);

    let origem = new THREE.Vector3(0.0,0.0,0.0);
    let direcao = p.normalize();

    return new Raio(origem, direcao);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Classe que representa um ponto de interseccao entre o raio e uma primitiva.
// Construtor: 
//   Sem parametros. As propriedades de um objeto desta classe sao preenchidas
//   assim que uma interseccao raio-primitiva e detectada.
///////////////////////////////////////////////////////////////////////////////
class Interseccao {
  constructor() {
    this.t = Infinity; // distancia entre a origem do rio e o ponto de intersecao.
    this.posicao = new THREE.Vector3(0.0, 0.0, 0.0); // Coordenadas do ponto de interseccao.
    this.normal = new THREE.Vector3(0.0, 0.0, 0.0);  // Vetor normal no ponto de interseccao.
  }
}

///////////////////////////////////////////////////////////////////////////////
// Classe que representa o triangulo
// Construtor: 
//   centro: Coordenadas do centro da esfera no espaco do universo (THREE.Vector3).
//   raio: Raio da esfera.
///////////////////////////////////////////////////////////////////////////////
class Triangle {
  constructor(v1,v2, v3) {
    this.v1 = v1;
    this.v2 = v2;
    this.v3 = v3;
  }

  ///////////////////////////////////////////////////////////////////////////////
  // Metodo que testa a interseccao entre o raio e o triangulo, adaptando o algoritmo de Möller e Trumbore.
  ///////////////////////////////////////////////////////////////////////////////
  
  interseccionar(raio, interseccao) {
    
    let edge1 = this.v2.clone().sub(this.v1);
    let edge2 = this.v3.clone().sub(this.v1);
    let h = raio.direcao.clone().cross(edge2);
    let a = edge1.clone().dot(h);
    
    if (Math.abs(a) < 0.001) // Este raio é paralelo a este triângulo.
      return false;
    
    let f = 1.0 / a;
    
    let s = raio.origem.clone().sub(this.v1);
    let u = s.clone().dot(h) * f;
    
    if (u < 0.0 || u > 1.0)
      return false;
    
    let q = s.clone().cross(edge1);
    let v = raio.direcao.clone().dot(q) * f;
    
    if (v < 0.0 || u + v > 1.0)
      return false;
    
    
    interseccao.t = edge2.clone().dot(q) * f; // Aqui podemos calcular t para descobrir onde está o ponto de interseção na linha.
  
    let w0 = this.v1.clone().multiplyScalar(1 - u - v);
    let u1 = this.v2.clone().multiplyScalar(u);
    let v2 = this.v3.clone().multiplyScalar(v);
    interseccao.posicao = w0.add(u1).add(v2);
    
    // Aqui acontece o calculo do vetor normal de interseccao com o triangulo.
    let p2 = this.v3.clone().sub(interseccao.posicao);
    let p1 = this.v2.clone().sub(interseccao.posicao)
    interseccao.normal = p2.cross(p1).normalize();

    return true;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Classe que representa uma fonte de luz pontual.
// Construtor: 
//   posicao: Posicao da fonte de luz pontual no espaco (THREE.Vector3).
//   cor: Cor da fonte de luz no formato RGB (THREE.Vector3).
///////////////////////////////////////////////////////////////////////////////
class Luz {
  constructor(posicao, cor) {
    this.posicao = posicao;
    this.cor = cor;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Funcao que renderiza a cena utilizando ray tracing.
// Entrada: 
//  Sem entradas.
// Retorno:
//   Sem retorno.
///////////////////////////////////////////////////////////////////////////////
function Render() {
  let camera = new Camera();
  let t1 = new Triangle(new THREE.Vector3(-1.0, -1.0, -3.5), 
                         new THREE.Vector3(1.0, 1.0, -3.0), 
                         new THREE.Vector3(0.75, -1.0, -2.5)); //correção aplicada em -0.75 para 0.75
  let Ip = new Luz(new THREE.Vector3(-10.0, 10.0, 4.0), new THREE.Vector3(0.9, 0.9, 0.9));

  // Lacos que percorrem os pixels do sensor.
    for (let y = 0; y < 512; ++y)
    for (let x = 0; x < 512; ++x) {

      let raio = camera.raio(x,y); // Construcao do raio primario que passa pelo centro do pixel de coordenadas (x,y).
      let interseccao = new Interseccao(); 

      if (t1.interseccionar(raio, interseccao)) { // Se houver interseccao entao...

        let ka = new THREE.Vector3(1.0, 0.0, 0.0);  // Coeficiente de reflectancia ambiente do triangulo.
        let kd = new THREE.Vector3(1.0, 0.0, 0.0);  // Coeficiente de reflectancia difusa do triangulo.
            
        let ks = new THREE.Vector3(1.0,1.0, 1.0); // Coeficiente de reflectancia specular do triangulo.
        
        let Ia = new THREE.Vector3(0.2, 0.2, 0.2);  // Intensidade da luz ambiente. 

        let termo_ambiente = Ia.clone().multiply(ka); // Calculo do termo ambiente do modelo local de iluminacao.

        let L = (Ip.posicao.clone().sub(interseccao.posicao)).normalize(); // Vetor que aponta para a fonte e luz pontual.

        // Calculo do termo difuso do modelo local de iluminacao.
        let termo_difuso = (Ip.cor.clone().multiply(kd)).multiplyScalar(Math.max(0.0, interseccao.normal.dot(L)));
         
       
        
        let v = interseccao.posicao.normalize();
        let r = L.clone().reflect(interseccao.normal);
  
        let termo_specular = Ip.cor.clone().multiply(ks).multiplyScalar((Math.max(0.0, r.dot(v)))**32)
        
        
        PutPixel(x, y, termo_difuso.add(termo_ambiente).add(termo_specular)); // Combina os termos difuso e ambiente e pinta o pixel.
      } else // Senao houver interseccao entao...
        PutPixel(x, y, new THREE.Vector3(0.0, 0.0, 0.0)); // Pinta o pixel com a cor de fundo.
    }
}

Render(); // Invoca o ray tracer.
