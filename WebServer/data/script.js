var redState = false
var greenState = false
var blueState = false

function toggleColor(id) {
    const url = `/toggle?state=${id}`;

    fetch(url)
        .then(res => res.text)
        .catch(error => {console.error('Error caught:',error.message)})
    getData();
}

function setColors() {
    var btn_red = document.getElementById("btnred");
    var btn_green = document.getElementById("btngreen");
    var btn_blue = document.getElementById("btnblue");
    if (redState) btn_red.className = "button red onred"; else btn_red.className = "button red OFF";
    if (greenState) btn_green.className = "button green ongreen"; else btn_green.className = "button green OFF";
    if (blueState) btn_blue.className = "button blue onblue"; else btn_blue.className = "button blue OFF";
}

function getData() {
    const url = `/data`;
    fetch(url)
        .then(res => res.json())
        .then(data => {
            useData(data);})
        .catch(error => {console.error('Error caught:',error.message)})
}

function useData(data) {
    document.getElementById("temperature").innerText = data.temperature;
    document.getElementById("humidity").innerText = data.humidity;
    redState = data.red;
    greenState = data.green;
    blueState = data.blue;
    setColors();
}

getData();
setInterval(getData, 1000);

function creatBG() {
    const container = document.getElementById('bg-container');
    const numberOfShapes = 500;
    const speed_range = 20;
    for (let i = 0; i < numberOfShapes; i++) {
    const shape = document.createElement('div');
    shape.classList.add('layer');
    const size = Math.floor(Math.random() * 300) + 100; // Size between 100px and 400px
    const top = Math.random() * 100; // Random top %
    const left = Math.random() * 100; // Random left %
    const speed = (Math.random() * speed_range) - speed_range/2; // Random speed between -4 and 4
    const r = Math.floor(Math.random() * 255);
    const g = Math.floor(Math.random() * 255);
    const b = Math.floor(Math.random() * 255);
    shape.style.width = `${size}px`;
    shape.style.height = `${size}px`;
    shape.style.top = `${top}%`;
    shape.style.left = `${left}%`;
    shape.style.background = `radial-gradient(circle, rgba(${r},${g},${b},0.3) 0%, rgba(0,0,0,0) 70%)`;
    shape.dataset.speed = speed;
    container.appendChild(shape);
    }
}
document.addEventListener("DOMContentLoaded", creatBG);
document.addEventListener("mousemove", (e) => {
  const layers = document.querySelectorAll(".layer");
  const x = (window.innerWidth / 2 - e.pageX) / 50;
  const y = (window.innerHeight / 2 - e.pageY) / 50;

  layers.forEach((layer) => {
    const speed = layer.dataset.speed;
    layer.style.transform = `translateX(${x * speed}px) translateY(${y * speed}px)`;
  });
});