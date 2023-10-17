
function abrirMenuLateral() {
    document.getElementById("miMenuLateral").style.width = "500px";
  }

  function cerrarMenuLateral() {
    document.getElementById("miMenuLateral").style.width = "0px";
  }


$(document).ready(function(){
setInterval(fetchdata,5000);
});