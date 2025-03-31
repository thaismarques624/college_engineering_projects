function getRandom() {
    return Math.floor(Math.random() * 100)
}
                                                //Essa function ta gerando 10 valores aleatorios entre 0 e 100.
let array = [];
for (let i = 0 ; i < 10 ; i++){
  array.push(getRandom());
}

//console.log(array);
document.write("Array: "+array); // Aqui para exibir os valores randomicos antes da ordenação
document.write("<br>");

function swap(array, leftIndex, rightIndex){ //swap é uma function para trocar os valores.
    var temp = array[leftIndex];
    array[leftIndex] = array[rightIndex];
    array[rightIndex] = temp;
}

function partition(array, left, right){
    var pivo = array[Math.floor((right + left)/2)],
    i=left,
    j=right;
    while(i <= j){
        while(array[i]<pivo){               //partição ta escolhendo como pivo o elemento do meio
            i++;                            //(comprimento do array dividido por 2). 
        }
        while(array[j]>pivo){
            j--;
        }
        if(i<=j){
            swap(array, i, j);
            i++;
            j--;
        }
    }
    return i;
}

function quickSort(array, left, right){
    var index;
    if(array.length>1){
        index = partition(array, left, right);
        if(left < index - 1){
            quickSort(array,left, index-1);
        }
        if(index < right){
            quickSort(array, index, right);
        }
    }
    return array;
}

var sortedArray = quickSort(array, 0, array.length - 1);
document.write( "QuickSort: "+sortedArray);

