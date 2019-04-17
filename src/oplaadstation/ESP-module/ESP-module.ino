#include <ESP8266WiFi.h>
//#include <SoftwareSerial.h>

const char* ssid = "iottest";//type your ssid
const char* password = "testtest";//type your password


WiFiServer server(80);


bool isFree = true;
char newData[2] = "";
char oldData[2] = "";




//SoftwareSerial mySerial(0, 2); //RX TX
void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println("begin softwareserial");
  //mySerial.begin(9600);
  Serial.println("SoftSerial started");
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  serialEvent();

  if (strcmp(newData, oldData)) {
    Serial.println(newData);

    connect();
    for (int i = 0; i < 2; i++) {
      oldData[i] = newData[i];
    }
  }

}

//------------------------------------------- SERIAL EVENT


void serialEvent() {
  int i = 0;
  while (Serial.available() && i < 2) {
    char c = (char)Serial.read();
    newData[i] = c;
    i++;
  }

}

void connect() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Refresh: 2");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html lang=\"en\">");

  client.println("<style>");
  client.println("* {margin: 0;padding: 0;font-family: 'Source Sans Pro', sans-serif;outline: none!important;} a {text-decoration: none!important;} body { overflow-x: hidden; }        ul { list-style: none; margin: 0px;}        p {font-size: 16px;line-height: 26px;letter-spacing: 0.25px; font-weight: 300; }        .section-heading { text-align: center; margin-top: 80px; margin-bottom: 60px;}        .section-heading h4 { margin-top: 0px; font-size: 28px; text-transform: uppercase;font-weight: 300; color: #121212; }        .section-heading p {color: #7a7a7a; padding: 0px 25%; }        .banner { background-image: url(https://d2v9y0dukr6mq2.cloudfront.net/video/thumbnail/cW5lDBG/videoblocks-abstract-technology-futuristic-network-animation-on-a-blue-background-seamless-loop_hbdnvlv-w_thumbnail-full08.png); background-repeat: no-repeat; background-size: cover; background-position: center center;} .banner-content { text-align: center; padding: 280px 0px 200px 0px;} .banner-content h6 { font-size: 18px; color: #fff;font-weight: 700; text-transform: uppercase; letter-spacing: 2px;margin-bottom: 5px;}.banner-content h2 {font-size: 80px; font-weight: 700;text-transform: uppercase; color: #fff;letter-spacing: 2px; margin-top: 0px; margin-bottom: 30px; }.banner-content ul { padding: 0; margin: 0;list-style: none;}.banner-content ul li {display: inline-block;margin: 10px; }.what-we-do { background-color: #fff;padding-bottom: 80px; } .what-we-do .tabs li a { text-decoration: none; color: #121212;}.what-we-do .active .list-item { background-color: #7CB342!important; color: #fff!important;}.what-we-do .inactive .list-item { background-color: #E65100!important; color: #fff!important;}.what-we-do .list-item {background-color: #f4f4f4; text-align: center;padding: 40px 0px;margin: 15px 0px; transition: all 0.5s;}.what-we-do .list-item .icon {border-radius: 50%; margin: auto;display: inline-block;text-align: center;vertical-align: middle;background-color: transparent;}.what-we-do .list-item h4 { margin-top: 20px;margin-bottom: 0px;font-size: 17px;font-weight: 700;text-transform: uppercase;}footer {background-color: #363e50; padding: 0px 0px;text-align: center;}footer p { font-size: 14px;text-transform: uppercase;color: #fff;margin-bottom: 0px;padding: 75px 0px;}footer .back-to-top a { text-align: center;background-color: #46bae2; display: inline-block;width: 100%;padding: 60px 0px; color: #fff; font-size: 15px; text-transform: uppercase;font-weight: 700;text-decoration: none;letter-spacing: 1px;}footer .back-to-top i {display: block; font-size: 36px;}");
  client.println("</style>");

  client.println("<meta charset=\"UTF-8\">");
  client.println("<title>WiPo</title>");

  client.println("</head>");
  client.println("<body>");

  client.println("<div class=\"banner\">");
  client.println("<div class=\"container\">");
  client.println("<div class=\"row\">");
  client.println(" <div class=\"col-md-8 col-md-offset-2\">");
  client.println("<div class=\"banner-content\">");
  client.println("<h6>Internet of Things - Wi-Po</h6>");
  client.println("<h2>The Smart Chair</h2>");
  client.println("</div> </div> </div> </div></div>");

  client.println("<div class=\"second-tabs-content what-we-do\">");
  client.println("<div class=\"container\">");
  client.println("<div class=\"row\">");
  client.println("<div class=\"col-md-12\">");
  client.println("<div class=\"section-heading\">");
  client.println("<h4>Chair availability</h4>");
  client.println("<p>On this website you can check wether the chair is available or not.</p>");
  client.println("</div></div></div>");

  client.println("<div class=\"row\">");
  client.println("<div class=\"wrapper\">");
  client.println("<div class=\"col-md-12\">");
  if (newData[0] == '8') {
    client.println("<div class=\"active\">");
    client.println("<div class=\"list-item\">");
    client.println("<div class=\"icon\">");
    client.println("<img src=\"https://mt.googleapis.com/vt/icon/name=icons/onion/SHARED-mymaps-container_4x.png,icons/onion/1769-checkmark_4x.png&highlight=7CB342&scale=2.0\" alt=\"\">");
    client.println("</div>");
    client.println("<h4>Chair is available</h4>");
    client.println("</div> </div>");
  }
  if (newData[0] == '1') {
    client.println("<div class=\"inactive\">");
    client.println(" <div class=\"list-item\">");
    client.println("<div class=\"icon\">");
    client.println("<img src=\"https://mt.googleapis.com/vt/icon/name=icons/onion/SHARED-mymaps-container_4x.png,icons/onion/1898-x-cross_4x.png&highlight=E65100&scale=2.0\" alt=\"\">");
    client.println("</div>");
    client.println(" <h4>Chair is occupied</h4>");
    client.println("</div> </div>");
  }
  client.println("</div></div></div></div> </div>");

  client.println("<div class=\"second-tabs-content what-we-do\">");
  client.println("<div class=\"container\">");
  client.println("<div class=\"row\">");
  client.println("<div class=\"col-md-12\">");
  client.println("<div class=\"section-heading\">");
  client.println("<h4>Module power</h4>");
  client.println("<p>Here you can check the battery level of the module.</p>");

  switch (newData[1]) {
    case '0': client.println("<h4>Battery is low please charge</h4>");
      break;
    case '1': client.println("<h4>20%</h4>");
      break;
    case '2': client.println("<h4>50%</h4>");
      break;
    case '3': client.println("<h4>70%</h4>");
      break;
    case '4': client.println("<h4>90%</h4>");
      break;
    default: client.println("<h4>Can't read battery levels! Something went wrong!</h4>");
      break;
  }


  client.println("</div></div></div></div></div>");

  client.println("<footer>");
  client.println("<div class=\"container\">");
  client.println("<div class=\"row\">");
  client.println("<div class=\"col-md-4 col-sm-12\">");
  client.println("<p>Copyright &copy; 2017 - 2018 AP-Hogeschool <br> Nathan Steven Ewout Robin</p>");
  client.println("</div>");

  client.println("<div class=\"col-md-2 col-md-offset-2 col-sm-12\">");
  client.println("<div class=\"back-to-top\">");
  client.println("<a href=\"#top\"><i class=\"fa fa-angle-up\"></i>back to top</a>");
  client.println("</div></div></div></div></footer></body></html>");



  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}


