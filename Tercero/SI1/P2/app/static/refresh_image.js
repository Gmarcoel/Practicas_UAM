var element = document.getElementById('poster');

element.onclick = refreshImage(element, "https://loremflickr.com/300/500/movie%20poster") {

function refreshImage(imgElement, imgURL){    
    // create a new timestamp 
    var timestamp = new Date().getTime();  
  
    var el = document.getElementById(imgElement);  
  
    var queryString = "?t=" + timestamp;    
   
    el.src = imgURL + queryString;    
}    

