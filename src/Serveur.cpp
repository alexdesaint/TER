#include "Serveur.hpp"
#include "pageWeb.hpp"

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

void handleNotFound(){
  server.sendHeader("Location", "/", true);
  server.send (200, "text/html", MAIN_page);
  //server.send(404, "text/plain", "404: Not found");
}
 
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void Serveur::test() {

  /* Soft AP network parameters */
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

}

void Serveur::useServeur() {
  dnsServer.processNextRequest();
  server.handleClient();
}
