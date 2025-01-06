
const endPoint = "http://10.1.5.127";

function getDapurLed() {
  fetch(endPoint + "/dapur", {
    method: "GET"
  }).then (response => response.text()).then(result => {
    if (result == "Dapur On") {

    }
  })
}

function getTamuLed() {
  fetch(endPoint + "/tamu", {
    method: "GET"
  }).then (response => response.text()).then(result => {
    if (result == "Dapur On") {

    }
  })
}

function getMakanLed() {
  fetch(endPoint + "/makan", {
    method: "GET"
  }).then (response => response.text()).then(result => {
    if (result == "Dapur On") {

    }
  })
}

function setDapurLed() {
  fetch(endPoint + "/dapur", {
    method: "POST"
  }).then (response => response.text()).then(() => location.reload());
}

function setTamuLed() {
  fetch(endPoint + "/dapur", {
    method: "POST"
  }).then (response => response.text()).then(() => location.reload());
}

function setMakanLed() {
  fetch(endPoint + "/dapur", {
    method: "POST"
  }).then (response => response.text()).then(() => location.reload());
}