#include <WiFi.h>
#include <WebServer.h>
#include <map>

const int pinLaser = 5;       // Pin donde se conecta el láser
const int dotDuration = 200;  // Duración del punto en milisegundos

// Configuración de red
const char *ssid = "";      //  Cambia por tu SSID
const char *password = "";  //  Cambia por tu contraseña

// Crear un objeto WebServer en el puerto 80
WebServer server(80);

// Representación del código Morse usando clave-valor
std::map<char, String> morseCode = {
  { 'A', ".-" }, { 'B', "-..." }, { 'C', "-.-." }, { 'D', "-.." }, { 'E', "." }, { 'F', "..-." }, { 'G', "--." }, { 'H', "...." }, { 'I', ".." }, { 'J', ".---" }, { 'K', "-.-" }, { 'L', ".-.." }, { 'M', "--" }, { 'N', "-." }, { 'O', "---" }, { 'P', ".--." }, { 'Q', "--.-" }, { 'R', ".-." }, { 'S', "..." }, { 'T', "-" }, { 'U', "..-" }, { 'V', "...-" }, { 'W', ".--" }, { 'X', "-..-" }, { 'Y', "-.--" }, { 'Z', "--.." }
};

// Función para enviar código Morse
void enviarMorse(const char *mensaje) {
  Serial.print("Acabas de mandar el siguiente mensaje: '");

  // Imprimir el mensaje con espacios entre letras
  for (int i = 0; i < strlen(mensaje); i++) {
    Serial.print(mensaje[i]);
    if (mensaje[i] != ' ' && i < strlen(mensaje) - 1) {
      Serial.print(" ");
    }
  }
  Serial.println("'");

  // Procesar el mensaje para enviar en código Morse
  while (*mensaje) {
    if (*mensaje >= 'A' && *mensaje <= 'Z') {
      enviarCodigoMorse(morseCode[*mensaje]);  // Enviar letra en código Morse
    }
    delay(dotDuration * 7);  // Pausa uniforme entre letras y palabras
    mensaje++;               // Avanzar al siguiente carácter
  }
}

void enviarCodigoMorse(String codigo) {
  for (int i = 0; i < codigo.length(); i++) {
    if (codigo[i] == '.') {
      digitalWrite(pinLaser, HIGH);  // Activar láser
      delay(dotDuration);
      digitalWrite(pinLaser, LOW);  // Desactivar láser
      delay(dotDuration);
    } else if (codigo[i] == '-') {
      digitalWrite(pinLaser, HIGH);  // Activar láser
      delay(dotDuration * 3);
      digitalWrite(pinLaser, LOW);  // Desactivar láser
      delay(dotDuration);
    }
  }
  delay(dotDuration * 3);  // Espacio entre letras
}

// Página web que se mostrará al cliente
String crearPaginaWeb(String mensaje = "") {
  String paginaWeb = "<html>\
  <head>\
    <title>Enviar mensaje en Morse</title>\ 
    <meta charset='utf-8'>\
    <style>\
      body { font-family: Arial, sans-serif; text-align: center; padding-top: 50px; }\
      h1 { color: #333; }\
      input[type='text'] { padding: 10px; font-size: 18px; }\
      input[type='submit'] { padding: 10px 20px; font-size: 18px; background-color: #4CAF50; color: white; border: none; cursor: pointer; }\
    </style>\
  </head>\
  <body>\
    <h1>Enviar mensaje en Morse</h1>\
    <form action='/enviar' method='GET'>\
      <input type='text' name='mensaje' placeholder='Escribe tu mensaje' required>\
      <input type='submit' value='Enviar'>\
    </form>";

  if (mensaje != "") {
    paginaWeb += "<h2>Mensaje enviado: " + mensaje + "</h2>";
  }

  paginaWeb += "</body>\
  </html>";

  return paginaWeb;
}

void handleRoot() {
  server.send(200, "text/html", crearPaginaWeb());
}

void handleEnviar() {
  if (server.hasArg("mensaje")) {
    String mensaje = server.arg("mensaje");
    mensaje.toUpperCase();  // Convertir a mayúsculas
    enviarMorse(mensaje.c_str());

    // Mostrar el mensaje enviado en la misma página
    server.send(200, "text/html", crearPaginaWeb(mensaje));
  } else {
    server.send(400, "text/plain", "Mensaje no recibido");
  }
}

void setup() {
  pinMode(pinLaser, OUTPUT);
  Serial.begin(115200);

  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Conectado a WiFi!");
  Serial.print("IP del servidor web: ");
  Serial.println(WiFi.localIP());

  // Definir rutas del servidor web
  server.on("/", handleRoot);
  server.on("/enviar", handleEnviar);

  // Iniciar el servidor web
  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  // Manejar las solicitudes del servidor web
  server.handleClient();
}
