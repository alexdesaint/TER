#include "Serveur.hpp"
//#include "WiFiManager.hpp"

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
String page;

void handleNotFound(){
  server.sendHeader("Location", "/", true);
  server.send (200, "text/html", page);
}
 
void handleRoot(){
  server.send(200, "text/html", page);
}

void Serveur::InitServeur(String id) {
  ssid = &id[0];
  page = MAIN_page_vide;

  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);

  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(ssid); //begin WiFi access point
  Serial.println("");

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); //use this IP to go in the web page
  
  server.on("/",handleRoot);
  server.on("/generate_204", handleRoot);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleRoot);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("Web server started!");

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP()); //Redirect research to the web page

  page = MAIN_page_vide; //on commence par une page blanche
}

void Serveur::modifyMeasurements(std::list<std::array<uint32_t, 10>> temps) {
  HTMLgenerator htmlCode = HTMLgenerator();
  std::string str = htmlCode.getCode(temps);
  const char *cstr = str.c_str();
  page = String(cstr);
}

void Serveur::useServeur() {
  dnsServer.processNextRequest();
  server.handleClient();
}