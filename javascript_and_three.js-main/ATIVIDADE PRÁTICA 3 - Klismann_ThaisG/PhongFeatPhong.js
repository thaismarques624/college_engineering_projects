// Criação do objeto Three.js que armazenará os dados da cena.
let scene = new THREE.Scene();

// Definição da câmera do Three.js
let camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 25;

// A câmera é adicionada a cena.
scene.add(camera);

// Criação do objeto Three.js responsável por realizar o rendering.
let renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Criação do objeto de controle (interação) da câmera.
let controls = new THREE.OrbitControls(camera, renderer.domElement);

//----------------------------------------------------------------------------
// 'geometry' : Variável que contém a geometria (informação sobre vértices
//     e arestas) do objeto a ser renderizado (um torus, neste caso). É importante 
//     observar que, de acordo com o Three.js, a geometria de um objeto não contém
//     ainda a informação sobre o seu material.
//----------------------------------------------------------------------------
let geometry = new THREE.TorusGeometry(10, 3, 16, 25);

//----------------------------------------------------------------------------
// Variáveis do tipo "uniform", enviadas pela CPU aos shaders :
//
// * 'Ip_position' : posição da fonte de luz pontual no Espaço do Universo.
// * 'Ip_ambient_color' : cor do componente ambiente da fonte de luz pontual.
// * 'Ip_diffuse_color' : cor do componente difuso da fonte de luz pontual.
// * 'k_a' : coeficiente de reflectância ambiente do objeto.
// * 'k_d' : coeficiente de reflectância difusa do objeto.
// * 'k_s' : coeficiente de reflectância especular do objeto.
//----------------------------------------------------------------------------
let rendering_uniforms = {
    Ip_position: {type: 'vec3', value: new THREE.Vector3(-20, 10, 10)},
    Ip_ambient_color: {type: 'vec3', value: new THREE.Color(0.3, 0.3, 0.3)},
    Ip_diffuse_color: {type: 'vec3', value: new THREE.Color(0.7, 0.7, 0.7)},
    k_a: {type: 'vec3', value: new THREE.Color(0.25, 0.25, 0.85)},
    k_d: {type: 'vec3', value: new THREE.Color(0.25, 0.25, 0.85)},
    k_s: {type: 'vec3', value: new THREE.Color(1, 1, 1)},
    camera_position : {type: 'vec3', value: new THREE.Vector3(0, 0, 25)}
}

//----------------------------------------------------------------------------
// Criação do material na forma de um Vertex Shader e um Fragment Shader customizados.
// Os shaders receberão valores da CPU (i.e. variáveis do tipo 'uniform') por meio da
// variável 'rendering_uniforms'.
//----------------------------------------------------------------------------
let material = new THREE.ShaderMaterial({
    uniforms: rendering_uniforms,
    vertexShader:'',
    fragmentShader: ''
});

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------
material.vertexShader = `
    // 'uniforms' contendo informações sobre a fonte de luz pontual.
    
    uniform vec3 Ip_position;

    // Variáveis que são passadas do vertex shader para o fragment shader.
    
    varying vec3 N_cam_spc;
    varying vec3 L_cam_spc;
    varying vec3 R_cam_spc;
    varying vec3 V_cam_spc;
    
    uniform vec3 camera_position;

    // Programa principal do Vertex Shader.

    void main() {
    
        // 'modelViewMatrix' : variável de sistema que contém a matriz ModelView (4x4).
        // 'Ip_pos_cam_spc' : variável que armazenará a posição da fonte de luz no Espaço da Câmera.
        
        vec4 Ip_pos_cam_spc = modelViewMatrix * vec4(Ip_position, 1.0);

        // 'position' : variável de sistema que contém a posição do vértice (vec3) no espaço do objeto.
        // 'P_cam_spc' : variável que contém o vértice (i.e. 'position') transformado para o Espaço de Câmera.
        //     Observe que 'position' é um vetor 3D que precisou ser levado para o espaço homogêneo 4D 
        //     (i.e., acrescentando-se uma coordenada adicional w = 1.0) para poder ser multiplicado pela
        //     matriz 'modelViewMatrix' (que é 4x4).
        
        vec4 P_cam_spc = modelViewMatrix * vec4(position, 1.0);

        // 'normal' : variável de sistema que contém o vetor normal do vértice (vec3) no espaço do objeto.
        // 'normalMatrix' : variável de sistema que contém a matriz de normais (3x3) gerada a partir da matriz 'modelViewMatrix'.
        
        N_cam_spc = normalize(normalMatrix * normal);

        // 'normalize()' : função do sistema que retorna o vetor de entrada normalizado (i.e. com comprimento = 1).
        // 'L_cam_spc' : variável que contém o vetor unitário, no Espaço de Câmera, referente à fonte de luz.
        
        L_cam_spc = normalize(Ip_pos_cam_spc.xyz - P_cam_spc.xyz);

        // 'reflect()' : função do sistema que retorna 'R_cam_spc', isto é, o vetor 'L_cam_spc' refletido 
        //     em relação o vetor 'N_cam_spc'.
        
        R_cam_spc = reflect(L_cam_spc, N_cam_spc);

        // 'V_cam_spc': representa o vetor de visualização do observador. è um vetor que aponta da
        // câmera para o vértice sob análise.
        
        V_cam_spc = normalize(position - camera_position);

        // 'gl_Position' : variável de sistema que conterá a posição final do vértice transformado pelo Vertex Shader.
        
        gl_Position = projectionMatrix * P_cam_spc;
    }
    `;

//----------------------------------------------------------------------------
// Fragment Shader
//----------------------------------------------------------------------------
material.fragmentShader = `
    // 'uniforms' contendo informações sobre a fonte de luz pontual.
    
    uniform vec3 Ip_ambient_color;
    uniform vec3 Ip_diffuse_color;

    // 'uniforms' contendo informações sobre as reflectâncias do objeto.
    
    uniform vec3 k_a;
    uniform vec3 k_d;
    uniform vec3 k_s;

    // Variáveis calculadas no vertex shader.
    
    varying vec3 N_cam_spc;
    varying vec3 L_cam_spc;
    varying vec3 R_cam_spc;
    varying vec3 V_cam_spc;

    // Programa principal do Fragment Shader.

    void main() {
        
        ///////////////////////////////////////////////////////////////////////////////
        // Modelos de iluminação com Phong Shading (interpolação por fragmento).
        
        // Como o vertex shader calcula os vetores para cada vértice e esses vetores são
        // interpolados no fragment shader, é necessário refazer a normalização dos mesmos.
        
        vec3 N_cam_spc = normalize(N_cam_spc);
        vec3 L_cam_spc = normalize(L_cam_spc);
        vec3 R_cam_spc = normalize(R_cam_spc);
        vec3 V_cam_spc = normalize(V_cam_spc);
        
        // Cálculo de iluminação de Phong.
        
        vec3 amb_term = Ip_ambient_color * k_a;
        vec3 diff_term = Ip_diffuse_color * k_d * max(0.0, dot(L_cam_spc, N_cam_spc));
        vec3 spec_term = Ip_diffuse_color * k_s * pow( max(0.0, dot(R_cam_spc, V_cam_spc)), 16.0 );
        
        vec3 Iphong = amb_term + diff_term + spec_term;
        ///////////////////////////////////////////////////////////////////////////////
        
        vec4 I = vec4(Iphong, 1);
    
        // 'gl_FragColor' : variável de sistema que conterá a cor final do fragmento calculada pelo Fragment Shader.
        
        gl_FragColor = I;
    }
    `;

//----------------------------------------------------------------------------
// 'object_mesh' : De acordo com o Three.js, um 'mesh' é a geometria acrescida do material.
//----------------------------------------------------------------------------
var object_mesh = new THREE.Mesh(geometry, material);
scene.add(object_mesh);

//----------------------------------------------------------------------------
// 'render()' : Função que realiza o rendering da cena a cada frame.
//----------------------------------------------------------------------------
function render() {
  requestAnimationFrame(render);
  renderer.render(scene, camera);
}

// Chamada da função de rendering.
render();
