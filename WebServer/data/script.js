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