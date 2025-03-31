function getRandom() {
    return Math.floor(Math.random() * 10 + 1)
}

let array = [];
var somapar = 0;
for (let i = 0 ; i < 10 ; i++){
  array.push(getRandom());
  if(array[i] % 2 === 0){
    somapar++;
  }
}
document.write("Array: "+array);
document.write("<br>");
document.write("Total de números pares é: "+somapar);
//console.log(array);
//console.log("Total de números pares é: "+somapar);