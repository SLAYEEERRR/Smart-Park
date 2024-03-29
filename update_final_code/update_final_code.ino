#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#ifndef STASSID
#define STASSID "realme C25Y"
#define STAPSK "abhi1234"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

Servo myservo;

int entrance_ir_sensor = D1;
int exit_ir_sensor = D2;
int parking_slot_ir_sensor1 = D3;
int parking_slot_ir_sensor2 = D6;
int parking_slot_ir_sensor3 = D7;

int parkedCount1 = 0;
int parkedCount2 = 0;
int parkedCount3 = 0;

// // Function to check if a parking slot is occupied or not
// int isSlotOccupied(int sensorPin) {
//   if (digitalRead(sensorPin) == LOW) {
//     return 1;  // Slot is occupied
//   } else {
//     return 0;  // Slot is empty
//   }
// }

void setup() {


  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //successful connection
  Serial.println("");
  Serial.println("Connected to WiFi");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);


  // Initialize server routes
  // Serve the welcome page



  server.on("/", HTTP_GET, handleRoot);
  server.on("/status", HTTP_GET, handleStatus);

  // Start the server
  server.begin();

  pinMode(entrance_ir_sensor, INPUT);
  pinMode(exit_ir_sensor, INPUT);
  pinMode(parking_slot_ir_sensor1, INPUT);
  // pinMode(parking_slot_ir_sensor2, INPUT);
  // pinMode(parking_slot_ir_sensor3, INPUT);

  myservo.attach(D0);
}

void loop() {
  server.handleClient();

  // gates opeining
  if (digitalRead(entrance_ir_sensor) == LOW || digitalRead(exit_ir_sensor) == LOW) {
    myservo.write(90);
    delay(2000);
  } else if (digitalRead(entrance_ir_sensor) == HIGH || digitalRead(exit_ir_sensor) == HIGH) {
    myservo.write(0);
  }
  // Update each variable based on the value of the corresponding IR sensor
parkedCount1 = (digitalRead(parking_slot_ir_sensor1) == LOW) ? 0 : 1;
// parkedCount2 = (digitalRead(parking_slot_ir_sensor2) == LOW) ? 0 : 1;
// parkedCount3 = (digitalRead(parking_slot_ir_sensor3) == LOW) ? 0 : 1;
}


void handleRoot() {
  server.send(200, "text/html", generateHtml());
}

void handleStatus() {
  // Return the parkedCount1 as plain text
  server.send(200, "text/plain", String(parkedCount1));
  server.send(200, "text/plain", String(parkedCount2));
  // server.send(200, "text/plain", String(parkedCount3));
}


String generateHtml() {
  // Generate the HTML page with JavaScript for dynamic updates
  String html = R"(
    <!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>VIT Smart Park</title>
</head>
<style>
  *{
    margin: 0 0;
    padding: 0 0;
  }
  body {
    width: 100%;
    height: 100%;
    position: fixed;
    background-color: #34495e;
    margin: 0 auto;
    
  }
  .rows{
    margin: 4%;
    display: flex;
    gap: 4%;
    
  }

  .content {
    position: absolute;
    top: 26%;
    left: 50%;
    transform: translate(-50%, -50%);
    height: 260px;
    overflow: hidden;
    font-family: "Lato", sans-serif;
    font-size: 35px;
    line-height: 40px;
    color: #ecf0f1;
  }

  .content__container {
    font-weight: 600;
    overflow: hidden;
    height: 40px;
    padding: 0 40px;
  }

  .content__container:before {
    content: "[";
    left: 0;
  }

  .content__container:after {
    content: "]";
    position: absolute;
    right: 0;
  }
/* brackets */
  .content__container:after,
  .content__container:before {
    position: absolute;
    top: 0;
    color: #16a085;
    font-size: 42px;
    line-height: 40px;
    -webkit-animation-name: opacity;
    -webkit-animation-duration: 2s;
    -webkit-animation-iteration-count: infinite;
    animation-name: opacity;
    animation-duration: 2s;
    animation-iteration-count: infinite;
  }

  .content__container__text {
    display: inline;
    float: left;
    margin: 0;
  }

  .content__container__list {
    margin-top: 0;
    padding-left: 110px;
    text-align: left;
    list-style: none;
    -webkit-animation-name: change;
    -webkit-animation-duration: 10s;
    -webkit-animation-iteration-count: infinite;
    animation-name: change;
    animation-duration: 10s;
    animation-iteration-count: infinite;
  }

  .content__container__list__item {
    line-height: 40px;
    margin: 0;
  }

  @-webkit-keyframes opacity {

    0%,
    100% {
      opacity: 0;
    }

    50% {
      opacity: 1;
    }
  }

  @-webkit-keyframes change {

    0%,
    12.66%,
    100% {
      transform: translate3d(0, 0, 0);
    }

    16.66%,
    29.32% {
      transform: translate3d(0, -25%, 0);
    }

    33.32%,
    45.98% {
      transform: translate3d(0, -50%, 0);
    }

    49.98%,
    62.64% {
      transform: translate3d(0, -75%, 0);
    }

    66.64%,
    79.3% {
      transform: translate3d(0, -50%, 0);
    }

    83.3%,
    95.96% {
      transform: translate3d(0, -25%, 0);
    }
  }

  @keyframes opacity {

    0%,
    100% {
      opacity: 0;
    }

    50% {
      opacity: 1;
    }
  }

  @keyframes change {

    0%,
    12.66%,
    100% {
      transform: translate3d(0, 0, 0);
    }

    16.66%,
    29.32% {
      transform: translate3d(0, -25%, 0);
    }

    33.32%,
    45.98% {
      transform: translate3d(0, -50%, 0);
    }

    49.98%,
    62.64% {
      transform: translate3d(0, -75%, 0);
    }

    66.64%,
    79.3% {
      transform: translate3d(0, -50%, 0);
    }

    83.3%,
    95.96% {
      transform: translate3d(0, -25%, 0);
    }
  }

  /* speedy truck and slot*/

  .slot {
    /* justify-content: center; */
    /* margin: 10;
    padding: auto; */
  }

  .first {
    flex: 1;
  border: 1px solid #000;
  padding: 10px;
  text-align: center;
    justify-content: center;
    width: 650px;
    height: 6%;
    background: #009688;
    overflow: hidden;
    font-family: "Open Sans", sans-serif;
    margin-top: 12%;
     
    border-radius: 20px;
  }

  #data1,#data2,#data3 {
    font-family: "Lato", sans-serif;
    font-size: 35px;
    line-height: 40px;
    margin: 0;
  }

  /* body { 
  background: #009688;
  overflow: hidden;
  font-family: 'Open Sans', sans-serif;
} */
  .loop-wrapper {
    margin: 0 auto;
    position: relative;
    display: block;
    width: 600px;
    height: 250px;
    overflow: hidden;
    border-bottom: 3px solid #fff;
    color: #fff;
  }

  .mountain {
    position: absolute;
    right: -900px;
    bottom: -20px;
    width: 2px;
    height: 2px;
    box-shadow: 0 0 0 50px #4db6ac, 60px 50px 0 70px #4db6ac,
      90px 90px 0 50px #4db6ac, 250px 250px 0 50px #4db6ac,
      290px 320px 0 50px #4db6ac, 320px 400px 0 50px #4db6ac;
    transform: rotate(130deg);
    animation: mtn 20s linear infinite;
  }

  .hill {
    position: absolute;
    right: -900px;
    bottom: -50px;
    width: 400px;
    border-radius: 50%;
    height: 20px;
    box-shadow: 0 0 0 50px #4db6ac, -20px 0 0 20px #4db6ac,
      -90px 0 0 50px #4db6ac, 250px 0 0 50px #4db6ac, 290px 0 0 50px #4db6ac,
      620px 0 0 50px #4db6ac;
    animation: hill 4s 2s linear infinite;
  }

  .tree,
  .tree:nth-child(2),
  .tree:nth-child(3) {
    position: absolute;
    height: 100px;
    width: 35px;
    bottom: 0;
    background: url(https://s3-us-west-2.amazonaws.com/s.cdpn.io/130015/tree.svg) no-repeat;
  }

  .rock {
    margin-top: -17%;
    height: 2%;
    width: 2%;
    bottom: -2px;
    border-radius: 20px;
    position: absolute;
    background: #ddd;
  }

  .truck,
  .wheels {
    transition: all ease;
    width: 85px;
    margin-right: -60px;
    bottom: 0px;
    right: 50%;
    position: absolute;
    background: #eee;
  }

  .truck {
    background: url(https://s3-us-west-2.amazonaws.com/s.cdpn.io/130015/truck.svg) no-repeat;
    background-size: contain;
    height: 60px;
  }

  .truck:before {
    content: " ";
    position: absolute;
    width: 25px;
    box-shadow: -30px 28px 0 1.5px #fff, -35px 18px 0 1.5px #fff;
  }

  .wheels {
    background: url(https://s3-us-west-2.amazonaws.com/s.cdpn.io/130015/wheels.svg) no-repeat;
    height: 15px;
    margin-bottom: 0;
  }

  .tree {
    animation: tree 3s 0s linear infinite;
  }

  .tree:nth-child(2) {
    animation: tree2 2s 0.15s linear infinite;
  }

  .tree:nth-child(3) {
    animation: tree3 8s 0.05s linear infinite;
  }

  .rock {
    animation: rock 4s -0.53s linear infinite;
  }

  .truck {
    animation: truck 4s 0.08s ease infinite;
  }

  .wheels {
    animation: truck 4s 0.001s ease infinite;
  }

  .truck:before {
    animation: wind 1.5s 0s ease infinite;
  }

  @keyframes tree {
    0% {
      transform: translate(1350px);
    }

    50% {}

    100% {
      transform: translate(-50px);
    }
  }

  @keyframes tree2 {
    0% {
      transform: translate(650px);
    }

    50% {}

    100% {
      transform: translate(-50px);
    }
  }

  @keyframes tree3 {
    0% {
      transform: translate(2750px);
    }

    50% {}

    100% {
      transform: translate(-50px);
    }
  }

  @keyframes rock {
    0% {
      right: -200px;
    }

    100% {
      right: 2000px;
    }
  }

  @keyframes truck {
    0% {}

    6% {
      transform: translateY(0px);
    }

    7% {
      transform: translateY(-6px);
    }

    9% {
      transform: translateY(0px);
    }

    10% {
      transform: translateY(-1px);
    }

    11% {
      transform: translateY(0px);
    }

    100% {}
  }

  @keyframes wind {
    0% {}

    50% {
      transform: translateY(3px);
    }

    100% {}
  }

  @keyframes mtn {
    100% {
      transform: translateX(-2000px) rotate(130deg);
    }
  }

  @keyframes hill {
    100% {
      transform: translateX(-2000px);
    }
  }
</style>

<body>
    <div class="content">
        <div class="content__container">
            <p class="content__container__text">VIT</p>

            <ul class="content__container__list">
                <li class="content__container__list__item">Park</li>
                <li class="content__container__list__item">Spark</li>
            </ul>
        </div>
    </div>

    <div class="slots">
        <div class="rows">
            <!-- First parking slot -->
            <div class="first">
                <center>
                    <p id="data1">Spot A</p>
                </center>
                <div class="loop-wrapper">
                  <div class="mountain"></div>
                  <div class="hill"></div>
                  <div class="tree"></div>
                  <div class="tree"></div>
                  <div class="tree"></div>
                  <div class="rock"></div>
                  <div class="truck"></div>
                  <div class="wheels"></div>
                </div>
            </div>

            <!-- Second parking slot -->
            <div class="first">
                <center>
                    <p id="data2">Spot B</p>
                </center>
                <div class="loop-wrapper">
                  <div class="mountain"></div>
                  <div class="hill"></div>
                  <div class="tree"></div>
                  <div class="tree"></div>
                  <div class="tree"></div>
                  <div class="rock"></div>
                  <div class="truck"></div>
                  <div class="wheels"></div>
                </div>
            </div>

            <!-- Third parking slot -->
            <div class="first">
                <center>
                    <p id="data3">Spot C</p>
                </center>
                <div class="loop-wrapper">
                  <div class="mountain"></div>
                  <div class="hill"></div>
                  <div class="tree"></div>
                  <div class="tree"></div>
                  <div class="tree"></div>
                  <div class="rock"></div>
                  <div class="truck"></div>
                  <div class="wheels"></div>
                </div>
            </div>
        </div>
    </div>

    <script>
  function updateStatus(slotNumber, elementId) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
if (this.readyState == 4 && this.status == 200) {
        var sensorData = this.responseText;
        var status =
          sensorData === "0"
            ? "Parking slot is full!"
            : "Parking slot is empty!";
        document.getElementById(elementId).innerHTML = status;
      }
    };
    xhttp.open("GET", "/status", true);
    xhttp.send();
  }

  // Call updateStatus for each parking slot
  setInterval(function () {
    updateStatus(1, "data1");
    // updateStatus(2, "data2");
    // updateStatus(3, "data3");
  }, 2000);

  // Initialize status for each parking slot
  updateStatus(1, "data1");
  // updateStatus(2, "data2");
  // updateStatus(3, "data3");
</script>

    // <script>
    //     function updateStatus(slotNumber) {
    //         var xhttp = new XMLHttpRequest();
    //         xhttp.onreadystatechange = function () {
    //             if (this.readyState == 4 && this.status == 200) {
    //                 var sensorData = this.responseText;
    //                 var status =
    //                     sensorData === "0"
    //                         ? "Parking slot is full!"
    //                         : "Parking slot is empty!";
    //                 document.getElementById("data" + slotNumber).innerHTML = status;
    //             }
    //         };
    //         xhttp.open("GET", "/status", true);
    //         xhttp.send();
    //     }

    //     // Call updateStatus for each parking slot
    //     setInterval(function () {
    //         updateStatus(1);
    //         updateStatus(2);
    //         updateStatus(3);
    //     }, 2000);

    //     // Initialize status for each parking slot
    //     updateStatus(1);
    //     updateStatus(2);
    //     updateStatus(3);
    // </script>
</body>
</html>
  )";

  return html;
}
