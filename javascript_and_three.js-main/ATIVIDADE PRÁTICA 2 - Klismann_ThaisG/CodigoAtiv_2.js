// Cria um color buffer para armazenar a imagem final.

//let color_buffer = new Canvas("canvas");
//color_buffer.clear();

/******************************************************************************
 * Vértices do modelo (cubo) centralizado no seu espaco do objeto. Os dois
 * vértices extremos do cubo são (-1,-1,-1) e (1,1,1), logo, cada aresta do cubo
 * tem comprimento igual a 2.
 *****************************************************************************/
//                                   X     Y     Z    W (coord. homogênea)
let vertices = [new THREE.Vector4(-1.0, -1.0, -1.0, 1.0),
  new THREE.Vector4( 1.0, -1.0, -1.0, 1.0),
  new THREE.Vector4( 1.0, -1.0,  1.0, 1.0),
  new THREE.Vector4(-1.0, -1.0,  1.0, 1.0),
  new THREE.Vector4(-1.0,  1.0, -1.0, 1.0),
  new THREE.Vector4( 1.0,  1.0, -1.0, 1.0), 
  new THREE.Vector4( 1.0,  1.0,  1.0, 1.0),
  new THREE.Vector4(-1.0,  1.0,  1.0, 1.0)];

/******************************************************************************
* As 12 arestas do cubo, indicadas através dos índices dos seus vértices.
*****************************************************************************/
let edges = [[0,1],
[1,2],
[2,3],
[3,0],
[4,5],
[5,6],
[6,7],
[7,4],
[0,4],
[1,5],
[2,6],
[3,7]];

/******************************************************************************
* Matriz Model (modelagem): Esp. Objeto --> Esp. Universo. 
* OBS: A matriz está carregada inicialmente com a identidade.
*****************************************************************************/
let m_model = new THREE.Matrix4();

m_model.set(1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0);

/******************************************************************************
* Parâmetros da camera sintética.
*****************************************************************************/
let cam_pos = new THREE.Vector3(1.3,1.7,2.0);     // posição da câmera no esp. do Universo.
let cam_look_at = new THREE.Vector3(0.0,0.0,0.0); // ponto para o qual a câmera aponta.
let cam_up = new THREE.Vector3(0.0,1.0,0.0);      // vetor Up da câmera.

/******************************************************************************
* Matriz View (visualização): Esp. Universo --> Esp. Câmera
*****************************************************************************/

const d_vector = new THREE.Vector3();
let Zcam = new THREE.Vector3();
let Xcam = new THREE.Vector3();
let Ycam = new THREE.Vector3();

d_vector.subVectors(cam_look_at, cam_pos);
Zcam = d_vector.normalize().clone().negate(); // - d/|d|
Xcam = Xcam.crossVectors(cam_up, Zcam).normalize(); 
Ycam = Ycam.crossVectors(Zcam, Xcam).normalize();
// Construir 'm_bt', a inversa da matriz de base da câmera.


let m_bt = new THREE.Matrix4();

m_bt.set(Xcam.x, Xcam.y, Xcam.z, 0.0,
Ycam.x, Ycam.y, Ycam.z, 0.0,
Zcam.x, Zcam.y, Zcam.z, 0.0,
0.0, 0.0, 0.0, 1.0);


// Construir a matriz 'm_t' de translação para tratar os casos em que as
// origens do espaço do universo e da câmera não coincidem.

let m_t = new THREE.Matrix4();

m_t.set(1.0, 0.0, 0.0, -cam_pos.x,
0.0, 1.0, 0.0, -cam_pos.y,
0.0, 0.0, 1.0, -cam_pos.z,
0.0, 0.0, 0.0, 1.0);

// Constrói a matriz de visualização 'm_view' como o produto
//  de 'm_bt' e 'm_t'.
let m_view = m_bt.clone().multiply(m_t);

for (let i = 0; i < 8; ++i)
vertices[i].applyMatrix4(m_view);


/*******************************************************************************
* Matriz de Projecao: Esp. Câmera --> Esp. Recorte
*****************************************************************************/

let m_projection = new THREE.Matrix4();
let D = 1.0;

m_projection.set(1.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 1.0, D,
     0.0, 0.0, -1.0/D, 1.0);

for (let i = 0; i < 8; ++i)
vertices[i].applyMatrix4(m_projection);

/******************************************************************************
* Homogeneizacao (divisao por W): 
*****************************************************************************/

for(let i = 0; i < 8; i++){
vertices[i].divideScalar(vertices[i].w);
}
/******************************************************************************
* Matriz Viewport: Esp. Canônico --> Esp. Tela
*****************************************************************************/

let m_viewport = new THREE.Matrix4();
let matrix_translation = new THREE.Matrix4();
let matrix_scale = new THREE.Matrix4();

matrix_scale.set( 64, 0.0, 0.0, 64,
      0.0, 64, 0.0, 64,
      0.0, 0.0, 1.0, 0.0,
      0.0, 0.0, 0.0, 1.0);

matrix_translation.set(1.0, 0.0, 0.0, 0.0,
           0.0, 1.0, 0.0, 0.0,
           0.0, 0.0, 1.0, 0.0,
           0.0, 0.0, 0.0, 1.0);

m_viewport.set(1.0, 0.0, 0.0, 0.0,
   0.0, 1.0, 0.0, 0.0,
   0.0, 0.0, 1.0, 0.0,
   0.0, 0.0, 0.0, 1.0);

m_viewport = matrix_scale.clone().multiply(matrix_translation);

for (let i = 0; i < 8; ++i)
vertices[i].applyMatrix4(m_viewport);

/******************************************************************************
* Rasterização
*****************************************************************************/
/*A principio não precisa implementar completamente, 
basta anexar link da atividade 1 aqui na aba js e chamar a função MidPointLineAlgorithm, 
porém é  preciso alterar algumas coisas na função MidPointLineAlgorithm, adaptando para essa atividade.*/
for(let i = 0; i < edges.length; ++i){ 
MidPointLineAlgorithm(vertices[edges[i][0]].x, 
            vertices[edges[i][0]].y, 
            vertices[edges[i][1]].x, 
            vertices[edges[i][1]].y, 
                [255,0,0]); 
}

