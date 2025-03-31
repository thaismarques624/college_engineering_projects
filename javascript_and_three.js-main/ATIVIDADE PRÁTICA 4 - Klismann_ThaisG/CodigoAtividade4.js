let image = new Image();
//image.src = src_gate; // Exemplo do professor utilizado no trabalho
//image.src = src_checkerboard; // Exemplo do professor utilizado no trabalho
//image.src = src_yourname;
//image.src = src_waves;
//image.src = src_yingyang;
//image.src = src_mine1; //Descartadas
//image.src = src_mine2; //Descartadas
image.src = src_minecraft;


texture = new THREE.Texture(image);

//Primeira comparação nearest neighbor.
/*
image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.NearestFilter;
    texture.minFilter = THREE.NearestFilter;
    texture.anisotropy = 1;
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};
*/
//Segunda comparação LinearFilter
/*
image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.LinearFilter
    texture.minFilter = THREE.LinearFilter
    texture.anisotropy = 1;
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};
*/
//Terceira comparação NearestMipmapNearestFilter --> aqui começa a Mag. Min simultânea.
/*
image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.NearestFilter;
    texture.minFilter = THREE.NearestMipmapNearestFilter;
    texture.anisotropy = 1;
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};
*/

//Quarta comparação NearestMipmapLinearFilter
/*
image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.NearestFilter; 
    texture.minFilter = THREE.NearestMipmapLinearFilter
    texture.anisotropy = 1;
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};
*/
//Quinta comparação LinearMipmapNearestFilter
/*
image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.LinearFilter; 
    texture.minFilter = THREE.LinearMipmapNearestFilter
    texture.anisotropy = 1;
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};
*/

//Sexta comparação LinearMipmapLinearFilter
/*
image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.LinearFilter; 
    texture.minFilter = THREE.LinearMipmapLinearFilter
    texture.anisotropy = 1;
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};
*/
// Sétima comparação filtragem anisotrópica no caso de  minificação

image.onload = function() {
    texture.needsUpdate = true;
    texture.magFilter = THREE.LinearFilter; 
    texture.minFilter = THREE.LinearMipmapLinearFilter
    texture.anisotropy = 16; //também testa com 32 e 64(amostras ao longo do maior eixo, quanto mais subir mais fica lento e nitido)
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
};

let scene = new THREE.Scene();

let camera = new THREE.PerspectiveCamera(75, window.innerWidth/window.innerHeight, 0.01, 100);
camera.position.z = 1.3;

scene.add(camera);

let renderer = new THREE.WebGLRenderer({canvas: document.getElementById("canvas")});
renderer.setPixelRatio( window.devicePixelRatio );
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild(renderer.domElement);

let controls = new THREE.OrbitControls(camera, renderer.domElement);

let geometry = new THREE.BoxGeometry(1, 1, 1);

//----------------------------------------------------------------------------
// Criação das fontes de luz pontuais (uma, mais clara, à frente e outra, 
// mais escura, atrás do cubo).
//----------------------------------------------------------------------------
var point_light = new THREE.PointLight(0xffffff);
point_light.position.set(-10, 15, 20);
scene.add(point_light);

var point_light = new THREE.PointLight(0x666666);
point_light.position.set(10, -10, -10);
scene.add(point_light);

//----------------------------------------------------------------------------
// Criação do material difuso. A textura define a reflectância difusa (k_d) 
// do material.
//----------------------------------------------------------------------------
let material = new THREE.MeshLambertMaterial({ //usando a iluminação de phong, as faces ficam mais visiveis, inclusive nas que estão atrás.
    map: texture
});


var object_mesh = new THREE.Mesh(geometry, material);
scene.add(object_mesh);

function render() {
  requestAnimationFrame(render);
  renderer.render(scene, camera);   
}

render();

//Também disponivel em: https://codepen.io/gabriellymarques02/pen/bGqQOdJ?editors=0011