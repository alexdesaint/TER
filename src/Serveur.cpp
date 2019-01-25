#include "Serveur.hpp"

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>

#include "pageWebVide.hpp"
#include "HTMLgenerator.hpp"


ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
DNSServer dnsServer;
String page;
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

void handleNotFound(){
  server.sendHeader("Location", "/", true);
  server.send (200, "text/html", page);
}
 
void handleRoot(){
  server.send(200, "text/html", page);
}

void Serveur::InitServeur(String id) {
  ssid = id.c_str();
  page = MAIN_page_vide;

  //delay(1000);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(ssid, "tempsdevol");

  Serial.print("Connect to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  server.on("/", handleRoot);
  server.on("/generate_204", handleRoot);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  server.on("/fwlink", handleRoot);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("Web server started!");

  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  //dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "www.tempsdevol.com", WiFi.softAPIP()); //Redirect research to the web page

  page = MAIN_page_vide; //on commence par une page blanche

}

void Serveur::modifyMeasurements(std::list<std::array<uint32_t, 10>> temps) {
  HTMLgenerator htmlCode = HTMLgenerator();

  page = htmlCode.getCode(temps);
}

void Serveur::useServeur() {
  dnsServer.processNextRequest();
  server.handleClient();
}