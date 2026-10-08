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
    if (redState) btn_red.innerText = "red on "; else btn_red.innerText = "red off";
    if (greenState) btn_green.innerText = "green on "; else btn_green.innerText = "green off";
    if (blueState) btn_blue.innerText = "blue on "; else btn_blue.innerText = "blue off";
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